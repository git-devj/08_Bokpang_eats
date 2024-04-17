#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("./bokpangeats");

    if(!mydb.open())
        qDebug("Fail Database");
    else
        qDebug("DB Connect");
    bok_server = new QTcpServer();
    int port = 8080;
    if(bok_server->listen(QHostAddress::Any,port))
    {
        connect(bok_server, &QTcpServer::newConnection,this, &Widget::newcli_connection);
        //새로운 클라 접속시 newcl~로 연결
    }
}
Widget::~Widget()
{

    socket->close();
    socket->deleteLater();


    // 서버 소켓 해제
    bok_server->close();
    bok_server->deleteLater();
    delete ui;
}

//cli 연결
void Widget::newcli_connection()
{
    while(bok_server->hasPendingConnections())
    {
        cli_manage(bok_server->nextPendingConnection());
    }

}

//연결된cli 관리
void Widget::cli_manage(QTcpSocket* socket)
{
    bok_clSKT.insert(socket);
    //cli접속->bok_clSKT에서 소켓으로 묶어줌
    connect(socket, &QTcpSocket::readyRead, this, &Widget::fromcli_data);
    //cli에서 송신한 데이터를 수신
    connect(this, &Widget::signal_newmessage,this, &Widget::sendcategoribtn_clicked);

    socklist[socket]=QString::number(socket->socketDescriptor());
    ui->receiver_sel_comboBox->addItem(socklist[socket]);

    connect(socket,SIGNAL(disconnected()),this,SLOT(slot_discardSocket()));

    sendclidata(socket);

}
void Widget::sendclidata(QTcpSocket* socket)
{
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    QString clidata=socklist[socket];

    QByteArray mytype;
    mytype.prepend(QString("from:server,datatype:cliID,datasize:%1;").arg(clidata.size()).toUtf8());
    mytype.resize(128);


    QByteArray sendclidata=clidata.toUtf8();
    sendclidata.prepend(mytype);

    qDebug()<<sendclidata;
    socketStream<<sendclidata;
}
//cli로부터 온 데이터관리
void Widget::fromcli_data()
{
    //서버에 연결된 클라이언트들중 데이터보낸 클라이언트를 확인
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    //서버에 연결된 cli를 stream으로 연결
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    //stream으로 읽은데이터를 fromcli로 넘김
    socketStream.startTransaction();
    socketStream>>fromcli;

    //위과정에서 문제시 메시지를 출력 후 함수 종료
    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1::데이터를 기다리는중 . . .").arg(socket->socketDescriptor());
        emit signal_newmessage(message);
        return;
    }

    //cli에서 보낸 메시지를 담은 fromcli를 처음128byte만 읽어서 header에 담고
    header = fromcli.mid(0,128);
    // 클라이언트 구분
    cliID = header.split(",")[0].split(":")[1];
    // 클라이언트 타입을 확인하는 코드
    fromcliType = header.split(",")[1].split(":")[1];
    if(fromcliType=="user")
    {
        socklist[socket]=QString::number(socket->socketDescriptor());
    }
    else
    {
        shopsocklist[socket]=QString::number(socket->socketDescriptor());
        shopID=QString::number(socket->socketDescriptor());
    }
    //클라이언트의 데이터의 종류?
    fromcliChoose = header.split(",")[2].split(":")[1];
    //fromcli의 128byte 이후 부분
    fromcli = fromcli.mid(128);

    //%1의 argument에 클라이언트의 구분,%2의 argument에 클라이언트가 보낸 데이터
    QString message= QString("%1::%2").arg(socket->socketDescriptor()).arg(QString::fromStdString(fromcli.toStdString()));
    sendcategoribtn_clicked();
}
void Widget::sendcategori_data(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            int i=0;
            int j=0;
            QString query = QString("SELECT Shop From MENU WHERE Categori = '%1'").arg(fromcli);
            QSqlQuery qry(query);
            qry.exec();
            while(qry.next())
            {

                if(i%4==1)
                {
                    if(j>0)
                    {
                        //클라이언트에서 데이터를 수신할떄 .단위로 보낸사람 구분,:단위로 메시지시작부분 구분(클라이언트에서 수신한메시지 저장후 /로 데이터들의 세부 구분)
                        tocli+="/";
                    }
                    tocli+=qry.value(0).toString();
                    j++;
                }
                i++;
            }
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:shop,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::sendshop_data(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            int j=0;
            QString query = QString("SELECT Menu,MenuName,Price From MENU WHERE Shop = '%1'").arg(fromcli);
            QSqlQuery qry(query);
            qry.exec();
            while(qry.next())
            {
                if(j>0)
                {
                    //클라이언트에서 데이터를 수신할떄 .단위로 보낸사람 구분,:단위로 메시지시작부분 구분(클라이언트에서 수신한메시지 저장후 /로 데이터들의 세부 구분)
                    tocli+="/";
                }
                tocli=tocli+qry.value(0).toString()+"*"+qry.value(1).toString()+"&"+qry.value(2).toString();
                j++;

            }
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:menu,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");

}
void Widget::sendmenu_data(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            int j=0;
            QString query = QString("SELECT Menu,MenuName,Price From MENU WHERE Shop = '%1'").arg(fromcli);
            QSqlQuery qry(query);
            qry.exec();
            while(qry.next())
            {
                if(j>0)
                {
                    //클라이언트에서 데이터를 수신할떄 .단위로 보낸사람 구분,:단위로 메시지시작부분 구분(클라이언트에서 수신한메시지 저장후 /로 데이터들의 세부 구분)
                    tocli+="/";
                }
                tocli=tocli+qry.value(0).toString()+"*"+qry.value(1).toString()+"&"+qry.value(2).toString();
                j++;
            }
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:menu,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");

}


void Widget::sendcategoribtn_clicked()
{
    if(fromcliType=="user")
    {
        if(fromcliChoose=="categori")
        {
            socket=socklist.key(cliID);
            sendcategori_data(socket);

        }
        else if(fromcliChoose=="shop")
        {

            socket=socklist.key(cliID);
            sendshop_data(socket);

        }
        else if(fromcliChoose=="menu")
        {

            socket=socklist.key(cliID);
            sendmenu_data(socket);
        }
        else if(fromcliChoose=="question")
        {
            socket=socklist.key(cliID);
            slot_readsock();
        }
        else if(fromcliChoose=="ID")
        {
            socket=socklist.key(cliID);
            checkID(socket);
        }
        else if(fromcliChoose=="PH")
        {
            socket=socklist.key(cliID);
            checkPH(socket);
        }
        else if(fromcliChoose=="EMAIL")
        {
            socket=socklist.key(cliID);
            checkEMAIL(socket);
        }
        else if(fromcliChoose=="SIGNUP")
        {
            socket=socklist.key(cliID);
            SIGNUP();
        }
        else if(fromcliChoose=="findPW")
        {
            socket=socklist.key(cliID);
            findPW();
        }
        else if(fromcliChoose=="findID")
        {
            socket=socklist.key(cliID);
            findID();
        }
        else if(fromcliChoose=="SIGNIN")
        {
            socket=socklist.key(cliID);
            SIGNIN();
        }
        else if(fromcliChoose=="toShop")
        {
            shop=shopsocklist.key(shopID);
            toShop();

        }
    }
    else
    {
        if(fromcliChoose=="basket")
        {

            touser();
        }
    }
}
void Widget::touser()
{

    QString toshop=fromcli;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("from:server,data:basket,size:%1;").arg(toshop.size()).toUtf8());
    header.resize(128);

    // message 인코딩 설정하고, QByteArray에 할당하고
    QByteArray byteArray = toshop.toUtf8();
    // header 정보를 앞에 넣어준다.
    byteArray.prepend(header);

    // stream으로 byteArray 정보 전송
    socketStream << byteArray;

    qDebug()<<toshop;

}
void Widget::toShop()
{
    if(shop)
    {
        if(shop->isOpen())
        {
            QString toshop=fromcli;
            QDataStream socketStream(shop);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:basket,size:%1;").arg(toshop.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = toshop.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<toshop;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::SIGNIN()
{
   qDebug()<<"로그인쓰";
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            QSqlQuery query;
            QString queee = QString("SELECT ID FROM UserData WHERE ID = %1").arg(fromcli);
            query.exec(queee);
            if(!query.next())
            {
                tocli="ID혹은 비밀번호가 틀렸습니다";
            }
            else
            {
                tocli="로그인 완료";
            }

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:SIGNIN,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::findID()
{
    QSqlQuery query;
    QString queee = QString("SELECT ID FROM UserData WHERE NAME = %1").arg(fromcli);
    query.exec(queee);
    qDebug()<<queee;
    qDebug()<<"아이디찾기쓰";
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            QSqlQuery query;
            QString queee = QString("SELECT ID FROM UserData WHERE NAME = %1").arg(fromcli);
            query.exec(queee);
            if(!query.next())
            {
                tocli="해당정보가 존재하지않습니다";
            }
            else
            {
                tocli=query.value(0).toString();
            }

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:findID,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::findPW()
{

    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            QSqlQuery query;
            QString queee = QString("SELECT PW FROM UserData WHERE NAME = %1").arg(fromcli);
            qDebug()<<queee;
            query.exec(queee);
            if(!query.next())
            {
                tocli="해당정보가 존재하지않습니다";
            }
            else
            {
                tocli=query.value(0).toString();
            }

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:findPW,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::SIGNUP()
{
    QSqlQuery query;
    QString queee = QString("INSERT INTO UserData VALUES(%1)").arg(fromcli);
    query.exec(queee);
    qDebug()<<queee;
    qDebug()<<"횐갑쓰";
}
void Widget::checkID(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            QString query = QString("SELECT ID From UserData WHERE ID = '%1'").arg(fromcli);
            QSqlQuery qry(query);
            qry.exec();
            if(!qry.next())
            {
                tocli="YES";
            }
            else
            {
                tocli="NO";
            }

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:ID,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::checkPH(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            QString query = QString("SELECT PH From UserData WHERE PH = '%1'").arg(fromcli);
            QSqlQuery qry(query);
            qry.exec();
            if(!qry.next())
            {
                tocli="YES";
            }
            else
            {
                tocli="NO";
            }

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:PH,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
void Widget::checkEMAIL(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString tocli="";
            int j=0;
            QString query = QString("SELECT EMAIL From UserData WHERE EMAIL = '%1'").arg(fromcli);
            QSqlQuery qry(query);
            qry.exec();
            if(!qry.next())
            {
                tocli="YES";
            }
            else
            {
                tocli="NO";
            }

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("from:server,data:EMAIL,size:%1;").arg(tocli.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = tocli.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

            qDebug()<<tocli;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}


void Widget::send_msg(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen()) // 소켓이 열려있으면
        {
            QString msg = ui->tell_lineEdit->text(); // 입력창의 내용을 문자열 msg에

            QDataStream sock_stream(socket); // (서버에 연결된) sock과 연결된 데이터 스트림 생성

            QByteArray bytearr = msg.toUtf8(); // 메시지의 인코딩 설정

            // sock_stream << bytearr; // 데이터 스트림으로 인코딩된 메시지 전송
            QByteArray header;
            header.prepend(QString("from:server,data:question,size:%1;").arg(msg.size()).toUtf8());
            header.resize(128);

            // message 인코딩 설정하고, QByteArray에 할당하고
            // header 정보를 앞에 넣어준다.
            bytearr.prepend(header);

            // stream으로 byteArray 정보 전송
            sock_stream << bytearr;
            slot_displaymsg("나:"+msg);
        }
        else {
            QMessageBox::critical(this, "Uni_server", "소켓이 닫혀있습니다.");
        }
    }
    else {
        QMessageBox::critical(this, "Uni_server", "연결되어 있지 않습니다.");
    }

}
void Widget::slot_readsock()
{
    QString message= QString("%1::%2").arg(socket->socketDescriptor()).arg(QString::fromStdString(fromcli.toStdString()));
    slot_displaymsg(message); // sig_new_msg(message) 시그널 방출
}
void Widget::slot_displaymsg(const QString& str)
{
    ui->comm_textEdit->append(str);
}

void Widget::on_send_pbtn_clicked()
{
    cliID=ui->receiver_sel_comboBox->currentText();
    socket=socklist.key(cliID);
    send_msg(socket);

    ui->tell_lineEdit->clear();
}


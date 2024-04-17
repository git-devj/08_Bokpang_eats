#include "bokpang_user.h"
#include "ui_bokpang_user.h"

Bokpang_user::Bokpang_user(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bokpang_user)
{
    ui->setupUi(this);
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(0);
    serv_socket= new QTcpSocket(this);
    serv_socket->connectToHost(QHostAddress::LocalHost,8080);
    if(serv_socket->waitForConnected())
    {
        qDebug("Connected to Server");
    }
    else
    {
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(serv_socket->errorString()));
        exit(EXIT_FAILURE);
    }
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("./bokpangeats");

    if(!mydb.open())
        qDebug("Fail Database");
    else
        qDebug("DB Connect");
    page_basket_pbtn_enable();
    connect(serv_socket, &QTcpSocket::readyRead,this,&Bokpang_user::receiveclidata);
    connect(this, &Bokpang_user::signal_newMessage,this, &Bokpang_user::slotdebugmessage);
    ui->signupbtn_->setDisabled(1);
}


Bokpang_user::~Bokpang_user()
{
    delete ui;
}

void Bokpang_user::receiveclidata()
{
    QDataStream socketStream(serv_socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream>>receivedata;

    // stream startTransaction 실행 문제시 에러 표시 후 함수 종료
    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(serv_socket->socketDescriptor());
        emit signal_newMessage(message);
        return;
    }
    //0~128바이트까지
    QString data = receivedata.mid(0,128);
    //data를 재단
    //어디서왔는지
    QString from = data.split(",")[0].split(":")[1];
    //어떤종류를 보낸건지
    QString datatype= QString("%1").arg(data.split(",")[1].split(":")[1]);

    receivedata=receivedata.mid(128);
    encodingdata=QString("%1").arg(QString::fromStdString(receivedata.toStdString()));
    qDebug()<<data;
    qDebug("\n");
    qDebug()<<from;
    qDebug("\n");
    qDebug()<<datatype;
    if(datatype=="cliID")
    {
        myname=encodingdata;
    }
    else if(datatype=="shop")
    {
        slotdebugmessage(encodingdata);
    }
    else if(datatype=="menu")
    {
        showmenu(encodingdata);
    }
    else if(datatype=="question")
    {
        slot_read_sock();
    }
    else if(datatype=="ID")
    {
        checkID();
    }
    else if(datatype=="PH")
    {
        checkPH();
    }
    else if(datatype=="EMAIL")
    {
        checkEMAIL();
    }
    else if(datatype=="SIGNUP")
    {
        qDebug()<<"회원가입완료";
    }
    else if(datatype=="findID")
    {
        if(receivedata=="해당정보가 존재하지않습니다")
        {

            QMessageBox::StandardButton check=QMessageBox::warning(this,"정보가없음",QString("정보가 존재하지않습니다"),QMessageBox::Yes);
            {
                qDebug()<<"해당정보가 존재하지않습니다";
                if(check==QMessageBox::Yes)
                {
                    ui->find_pw_email_lineEdit->setText("");
                    ui->find_pw_id_lineEdit->setText("");
                    ui->find_pw_name_lineEdit->setText("");
                    ui->find_pw_ph_lineEdit->setText("");
                }
                else;
            }
        }
        else
        {
            QMessageBox::StandardButton check=QMessageBox::warning(this,"아이디 확인",QString("찾으시는 ID:%1").arg(receivedata),QMessageBox::Yes);
            if(check==QMessageBox::Yes)
            {
                ui->find_id_email_lineEdit->setText("");
                ui->find_id_name_lineEdit->setText("");
                ui->find_id_ph_lineEdit->setText("");
                ui->Bokpang_eats_stackedWidget->setCurrentIndex(1);
            }
            else;
        }
    }
    else if(datatype=="findPW")
    {
        if(receivedata=="해당정보가 존재하지않습니다")
        {

            QMessageBox::StandardButton check=QMessageBox::warning(this,"정보가없음",QString("정보가 존재하지않습니다"),QMessageBox::Yes);
            {
                qDebug()<<"해당정보가 존재하지않습니다";
                if(check==QMessageBox::Yes)
                {
                    ui->find_pw_email_lineEdit->setText("");
                    ui->find_pw_id_lineEdit->setText("");
                    ui->find_pw_name_lineEdit->setText("");
                    ui->find_pw_ph_lineEdit->setText("");
                }
                else;
            }
        }
        else
        {
            QMessageBox::StandardButton check=QMessageBox::warning(this,"비밀번호 확인",QString("입력하신 ID의 비밀번호:%1").arg(receivedata),QMessageBox::Yes);
            if(check==QMessageBox::Yes)
            {
                ui->find_pw_email_lineEdit->setText("");
                ui->find_pw_id_lineEdit->setText("");
                ui->find_pw_name_lineEdit->setText("");
                ui->find_pw_ph_lineEdit->setText("");
                ui->Bokpang_eats_stackedWidget->setCurrentIndex(1);
            }
            else;
        }
    }
    else if(datatype=="SIGNIN")
    {
        if(receivedata=="ID혹은 비밀번호가 틀렸습니다")
        {

            QMessageBox::StandardButton check=QMessageBox::warning(this,"로그인실패",QString("ID혹은 비밀번호가 틀렸습니다"),QMessageBox::Yes);
            {
                qDebug()<<"ID혹은 비밀번호가 틀렸습니다";
                if(check==QMessageBox::Yes)
                {
                    ui->id_lineEdit->setText("");
                    ui->pw_lineEdit->setText("");
                }
                else;
            }
        }
        else
        {
            QMessageBox::StandardButton check=QMessageBox::warning(this,"로그인성공",QString("로그인성공"),QMessageBox::Yes);
            {
                qDebug()<<"로그인성공";
                if(check==QMessageBox::Yes)
                {
                    ui->Bokpang_eats_stackedWidget->setCurrentIndex(5);
                }
                else;
            }
        }
    }
    else if(datatype=="basket")
    {
        if(receivedata=="accept")
        {

            QMessageBox::StandardButton check=QMessageBox::warning(this,"주문승인",QString("주문이 승인되었습니다"),QMessageBox::Yes);
            {

                if(check==QMessageBox::Yes)
                {
                    qDebug()<<"주문승인완료";
                    ui->Bokpang_eats_stackedWidget->setCurrentIndex(0);
                }
                else;
            }
        }
        else
        {
            QMessageBox::StandardButton check=QMessageBox::warning(this,"주문승인",QString("주문이 거절되었습니다"),QMessageBox::Yes);
            {

                if(check==QMessageBox::Yes)
                {
                    qDebug()<<"주문거절";
                    ui->basket_tableWidget->clear();
                    basketmenu="";
                    basketprice=0;
                }
                else;
            }
        }
    }
}
void Bokpang_user::checkID()
{
    if(receivedata=="YES")
    {
        qDebug()<<"사용가능한아이디입니다";

        QMessageBox::StandardButton reply=QMessageBox::question(this,"아이디 확인","이 ID를 사용하시겠습니까?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            ui->sign_up_id_lineEdit->setReadOnly(1);
            ui->id_double_chk_pbtn->setDisabled(1);
            setting+=1;
        }
        else if(reply==QMessageBox::No)
        {
            qDebug()<<"다시입력";
        }
    }
    else
    {
        QMessageBox::StandardButton check=QMessageBox::warning(this,"중복",QString("중복된 아이디입니다 다시 입력하세요"),QMessageBox::Yes);
        {
            qDebug()<<"중복되었습니다 다시 입력하세요";
            if(check==QMessageBox::Yes)
            {
                ui->sign_up_id_lineEdit->setText("");
            }
        }
    }
    if(setting==3)
        ui->signupbtn_->setEnabled(1);
    else;
}
void Bokpang_user::checkPH()
{
    if(receivedata=="YES")
    {
        qDebug()<<"사용가능한전화번호입니다";

        QMessageBox::StandardButton reply=QMessageBox::question(this,"전화번호 확인","이 번호를 사용하시겠습니까?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            ui->sign_up_ph_lineEdit->setReadOnly(1);
            ui->ph_double_chk_pbtn->setDisabled(1);
            setting+=1;
        }
        else if(reply==QMessageBox::No)
        {
            qDebug()<<"다시입력";
        }
    }
    else
    {
        QMessageBox::StandardButton check=QMessageBox::warning(this,"중복","중복된 번호입니다 다시 입력하세요",QMessageBox::Yes);
        {
            qDebug()<<"중복되었습니다 다시 입력하세요";
            if(check==QMessageBox::Yes)
            {
                ui->sign_up_ph_lineEdit->setText("");
            }
        }
    }
    if(setting==3)
        ui->signupbtn_->setEnabled(1);
    else;
}

void Bokpang_user::checkEMAIL()
{
    if(receivedata=="YES")
    {
        qDebug()<<"사용가능한이메일입니다";

        QMessageBox::StandardButton reply=QMessageBox::question(this,"이메일 확인","이 이메일을 사용하시겠습니까?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            ui->sign_up_email_lineEdit->setReadOnly(1);
            ui->email_double_chk_pbtn->setDisabled(1);
            setting+=1;
        }
        else if(reply==QMessageBox::No)
        {
            qDebug()<<"다시입력";
        }
    }
    else
    {
        QMessageBox::StandardButton check=QMessageBox::warning(this,"중복","중복된 이메일입니다 다시 입력하세요",QMessageBox::Yes);
        {
            qDebug()<<"중복되었습니다 다시 입력하세요";
            if(check==QMessageBox::Yes)
            {
                ui->sign_up_email_lineEdit->setText("");
            }
        }
    }
    if(setting==3)
        ui->signupbtn_->setEnabled(1);
    else;
}

void Bokpang_user::startbtn_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(1);
}
void Bokpang_user::on_categoribtn_clicked()
{

    QPushButton *clickbtntemp = (QPushButton*)sender();
    categori = clickbtntemp->objectName();
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = categori;

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:categori,send:%2;").arg(myname).arg(categori.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = categori.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


void Bokpang_user::slotdebugmessage(const QString& str)
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(7);
    // qDebug()<<str;
    for(int i=0;i<4;i++)
    {
        shop[i]=str.split("/")[i];
    }
    for(int i=0;i<4;i++)
    {
        // qDebug()<<shop[i];
    }
    ui->shoplabel1->setText(shop[0]);
    ui->shoplabel2->setText(shop[1]);
    ui->shoplabel3->setText(shop[2]);
    ui->shoplabel4->setText(shop[3]);
}
void Bokpang_user::showmenu(const QString& str)
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(8);
    for (int j=0;j<4;j++)
    {
        menulist[j]=encodingdata.split("/")[j].split("*")[0];
        menunamelist[j]=encodingdata.split("/")[j].split("*")[1].split("&")[0];
        menupricelist[j]=encodingdata.split("/")[j].split("*")[1].split("&")[1];
        qDebug()<<menulist[j];
        qDebug()<<menunamelist[j];
        qDebug()<<menupricelist[j];

    }
    qDebug()<<menulist[1];
    QPixmap pixmap1(QString(":/food/bokpang_image/%1.jpg").arg(menulist[0]));
    QPixmap fitpixmap1=pixmap1.scaled(ui->menulabel1->width(),ui->menulabel1->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->menulabel1->setPixmap(fitpixmap1);
    QPixmap pixmap2(QString(":/food/bokpang_image/%1.jpg").arg(menulist[1]));
    QPixmap fitpixmap2=pixmap2.scaled(ui->menulabel1->width(),ui->menulabel1->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->menulabel2->setPixmap(fitpixmap2);
    QPixmap pixmap3(QString(":/food/bokpang_image/%1.jpg").arg(menulist[2]));
    QPixmap fitpixmap3=pixmap3.scaled(ui->menulabel1->width(),ui->menulabel1->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->menulabel3->setPixmap(fitpixmap3);
    QPixmap pixmap4(QString(":/food/bokpang_image/%1.jpg").arg(menulist[3]));
    QPixmap fitpixmap4=pixmap4.scaled(ui->menulabel1->width(),ui->menulabel1->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->menulabel4->setPixmap(fitpixmap4);
}
void Bokpang_user::on_shopbtn1_clicked()
{
    ui->shopLabel->setText(shop[0]);
    shopselect=0;
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = shop[0];

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:menu,send:%2;").arg(myname).arg(shop[0].size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = shop[0].toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
    shopselect=0;
}
void Bokpang_user::on_shopbtn2_clicked()
{
    ui->shopLabel->setText(shop[1]);
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = shop[1];

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:menu,send:%2;").arg(myname).arg(shop[0].size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = shop[1].toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
    shopselect=1;
}
void Bokpang_user::on_shopbtn3_clicked()
{
    ui->shopLabel->setText(shop[2]);
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = shop[2];

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:menu,send:%2;").arg(myname).arg(shop[0].size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = shop[2].toUtf8();
            byteArray.prepend(header);
            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
    shopselect=2;
}
void Bokpang_user::on_shopbtn4_clicked()
{
    ui->shopLabel->setText(shop[3]);
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = shop[3];

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:menu,send:%2;").arg(myname).arg(shop[0].size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = shop[3].toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
    shopselect=3;
}



void Bokpang_user::on_VoC_pbtn_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(6);
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = shop[3];

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:question,send:%2;").arg(myname).arg(shop[0].size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = shop[3].toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


void Bokpang_user::on_send_pbtn_clicked()
{
    if(serv_socket)
    {
        if(serv_socket->isOpen()) // 소켓이 열려있으면
        {
            QString msg = ui->tell_lineEdit->text(); // 입력창의 내용을 문자열 msg에

            QDataStream sock_stream(serv_socket); // (서버에 연결된) sock과 연결된 데이터 스트림 생성
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:question,send:%2;").arg(myname).arg(msg.size()).toUtf8());
            header.resize(128);

            QByteArray bytearr = msg.toUtf8(); // 메시지의 인코딩 설정

            bytearr.prepend(header);

            sock_stream << bytearr; // 데이터 스트림으로 인코딩된 메시지 전송


            ui->tell_lineEdit->clear(); // 보낸 뒤에는 입력창 비움
            slot_displaymsg("나:"+msg);

        }
        else {
            QMessageBox::critical(this, "Uni_client", "소켓이 닫혀있습니다.");
        }
    }
    else {
        QMessageBox::critical(this, "Uni_client", "연결되어 있지 않습니다.");
    }
}

void Bokpang_user::slot_read_sock()
{
    QString message = QString("%1").arg(QString::fromStdString(receivedata.toStdString())); // 메시지 형태를 유저명: bytearr형태로
    slot_displaymsg("상담사:"+message);
}
void Bokpang_user::slot_displaymsg(const QString& str)
{
    ui->comm_textEdit->append(str);
}

void Bokpang_user::on_id_double_chk_pbtn_clicked()
{
    QString ID;
    ID=ui->sign_up_id_lineEdit->text();
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:ID,send:%2;").arg(myname).arg(ID.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = ID.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");// if(!query.next())
}


void Bokpang_user::on_ph_double_chk_pbtn_clicked()
{
    QString PH;
    PH=ui->sign_up_ph_lineEdit->text();
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:PH,send:%2;").arg(myname).arg(PH.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = PH.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


void Bokpang_user::on_email_double_chk_pbtn_clicked()
{
    QString EMAIL;
    EMAIL=ui->sign_up_email_lineEdit->text();
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:EMAIL,send:%2;").arg(myname).arg(EMAIL.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = EMAIL.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}



void Bokpang_user::on_signupbtn__clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(1);
    QString NAME,ID,PW,EMAIL,PH;
    NAME=ui->sign_up_name_lineEdit->text();
    ID=ui->sign_up_id_lineEdit->text();
    PW=ui->sign_up_pw_lineEdit->text();
    EMAIL=ui->sign_up_email_lineEdit->text();
    PH=ui->sign_up_ph_lineEdit->text();
    QString SIGNUP="'"+NAME+"','"+ID+"','"+PW+"','"+EMAIL+"','"+PH+"'";
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:SIGNUP,send:%2;").arg(myname).arg(SIGNUP.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = SIGNUP.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");

}


void Bokpang_user::on_find_pw_pbtn_2_clicked()
{
    QString NAME,ID,EMAIL,PH;
    NAME=ui->find_pw_name_lineEdit->text();
    ID=ui->find_pw_id_lineEdit->text();
    EMAIL=ui->find_pw_email_lineEdit->text();
    PH=ui->find_pw_ph_lineEdit->text();
    QString findPW="'"+NAME+"'AND ID= '"+ID+"'AND EMAIL ='"+EMAIL+"'AND PH ='"+PH+"'";
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:findPW,send:%2;").arg(myname).arg(findPW.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = findPW.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


void Bokpang_user::on_find_id_pbtn_2_clicked()
{
    QString NAME,EMAIL,PH;
    NAME=ui->find_id_name_lineEdit->text();
    EMAIL=ui->find_id_email_lineEdit->text();
    PH=ui->find_id_ph_lineEdit->text();
    QString findID="'"+NAME+"'AND EMAIL ='"+EMAIL+"'AND PH ='"+PH+"'";
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:findID,send:%2;").arg(myname).arg(findID.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = findID.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


void Bokpang_user::on_login_pbtn_clicked()
{
    QString ID,PW;
    ID=ui->id_lineEdit->text();
    PW=ui->pw_lineEdit->text();
    QString login="'"+ID+"'AND PW ='"+PW+"'";
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:SIGNIN,send:%2;").arg(myname).arg(login.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = login.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


void Bokpang_user::on_find_id_pbtn_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(2);
}


void Bokpang_user::on_find_pw_pbtn_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(3);
}


void Bokpang_user::on_sign_up_pbtn_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(4);
}


void Bokpang_user::on_pushButton_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(1);
}
void Bokpang_user::page_basket_pbtn_enable()
{
    connect(ui->basket_back_pbtn, &QPushButton::clicked, this, &Bokpang_user::basket_back_pbtn_clicked);
    connect(ui->menubtn1, &QPushButton::clicked, this, &Bokpang_user::menu_pbtn_1_clicked);
    connect(ui->menubtn2, &QPushButton::clicked, this, &Bokpang_user::menu_pbtn_2_clicked);
    connect(ui->menubtn3, &QPushButton::clicked, this, &Bokpang_user::menu_pbtn_3_clicked);
    connect(ui->menubtn4, &QPushButton::clicked, this, &Bokpang_user::menu_pbtn_4_clicked);
    connect(ui->bakset_order_pbtn, &QPushButton::clicked, this, &Bokpang_user::basket_order_pbtn_clicked);
}
void Bokpang_user::basket_back_pbtn_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(8);
}

void Bokpang_user::menu_pbtn_1_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(9);
    ui->basket_tableWidget->setItem(row,0, new QTableWidgetItem(menunamelist[0]));
    ui->basket_tableWidget->setItem(row, 1, new QTableWidgetItem(menupricelist[0]));
    if(basketprice>0)
        basketmenu+=",";
    basketmenu+=menunamelist[0];
    basketprice+=menupricelist[0].toInt();
    row++;
}
void Bokpang_user::menu_pbtn_2_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(9);
    ui->basket_tableWidget->setItem(row, 0, new QTableWidgetItem(menunamelist[1]));
    ui->basket_tableWidget->setItem(row, 1, new QTableWidgetItem(menupricelist[1]));
    if(basketprice>0)
        basketmenu+=",";
    basketmenu+=menunamelist[1];
    basketprice+=menupricelist[1].toInt();
    row++;
}
void Bokpang_user::menu_pbtn_3_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(9);
    ui->basket_tableWidget->setItem(row, 0, new QTableWidgetItem(menunamelist[2]));
    ui->basket_tableWidget->setItem(row, 1, new QTableWidgetItem(menupricelist[2]));
    if(basketprice>0)
        basketmenu+=",";
    basketmenu+=menunamelist[2];
    basketprice+=menupricelist[2].toInt();
    row++;
}
void Bokpang_user::menu_pbtn_4_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(9);
    ui->basket_tableWidget->setItem(row, 0, new QTableWidgetItem(menunamelist[3]));
    ui->basket_tableWidget->setItem(row, 1, new QTableWidgetItem(menupricelist[3]));
    if(basketprice>0)
        basketmenu+=",";
    basketmenu+=menunamelist[3];
    basketprice+=menupricelist[3].toInt();
    row++;
}

void Bokpang_user::basket_order_pbtn_clicked()
{
    // ui->Bokpang_eats_stackedWidget->setCurrentIndex(10);
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString toserver = basketmenu+"/"+QString("%1").arg(basketprice);
            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("cliID:%1,cliType:user,cliChoose:toShop,send:%2;").arg(myname).arg(toserver.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = toserver.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}



void Bokpang_user::on_basket_back_pbtn_2_clicked()
{
    ui->Bokpang_eats_stackedWidget->setCurrentIndex(5);
}


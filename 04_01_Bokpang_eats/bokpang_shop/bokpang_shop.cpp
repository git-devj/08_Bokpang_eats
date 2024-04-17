#include "bokpang_shop.h"
#include "ui_bokpang_shop.h"

bokpang_shop::bokpang_shop(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bokpang_shop)
{
    ui->setupUi(this);
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
    connect(serv_socket, &QTcpSocket::readyRead,this,&bokpang_shop::receivebasket);

}

bokpang_shop::~bokpang_shop()
{
    delete ui;
}
void bokpang_shop::receivebasket()
{
    QDataStream socketStream(serv_socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream>>receivedata;

    // stream startTransaction 실행 문제시 에러 표시 후 함수 종료
    //0~128바이트까지
    QString data = receivedata.mid(0,128);
    //data를 재단
    //어디서왔는지
    QString from = data.split(",")[0].split(":")[1];
    //어떤종류를 보낸건지
    QString datatype= QString("%1").arg(data.split(",")[1].split(":")[1]);

    receivedata=receivedata.mid(128);
   QString encodingdata=QString("%1").arg(QString::fromStdString(receivedata.toStdString()));
    qDebug()<<data;
    qDebug("\n");
    qDebug()<<from;
    qDebug("\n");
    qDebug()<<datatype;
    if(datatype=="cliID")
    {
        myname=encodingdata;

        if(serv_socket)
        {
            if(serv_socket->isOpen())
            {
                QString choose = "data";

                QDataStream socketStream(serv_socket);
                socketStream.setVersion(QDataStream::Qt_5_15);
                QByteArray header;
                header.prepend(QString("cliID:%1,cliType:shop,cliChoose:menu,send:%2;").arg(myname).arg(choose.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = "im shop";
                byteArray.prepend(header);

                socketStream << byteArray;
            }
            else
                QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
        }
        else
            QMessageBox::critical(this,"QTCPClient","Not connected");
    }
    else
    {
        QDataStream socketStream(serv_socket);
        socketStream.setVersion(QDataStream::Qt_5_15);
        socketStream.startTransaction();
        socketStream>>receivedata;

        // stream startTransaction 실행 문제시 에러 표시 후 함수 종료

        qDebug()<<data;
        qDebug("\n");
        qDebug()<<from;
        qDebug("\n");
        qDebug()<<datatype;
        ui->menu->append(encodingdata);
    }
}

void bokpang_shop::on_accept_clicked()
{
    QPushButton* clickbtntemp = qobject_cast<QPushButton*>(sender());
    QString categori = clickbtntemp->objectName();
    if(serv_socket)
    {
        if(serv_socket->isOpen())
        {
            QString choose = categori;

            QDataStream socketStream(serv_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);
            QByteArray header;
            header.prepend(QString("myID:%1,cliType:shop,cliChoose:basket,send:%2;").arg(myname).arg(categori.size()).toUtf8());
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


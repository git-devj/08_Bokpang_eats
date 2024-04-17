#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QMetaType>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpServer* bok_server;
    QSet<QTcpSocket*> bok_clSKT;
    QString cliID;
    QString shopID;
    QByteArray fromcli;
    QString header;
    QString fromcliType;
    QString fromcliChoose;
    QMap<QTcpSocket* ,QString> socklist;
    QMap<QTcpSocket* ,QString> shopsocklist;
    QTcpSocket* socket;
    QTcpSocket* shop;
    QStringList insert{5};
    QString cusID;
     // 메시지 보내는 함수
    void sendtocli(QTcpSocket* socket);
    void checkID(QTcpSocket* socket);
    void checkPH(QTcpSocket* socket);
    void checkEMAIL(QTcpSocket* socket);
    void SIGNUP();
    void findID();
    void findPW();
    void SIGNIN();

signals:
    void signal_newmessage(QString);

private slots:
    void touser();
    void newcli_connection();
    void cli_manage(QTcpSocket* socket);
    void fromcli_data();
    void sendcategoribtn_clicked();
    void sendcategori_data(QTcpSocket* socket);
    void sendclidata(QTcpSocket* socket);
    void sendmenu_data(QTcpSocket* socket);
    void sendshop_data(QTcpSocket* socket);
    void slot_displaymsg(const QString& str); // 메시지 표시 슬롯
    void slot_readsock(); // 소켓을 읽기 슬롯
    void send_msg(QTcpSocket* sock);
    void on_send_pbtn_clicked();
    void toShop();
};

#endif // WIDGET_H

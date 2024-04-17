#ifndef BOKPANG_USER_H
#define BOKPANG_USER_H

#include <QResource>
#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QFileInfo>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTableWidget>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QLabel>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class Bokpang_user;
}
QT_END_NAMESPACE

class Bokpang_user : public QWidget
{
    Q_OBJECT

public:
    Bokpang_user(QWidget *parent = nullptr);
    ~Bokpang_user();

private slots:
    void on_categoribtn_clicked();

    void on_shopbtn1_clicked();

    void showmenu(const QString& str);


    void on_shopbtn2_clicked();

    void on_shopbtn3_clicked();

    void on_shopbtn4_clicked();

    void startbtn_clicked();

    void slotdebugmessage(const QString& str);

    void receiveclidata();


    void on_VoC_pbtn_clicked();

    void on_send_pbtn_clicked();
    void slot_read_sock();
    void slot_displaymsg(const QString& str);
    void on_id_double_chk_pbtn_clicked();
    void checkID();

    void on_ph_double_chk_pbtn_clicked();
    void checkPH();

    void on_email_double_chk_pbtn_clicked();
    void checkEMAIL();

    void on_signupbtn__clicked();


    void on_find_pw_pbtn_2_clicked();

    void on_find_id_pbtn_2_clicked();

    void on_login_pbtn_clicked();

    void on_find_id_pbtn_clicked();

    void on_find_pw_pbtn_clicked();

    void on_sign_up_pbtn_clicked();

    void on_pushButton_clicked();

    void page_basket_pbtn_enable();
    void basket_back_pbtn_clicked();
    void menu_pbtn_1_clicked();
    void menu_pbtn_2_clicked();
    void menu_pbtn_3_clicked();
    void menu_pbtn_4_clicked();
    void basket_order_pbtn_clicked();

    void on_basket_back_pbtn_2_clicked();

private:
    Ui::Bokpang_user *ui;
    QString categori;
    QStringList shop{4};
    int shopselect;
    QStringList menulist{4};
    QStringList menunamelist{4};
    QStringList menupricelist{4};
    QTcpSocket* serv_socket;
    QByteArray receivedata;
    QString myname;
    QString encodingdata;
    int basketprice=0;
    QString basketmenu;
    int setting=0;
    QString menu_1, menu_2, menu_3, menu_4;
    int row = 0;
    int column = 0;

signals:
    void signal_newMessage(QString);
    void signal_newID();
};
#endif // BOKPANG_USER_H

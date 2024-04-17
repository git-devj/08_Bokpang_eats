#ifndef BOKPANG_SHOP_H
#define BOKPANG_SHOP_H

#include <QWidget>
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
class bokpang_shop;
}
QT_END_NAMESPACE

class bokpang_shop : public QWidget
{
    Q_OBJECT

public:
    bokpang_shop(QWidget *parent = nullptr);
    ~bokpang_shop();

private slots:
    void receivebasket();

    void on_accept_clicked();

private:
    Ui::bokpang_shop *ui;
    QTcpSocket* serv_socket;
    QByteArray receivedata;
    QString myname;
    QString cusID;


};
#endif // BOKPANG_SHOP_H

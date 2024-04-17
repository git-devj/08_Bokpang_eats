/********************************************************************************
** Form generated from reading UI file 'bokpang_shop.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOKPANG_SHOP_H
#define UI_BOKPANG_SHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bokpang_shop
{
public:
    QTextEdit *menu;
    QPushButton *accept;
    QPushButton *refuse;

    void setupUi(QWidget *bokpang_shop)
    {
        if (bokpang_shop->objectName().isEmpty())
            bokpang_shop->setObjectName("bokpang_shop");
        bokpang_shop->resize(800, 600);
        bokpang_shop->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        menu = new QTextEdit(bokpang_shop);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(80, 30, 621, 421));
        accept = new QPushButton(bokpang_shop);
        accept->setObjectName("accept");
        accept->setGeometry(QRect(80, 480, 271, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("\353\202\230\353\210\224\354\212\244\355\200\230\354\226\264")});
        font.setPointSize(18);
        accept->setFont(font);
        accept->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(170, 255, 127);"));
        refuse = new QPushButton(bokpang_shop);
        refuse->setObjectName("refuse");
        refuse->setGeometry(QRect(400, 480, 301, 71));
        refuse->setFont(font);
        refuse->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 127, 127);"));

        retranslateUi(bokpang_shop);
        QObject::connect(refuse, SIGNAL(clicked()), bokpang_shop, SLOT(on_accept_clicked()));

        QMetaObject::connectSlotsByName(bokpang_shop);
    } // setupUi

    void retranslateUi(QWidget *bokpang_shop)
    {
        bokpang_shop->setWindowTitle(QCoreApplication::translate("bokpang_shop", "bokpang_shop", nullptr));
        accept->setText(QCoreApplication::translate("bokpang_shop", "\354\212\271\354\235\270", nullptr));
        refuse->setText(QCoreApplication::translate("bokpang_shop", "\352\261\260\354\240\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bokpang_shop: public Ui_bokpang_shop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOKPANG_SHOP_H

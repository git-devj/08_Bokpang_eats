/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLineEdit *tell_lineEdit;
    QComboBox *receiver_sel_comboBox;
    QPushButton *send_pbtn;
    QTextEdit *comm_textEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(637, 600);
        Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tell_lineEdit = new QLineEdit(Widget);
        tell_lineEdit->setObjectName("tell_lineEdit");
        tell_lineEdit->setGeometry(QRect(10, 550, 501, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\353\202\230\353\210\224\354\212\244\355\200\230\354\226\264")});
        font.setPointSize(14);
        font.setBold(false);
        tell_lineEdit->setFont(font);
        receiver_sel_comboBox = new QComboBox(Widget);
        receiver_sel_comboBox->setObjectName("receiver_sel_comboBox");
        receiver_sel_comboBox->setGeometry(QRect(10, 500, 221, 31));
        receiver_sel_comboBox->setFont(font);
        receiver_sel_comboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(152, 152, 152);"));
        send_pbtn = new QPushButton(Widget);
        send_pbtn->setObjectName("send_pbtn");
        send_pbtn->setGeometry(QRect(530, 550, 91, 31));
        send_pbtn->setFont(font);
        send_pbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 186, 180);"));
        comm_textEdit = new QTextEdit(Widget);
        comm_textEdit->setObjectName("comm_textEdit");
        comm_textEdit->setGeometry(QRect(10, 10, 611, 481));
        comm_textEdit->setFont(font);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        send_pbtn->setText(QCoreApplication::translate("Widget", "\353\263\264\353\202\264\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

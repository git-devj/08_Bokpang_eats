#include "bokpang_user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bokpang_user w;
    w.setWindowTitle("복스이츠");
    w.show();
    return a.exec();
}

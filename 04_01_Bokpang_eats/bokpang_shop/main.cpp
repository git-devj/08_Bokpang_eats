#include "bokpang_shop.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bokpang_shop w;

    w.setWindowTitle("매장 클라이언트");
    w.show();
    return a.exec();
}

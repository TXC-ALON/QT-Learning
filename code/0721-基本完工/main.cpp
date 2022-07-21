#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("路径设计"); // 此处写应用程序在标题栏上显示的名称
    w.show();
    return a.exec();
}

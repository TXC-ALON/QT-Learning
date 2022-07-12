#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include"widget.h"
#include<iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionDrawbut_triggered()
{
    Widget* dWidget = new Widget(this,this);
    dWidget->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    dWidget->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");
    dWidget->setWindowFlag(Qt::Window,true);
    dWidget->setWindowOpacity(1);

    dWidget->show(); //在单独的窗口中显示
}

void MainWindow::on_DrawButton_clicked()
{
    Widget* dWidget = new Widget(this,this);
    dWidget->PrintAllPara();
}

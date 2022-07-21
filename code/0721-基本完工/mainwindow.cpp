#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include"widget.h"
#include<iostream>
#include<QFileDialog>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel * tag = new QLabel("Version 1.0.0");
    ui->statusBar->addWidget(tag);
}

MainWindow::~MainWindow()
{
    delete ui;

}




void MainWindow::on_DrawButton_clicked()
{
    Widget* dWidget = new Widget(this,this);
    dWidget->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    dWidget->setWindowTitle("绘图演示");
    dWidget->setWindowFlag(Qt::Window,true);
    dWidget->setWindowOpacity(1);
    dWidget->show(); //在单独的窗口中显示
}



void MainWindow::on_actSave_triggered()
{
    Widget* dWidget = new Widget(this,this);
    QString curPath=QApplication::applicationDirPath()+"/Path.txt";
    std::cout<<curPath.toStdString().data()<<std::endl;
    dWidget->MakeTxt(curPath);
    delete dWidget;
}

void MainWindow::on_actSaveOtherPlace_triggered()
{
    Widget* dWidget = new Widget(this,this);
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),"/Path",tr("Text File(*.txt)"));
    if(fileName == "")
    {
            return;
    }
    dWidget->MakeTxt(fileName);
    delete dWidget;
}

//void MainWindow::on_actOpen_triggered()
//{
//    QFileDialog fileDialog;
//    QString fileName = fileDialog.getOpenFileName(this,tr("Open File"),"/Path",tr("Text File(*.txt)"));
//    QFile file(fileName);
//        //重新打开文件，对文件进行读操作
//        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
//            qDebug()<<"文件打开失败";
//        }
//        //每次都去文件中的一行，然后输出读取到的字符串
//        char * str = new char[1000];
//        qint64 readNum = file.readLine(str,1000);
//        //当读取出现错误（返回 -1）或者读取到的字符数为 0 时，结束读取
//        while((readNum !=0) && (readNum != -1)){
//            qDebug() << str;
//            readNum = file.readLine(str,100);
//        }
//}


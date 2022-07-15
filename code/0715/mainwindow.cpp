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
    MyLayer = LayerCom(
                ui->RouteType->currentIndex(),
                false,//是否隔行
                false, // 是否从内向外
                ui->TiltAngle->value(),//倾斜角
                QPointF(ui->BaseMidPointX->value(),ui->BaseMidPointY->value()),
                ui->RotateAngle->value(),
                ui->LayerSliceThickness->value(),//激光切片层厚
                ui->sheetThickness->value(),//薄片厚度
                ui->sheetWidth->value(),//薄片宽度
                ui->sheetHeight->value(),//薄片高度
                ui->BaseLayerNum->value(),//基台层数
                ui->TreeVeinDif->value(), //树形筋间距
                ui->ExtendedContourFillSpace->value(), //拓展轮廓间距
                ui->ContourFillSpace->value(),   //轮廓和填充间距
                ui->FillSpace->value(),  //填充间距
                ui->ExtendedContourPower->value(), //拓展轮廓功率
                ui->ExtendedContourSpeed->value(), //拓展轮廓速度
                ui->ContourPower->value(), //轮廓功率
                ui->ContourSpeed->value(), //轮廓速度
                ui->FillPower->value(), //填充功率
                ui->FillSpeed->value() //填充速度
                );
    std::cout<<"填充间距 "<<MyLayer.FillSpace<<std::endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionDrawbut_triggered()
{
    Widget* dWidget = new Widget(this,this);
    dWidget->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    dWidget->setWindowTitle("绘图演示");
    dWidget->setWindowFlag(Qt::Window,true);
    dWidget->setWindowOpacity(1);
    dWidget->show(); //在单独的窗口中显示
}

void MainWindow::on_DrawButton_clicked()
{
    Widget* dWidget = new Widget(this,this);
    dWidget->PrintAllPara();
}

void MainWindow::on_actSave_triggered()
{
    Widget* dWidget = new Widget(this,this);
    dWidget->MakeTxt();
}

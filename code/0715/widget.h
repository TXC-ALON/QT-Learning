#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "objects.h"
#include <QFile>
#include <QDebug>
#include <QTextCodec>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
public:
    Widget(QWidget *parent,MainWindow *tt){
        MW = tt;
        bool IF_Interlaced = false;
        if(MW->ui->IF_Interlaced->checkState() == 2){
            IF_Interlaced = true;
        }else{
            IF_Interlaced = false;
        }
        bool IF_I2O = false;
        if(MW->ui->IF_I2O->checkState() == 2){
            IF_I2O = true;
        }else{
            IF_I2O = false;
        }

//        LayerCom tMyLayer(
//                MW->ui->RouteType->currentIndex(),
//                IF_Interlaced,//是否隔行
//                IF_I2O, // 是否从内向外
//                MW->ui->TiltAngle->value(),//倾斜角
//                QPointF(MW->ui->BaseMidPointX->value(),MW->ui->BaseMidPointY->value()),
//                MW->ui->RotateAngle->value(),
//                MW->ui->LayerSliceThickness->value(),//激光切片层厚
//                MW->ui->sheetThickness->value(),//薄片厚度
//                MW->ui->sheetWidth->value(),//薄片宽度
//                MW->ui->sheetHeight->value(),//薄片高度
//                MW->ui->BaseLayerNum->value(),//基台层数
//                MW->ui->TreeVeinDif->value(), //树形筋间距
//                MW->ui->ExtendedContourFillSpace->value(), //拓展轮廓间距
//                MW->ui->ContourFillSpace->value(),   //轮廓和填充间距
//                MW->ui->FillSpace->value(),  //填充间距
//                MW->ui->ExtendedContourPower->value(), //拓展轮廓功率
//                MW->ui->ExtendedContourSpeed->value(), //拓展轮廓速度
//                MW->ui->ContourPower->value(), //轮廓功率
//                MW->ui->ContourSpeed->value(), //轮廓速度
//                MW->ui->FillPower->value(), //填充功率
//                MW->ui->FillSpeed->value() //填充速度
//                );
        std::cout<<"**********************************************"<<std::endl;
        std::cout<<"当前路径类型为 "<<MW->ui->RouteType->currentIndex()<<std::endl;
        std::cout<<"是否隔行 "<<MW->ui->IF_Interlaced->checkState()<<std::endl;
        std::cout<<"从内到外 "<<MW->ui->IF_I2O->checkState()<<std::endl;
        std::cout<<"树筋间间距 "<<MW->ui->TreeVeinDif->value()<<std::endl;
        std::cout<<"薄片层厚 "<<MW->ui->sheetThickness->value()<<std::endl;
        std::cout<<"薄片宽度 "<<MW->ui->sheetWidth->value()<<std::endl;
        std::cout<<"薄片高度 "<<MW->ui->sheetHeight->value()<<std::endl;
        std::cout<<"激光切片厚度 "<<MW->ui->LayerSliceThickness->value()<<std::endl;
        std::cout<<"基台附加层数 "<<MW->ui->BaseLayerNum->value()<<std::endl;
        std::cout<<"薄片倾斜角 "<<MW->ui->TiltAngle->value()<<std::endl;
        std::cout<<"薄片旋转角 "<<MW->ui->RotateAngle->value()<<std::endl;
        std::cout<<"中心点坐标 ("<<MW->ui->BaseMidPointX->value();
        std::cout<<" , "<<MW->ui->BaseMidPointY->value()<<")"<<std::endl;
        std::cout<<"拓展轮廓间距 "<<MW->ui->ExtendedContourFillSpace->value()<<std::endl;
        std::cout<<"轮廓间距 "<<MW->ui->ContourFillSpace->value()<<std::endl;
        std::cout<<"填充间距 "<<MW->ui->FillSpace->value()<<std::endl;
        std::cout<<"拓展轮廓功率 "<<MW->ui->ExtendedContourPower->value()<<std::endl;
        std::cout<<"轮廓填充功率 "<<MW->ui->ContourPower->value()<<std::endl;
        std::cout<<"填充功率 "<<MW->ui->FillPower->value()<<std::endl;
        std::cout<<"拓展轮廓速率 "<<MW->ui->ExtendedContourSpeed->value()<<std::endl;
        std::cout<<"轮廓速率 "<<MW->ui->ContourSpeed->value()<<std::endl;
        std::cout<<"填充速率 "<<MW->ui->FillSpeed->value()<<std::endl;
        std::cout<<"---------------------------------------------"<<std::endl;

    }
    Widget(QWidget *parent);
    ~Widget();
    MainWindow *MW;
    void PrintAllPara();
    void PrintLayer();
    void MakeTxt();
    LayerCom tMyLayer;
private:
    void myDrawGradient();
    void myLines();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

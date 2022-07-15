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
//                IF_Interlaced,//�Ƿ����
//                IF_I2O, // �Ƿ��������
//                MW->ui->TiltAngle->value(),//��б��
//                QPointF(MW->ui->BaseMidPointX->value(),MW->ui->BaseMidPointY->value()),
//                MW->ui->RotateAngle->value(),
//                MW->ui->LayerSliceThickness->value(),//������Ƭ���
//                MW->ui->sheetThickness->value(),//��Ƭ���
//                MW->ui->sheetWidth->value(),//��Ƭ���
//                MW->ui->sheetHeight->value(),//��Ƭ�߶�
//                MW->ui->BaseLayerNum->value(),//��̨����
//                MW->ui->TreeVeinDif->value(), //���ν���
//                MW->ui->ExtendedContourFillSpace->value(), //��չ�������
//                MW->ui->ContourFillSpace->value(),   //�����������
//                MW->ui->FillSpace->value(),  //�����
//                MW->ui->ExtendedContourPower->value(), //��չ��������
//                MW->ui->ExtendedContourSpeed->value(), //��չ�����ٶ�
//                MW->ui->ContourPower->value(), //��������
//                MW->ui->ContourSpeed->value(), //�����ٶ�
//                MW->ui->FillPower->value(), //��书��
//                MW->ui->FillSpeed->value() //����ٶ�
//                );
        std::cout<<"**********************************************"<<std::endl;
        std::cout<<"��ǰ·������Ϊ "<<MW->ui->RouteType->currentIndex()<<std::endl;
        std::cout<<"�Ƿ���� "<<MW->ui->IF_Interlaced->checkState()<<std::endl;
        std::cout<<"���ڵ��� "<<MW->ui->IF_I2O->checkState()<<std::endl;
        std::cout<<"������� "<<MW->ui->TreeVeinDif->value()<<std::endl;
        std::cout<<"��Ƭ��� "<<MW->ui->sheetThickness->value()<<std::endl;
        std::cout<<"��Ƭ��� "<<MW->ui->sheetWidth->value()<<std::endl;
        std::cout<<"��Ƭ�߶� "<<MW->ui->sheetHeight->value()<<std::endl;
        std::cout<<"������Ƭ��� "<<MW->ui->LayerSliceThickness->value()<<std::endl;
        std::cout<<"��̨���Ӳ��� "<<MW->ui->BaseLayerNum->value()<<std::endl;
        std::cout<<"��Ƭ��б�� "<<MW->ui->TiltAngle->value()<<std::endl;
        std::cout<<"��Ƭ��ת�� "<<MW->ui->RotateAngle->value()<<std::endl;
        std::cout<<"���ĵ����� ("<<MW->ui->BaseMidPointX->value();
        std::cout<<" , "<<MW->ui->BaseMidPointY->value()<<")"<<std::endl;
        std::cout<<"��չ������� "<<MW->ui->ExtendedContourFillSpace->value()<<std::endl;
        std::cout<<"������� "<<MW->ui->ContourFillSpace->value()<<std::endl;
        std::cout<<"����� "<<MW->ui->FillSpace->value()<<std::endl;
        std::cout<<"��չ�������� "<<MW->ui->ExtendedContourPower->value()<<std::endl;
        std::cout<<"������书�� "<<MW->ui->ContourPower->value()<<std::endl;
        std::cout<<"��书�� "<<MW->ui->FillPower->value()<<std::endl;
        std::cout<<"��չ�������� "<<MW->ui->ExtendedContourSpeed->value()<<std::endl;
        std::cout<<"�������� "<<MW->ui->ContourSpeed->value()<<std::endl;
        std::cout<<"������� "<<MW->ui->FillSpeed->value()<<std::endl;
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

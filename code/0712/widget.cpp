#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include "layers.h"
#include <algorithm>
#include "ui_mainwindow.h"
#include "mainwindow.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    this->resize(1200,800);
}



void PrintBox(Widget *t,bool If_gehang,bool IF_I2O){
    QPainter    painter(t);//创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=t->width(); //绘图区宽度
    int H=t->height(); //绘图区高度
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    //set the brush
    QBrush brush;
    painter.translate(W/2, H/2);
    painter.setBrush(brush);
    BoxPath test = BoxPath(If_gehang,IF_I2O,0.2,QPoint(0,0),2,5);
    QVector<QVector<QPointF>> GG = test.ComBoxPointArray;
    QPointF to_Point(0,0);
    double transradio = std::min(W/test.PathAreaLength,H/test.PathAreaWidth)-5;
    Q2Point_Trans(GG,to_Point,transradio);
    PrintTwoDimVector(GG);
    double dif = 1.0 / GG.size();
    std::cout<<dif<<std::endl;
    QColor qc;
    for(int i = 0; i<GG.size();i++){
        qc.setHslF(dif*i,1,0.5);
        pen.setColor(qc);
        painter.setPen(pen);
        painter.drawConvexPolygon(GG[i].begin(), GG[0].size());
    }
    QPointF LU = QPointF(-test.PathAreaLength/2*transradio+to_Point.x(),-test.PathAreaWidth/2*transradio+to_Point.y());
    QPointF RU = QPointF(test.PathAreaLength/2*transradio+to_Point.x(),-test.PathAreaWidth/2*transradio+to_Point.y());
    QLineF LR = QLineF(LU,RU);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(LR);
}
void PrintUniCursalLine(Widget *ths,bool If_gehang,bool IF_I2O){
    QPainter    painter(ths);//创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=ths->width(); //绘图区宽度
    int H=ths->height(); //绘图区高度
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    //set the brush
    QBrush brush;
    painter.translate(W/2, H/2);
    painter.setBrush(brush);
    UniCursalPath test = UniCursalPath(If_gehang,IF_I2O,0.2,QPoint(0,0),2,2);

    QVector<QVector<QPointF>> GG = test.ComUniCursalPointArray;
    QPointF to_Point(0,0);
    PrintTwoDimVector(GG);
    double transradio = std::min(W/test.PathAreaLength,H/test.PathAreaWidth)-5;
    Q2Point_Trans(GG,to_Point,transradio);
    std::cout<<"******************************"<<std::endl;
    PrintTwoDimVector(GG);
    QVector<QVector<QLineF>> Objects = BuildUpQ2PLines(GG,false);
    QColor qc;
    double dif = 1.0 / Objects.size();
    for(int i = 0; i<Objects.size();i++){
        qc.setHslF(dif*i,1,0.5);
        pen.setColor(qc);
        painter.setPen(pen);
        painter.drawLines(Objects[i]);
    }

    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(Objects[0][0]);

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(Objects[0][1]);

    /*
    QPointF LU = QPointF(-test.PathAreaLength/2*transradio+to_Point.x(),-test.PathAreaWidth/2*transradio+to_Point.y());
    QPointF RU = QPointF(test.PathAreaLength/2*transradio+to_Point.x(),-test.PathAreaWidth/2*transradio+to_Point.y());
    QLineF LR = QLineF(LU,RU);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(LR);
    */
}
void PrintCommonTree(Widget *ths,
                     bool    IF_Interlaced,//是否隔行
                     double  TypeTreeVeinDif, //树形筋间距
                     double  FillSpace,  //填充间距
                     QPointF  MidPoint,
                     double  PathAreaLength,    //填充轮廓范围长（这里其实是较小的一段）
                     double  PathAreaWidth){
    QPainter  painter(ths);//创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=ths->width(); //绘图区宽度
    int H=ths->height(); //绘图区高度
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    //set the brush
    QBrush brush;
    painter.translate(W/2, H/2);
    painter.setBrush(brush);
    CommonTreePath test(IF_Interlaced,
                        TypeTreeVeinDif, //树形筋间距
                        FillSpace,  //填充间距
                        MidPoint,
                        PathAreaLength,    //填充轮廓范围长（这里其实是较小的一段）
                        PathAreaWidth);    //填充轮廓范围宽);
    QVector<QVector<QPointF>> GG = test.ForestPointArray;
    QPointF to_Point(0,0);
    //PrintTwoDimVector(GG);
    double transradio = std::min(W/test.PathAreaLength,H/test.PathAreaWidth)-5;
    Q2Point_Trans(GG,to_Point,transradio);
    QVector<QVector<QLineF>> Objects = BuildUpQ2PLines(GG,true);
    QColor qc;
    double dif = 1.0 / Objects.size();
    std::cout<<Objects.size()<<std::endl;
    for(int i = 0; i<Objects.size();i++){
        qc.setHslF(dif*i,1,0.5);
        pen.setColor(qc);
        painter.setPen(pen);
        painter.drawLines(Objects[i]);
    }
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(Objects[0][0]);

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(Objects[0][1]);

}
void Widget::PrintAllPara()
{
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
    std::cout<<"轮廓间距 "<<MW->ui->ContourPower->value()<<std::endl;
    std::cout<<"填充间距 "<<MW->ui->FillPower->value()<<std::endl;
    std::cout<<"拓展轮廓速率 "<<MW->ui->ExtendedContourSpeed->value()<<std::endl;
    std::cout<<"轮廓速率 "<<MW->ui->ContourSpeed->value()<<std::endl;
    std::cout<<"填充速率 "<<MW->ui->FillSpeed->value()<<std::endl;
    std::cout<<"---------------------------------------------"<<std::endl;
}
void Widget::myLines()
{
    bool t = false;
    if(MW->ui->IF_Interlaced->checkState() == 0){
        t = false;
    }
    else{
        t = true;
    }
    SingleLayer();

//    PrintCommonTree(this,t,MW->ui->TypeTreeVeinDif->value(),MW->ui->FillSpace->value(),
//                    QPointF(MW->ui->BaseMidPointX->value(),MW->ui->BaseMidPointY->value()),
//                    2,
//                    2
//                    );
    //PrintBox(this,false,true);
    //PrintUniCursalLine(this,true,false);
}


void Widget::paintEvent(QPaintEvent *event)
{
    myLines();

}

Widget::~Widget()
{
    delete ui;
}

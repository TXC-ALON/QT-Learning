#include "widget.h"
#include "ui_widget.h"
#include    <QPainter>
#include "layers.h"
#include<algorithm>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    this->resize(1200,800);
}

void Q2Point_Move(QVector<QVector<QPointF>> &Q2P,QPointF des){
    for (unsigned int i = 0;i<Q2P.size();i++){
        for (unsigned int j = 0; j<Q2P[0].size();j++){
            Q2P[i][j].rx() += des.x();
            Q2P[i][j].ry() += des.y();
        }
    }

}
void Q2Point_Trans(QVector<QVector<QPointF>> &Q2P,QPointF des,double radio){

    for (unsigned int i = 0;i<Q2P.size();i++){
        for (unsigned int j = 0; j<Q2P[0].size();j++){
            Q2P[i][j].rx() = Q2P[i][j].rx()*radio + des.x();
            Q2P[i][j].ry() = Q2P[i][j].ry()*radio + des.y();
        }
    }
}
QVector<QVector<QLineF>> BuildUpQ2PLines(QVector<QVector<QPointF>> Q2P,bool IF_Tree){
    QVector<QVector<QLineF>> Objects;
    QVector<QLineF> Lines;
    if(IF_Tree){
        for(size_t i = 0;i<Q2P.size();i++){
            Lines.clear();
            for(size_t j = 0 ; j<Q2P[i].size()-1;j++){
                if(j == 1){
                    continue;
                }
                Lines.append(QLineF(Q2P[i][j],Q2P[i][j+1]));
            }
            Objects.append(Lines);
        }
    }
    else{
    for(size_t i = 0;i<Q2P.size();i++){
        Lines.clear();
        for(size_t j = 0 ; j<Q2P[i].size()-1;j++){
            Lines.append(QLineF(Q2P[i][j],Q2P[i][j+1]));
        }
        Objects.append(Lines);
    }
    }
    return Objects;
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
    UniCursalPath test = UniCursalPath(If_gehang,IF_I2O,0.2,QPoint(0,0),2,5);

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
void PrintCommonTree(Widget *ths,bool If_gehang){
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
    CommonTreePath test(If_gehang,0.3,0.2,QPointF(0,0),2,88);
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

void Widget::myLines()
{

    PrintCommonTree(this,false);
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

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
    QPainter    painter(t);//����QPainter����
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=t->width(); //��ͼ�����
    int H=t->height(); //��ͼ���߶�
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
    QPainter    painter(ths);//����QPainter����
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=ths->width(); //��ͼ�����
    int H=ths->height(); //��ͼ���߶�
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
                     bool    IF_Interlaced,//�Ƿ����
                     double  TypeTreeVeinDif, //���ν���
                     double  FillSpace,  //�����
                     QPointF  MidPoint,
                     double  PathAreaLength,    //���������Χ����������ʵ�ǽ�С��һ�Σ�
                     double  PathAreaWidth){
    QPainter  painter(ths);//����QPainter����
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=ths->width(); //��ͼ�����
    int H=ths->height(); //��ͼ���߶�
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
                        TypeTreeVeinDif, //���ν���
                        FillSpace,  //�����
                        MidPoint,
                        PathAreaLength,    //���������Χ����������ʵ�ǽ�С��һ�Σ�
                        PathAreaWidth);    //���������Χ��);
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
    std::cout<<"�������� "<<MW->ui->ContourPower->value()<<std::endl;
    std::cout<<"��书�� "<<MW->ui->FillPower->value()<<std::endl;
    std::cout<<"��չ�������� "<<MW->ui->ExtendedContourSpeed->value()<<std::endl;
    std::cout<<"�������� "<<MW->ui->ContourSpeed->value()<<std::endl;
    std::cout<<"������� "<<MW->ui->FillSpeed->value()<<std::endl;
    std::cout<<"---------------------------------------------"<<std::endl;
}

void Widget::PrintLayer()
{
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
    //LayerCom MyLayers = MW->MyLayer;
    LayerCom MyLayers(
                MW->ui->RouteType->currentIndex(),
                IF_Interlaced,//�Ƿ����
                IF_I2O, // �Ƿ��������
                MW->ui->TiltAngle->value(),//��б��
                QPointF(MW->ui->BaseMidPointX->value(),MW->ui->BaseMidPointY->value()),
                MW->ui->RotateAngle->value(),
                MW->ui->LayerSliceThickness->value(),//������Ƭ���
                MW->ui->sheetThickness->value(),//��Ƭ���
                MW->ui->sheetWidth->value(),//��Ƭ���
                MW->ui->sheetHeight->value(),//��Ƭ�߶�
                MW->ui->BaseLayerNum->value(),//��̨����
                MW->ui->TreeVeinDif->value(), //���ν���
                MW->ui->ExtendedContourFillSpace->value(), //��չ�������
                MW->ui->ContourFillSpace->value(),   //�����������
                MW->ui->FillSpace->value(),  //�����
                MW->ui->ExtendedContourPower->value(), //��չ��������
                MW->ui->ExtendedContourSpeed->value(), //��չ�����ٶ�
                MW->ui->ContourPower->value(), //��������
                MW->ui->ContourSpeed->value(), //�����ٶ�
                MW->ui->FillPower->value(), //��书��
                MW->ui->FillSpeed->value() //����ٶ�
            );

    //��ͼ����
    QPainter  painter(this);//����QPainter����
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=this->width(); //��ͼ�����
    int H=this->height(); //��ͼ���߶�
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    //set the brush
    QBrush brush;
    painter.translate(W/2, H/2);
    painter.setBrush(brush);


    QVector<QVector<QPointF>> GG = MyLayers.Layers[1];
    QVector<QPointF> ECP = MyLayers.ECPointArray[1];
    QVector<QPointF> CP = MyLayers.CPointArray[1];
    QPointF to_Point(0,0);
    QColor qc;

//    QVector<QVector<QLineF>> sObjects;
//    QVector<QLineF> sLines;
//    for(size_t i = 0;i<GG.size();i++){
//        sLines.clear();
//        for(size_t j = 0 ; j<GG[i].size()-1;j++){
//            sLines.append(QLineF(GG[i][j],GG[i][j+1]));
//        }
//        sObjects.append(sLines);
//    }

    //PrintTwoDimVector(GG);
    double transradio = std::min(W/MyLayers.SingleLayerLength,H/MyLayers.SingleLayerWidth)-5;
    Q2Point_Trans(GG,to_Point,transradio);
    QPoint_Trans(ECP,to_Point,transradio);
    QPoint_Trans(CP,to_Point,transradio);

    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawConvexPolygon(ECP.begin(), ECP.size());
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawConvexPolygon(CP.begin(), CP.size());

    bool IF_tree = false;
    if(MW->ui->RouteType->currentIndex()<2){
        IF_tree = true;
    }
    if(MW->ui->RouteType->currentIndex()==2){
        double dif = 1.0 / GG.size();
        for(int i = 0; i<GG.size();i++){
            qc.setHslF(dif*i,1,0.5);
            pen.setColor(qc);
            painter.setPen(pen);
            painter.drawConvexPolygon(GG[i].begin(), GG[i].size());
        }

        return ;
    }



    QVector<QVector<QLineF>> Objects = BuildUpQ2PLines(GG,IF_tree);

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

void Widget::MakeTxt()
{
    QFile file("D:/test/demo.txt");
    //���ļ�����д����
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"�ļ���ʧ��";
    }
    //���ļ���д�������ַ���
    QTextStream stream(&file);
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec); //���������������
    stream.setCodec("UTF-8");
    //stream.setEncoding (QStringConverter::System);
    //stream.setCodec(QTextCodec::codecForName("GBK"));
    file.write("#�������ڹ��ղ��Ե��ļ�ģ�壬֧������߶Ρ����ߡ�Բ��·��������#������ע��/ע��\n");
    stream <<"Article"<<endl;
    stream <<"Thickness,"+QString::number(MW->ui->sheetThickness->value(), 10, 3)<<endl;
    stream << QString("Xmin," + QString::number(MW->ui->ContourPower->value(), 10, 4)) << endl;
    stream << QString("Ymin," + QString::number(MW->ui->ContourPower->value(), 10, 4)) << endl;
    stream << QString("Zmin," + QString::number(MW->ui->ContourPower->value(), 10, 4)) << endl;
    stream << QString("Xmax," + QString::number(MW->ui->ContourPower->value(), 10, 4)) << endl;
    stream << QString("Ymax," + QString::number(MW->ui->ContourPower->value(), 10, 4)) << endl;
    stream << QString("Zmax," + QString::number(MW->ui->ContourPower->value(), 10, 4)) << endl;
    stream << QString("LayerNumber," + QString::number(MW->MyLayer.SingleLayerNum, 10, 4)) << endl;
    stream << QString("#hatch_space," + QString::number(MW->MyLayer.FillSpace, 10, 4)) << endl;


    //�ر��ļ�
    file.close();
    //���´��ļ������ļ����ж�����
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"�ļ���ʧ��";
    }
    //ÿ�ζ�ȥ�ļ��е�һ�У�Ȼ�������ȡ�����ַ���
    char * str = new char[100];
    qint64 readNum = file.readLine(str,100);
    //����ȡ���ִ��󣨷��� -1�����߶�ȡ�����ַ���Ϊ 0 ʱ��������ȡ
    while((readNum !=0) && (readNum != -1)){
        qDebug() << str;
        readNum = file.readLine(str,100);
    }
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


     PrintLayer();
}


void Widget::paintEvent(QPaintEvent *event)
{
    myLines();
}

Widget::~Widget()
{
    delete ui;
}

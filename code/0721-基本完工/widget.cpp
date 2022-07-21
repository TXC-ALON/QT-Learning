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
    std::cout<<"轮廓功率 "<<MW->ui->ContourPower->value()<<std::endl;
    std::cout<<"填充功率 "<<MW->ui->FillPower->value()<<std::endl;
    std::cout<<"拓展轮廓速率 "<<MW->ui->ExtendedContourSpeed->value()<<std::endl;
    std::cout<<"轮廓速率 "<<MW->ui->ContourSpeed->value()<<std::endl;
    std::cout<<"填充速率 "<<MW->ui->FillSpeed->value()<<std::endl;
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
                IF_Interlaced,//是否隔行
                IF_I2O, // 是否从内向外
                MW->ui->TiltAngle->value(),//倾斜角
                QPointF(MW->ui->BaseMidPointX->value(),MW->ui->BaseMidPointY->value()),
                MW->ui->RotateAngle->value(),
                MW->ui->LayerSliceThickness->value(),//激光切片层厚
                MW->ui->sheetThickness->value(),//薄片厚度
                MW->ui->sheetWidth->value(),//薄片宽度
                MW->ui->sheetHeight->value(),//薄片高度
                MW->ui->BaseLayerNum->value(),//基台层数
                MW->ui->TreeVeinDif->value(), //树形筋间距
                MW->ui->ExtendedContourFillSpace->value(), //拓展轮廓间距
                MW->ui->ContourFillSpace->value(),   //轮廓和填充间距
                MW->ui->FillSpace->value(),  //填充间距
                MW->ui->ExtendedContourPower->value(), //拓展轮廓功率
                MW->ui->ExtendedContourSpeed->value(), //拓展轮廓速度
                MW->ui->ContourPower->value(), //轮廓功率
                MW->ui->ContourSpeed->value(), //轮廓速度
                MW->ui->FillPower->value(), //填充功率
                MW->ui->FillSpeed->value() //填充速度
            );
    MW->ui->plainTextEdit->clear();
    MW->ui->plainTextEdit->appendPlainText(QString("总层数为 " + QString::number(MyLayers.SingleLayerNum, 10, 0)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("单层的短边长 " + QString::number(MyLayers.SingleLayerLength, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("单层的长边长 " + QString::number(MyLayers.SingleLayerWidth, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前层数 " + QString::number(MW->ui->CurLayNum->value(), 10, 0)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前层数中心点位置: x " + QString::number(MyLayers.BaseMidPointArray[MW->ui->CurLayNum->value()-1].x(), 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前层数中心点位置: y " + QString::number(MyLayers.BaseMidPointArray[MW->ui->CurLayNum->value()-1].y(), 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前X_min 为 " + QString::number(MyLayers.x_min, 10, 4)).toUtf8()+QString(" X_max 为 " + QString::number(MyLayers.x_max, 10, 4)).toUtf8()+QString(" x方向差值为 " + QString::number(MyLayers.x_max-MyLayers.x_min, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前Y_min 为 " + QString::number(MyLayers.y_min, 10, 4)).toUtf8()+QString(" Y_max 为 " + QString::number(MyLayers.y_max, 10, 4)).toUtf8()+QString(" y方向差值为 " + QString::number(MyLayers.y_max-MyLayers.y_min, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前Z_min 为 " + QString::number(MyLayers.z_min, 10, 4)).toUtf8()+QString(" Z_max 为 " + QString::number(MyLayers.z_max, 10, 4)).toUtf8()+QString(" z方向差值为 " + QString::number(MyLayers.z_max-MyLayers.z_min, 10, 4)).toUtf8());

    MW->ui->plainTextEdit->show();
    //绘图设置
    QPainter  painter(this);//创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    int W=this->width(); //绘图区宽度
    int H=this->height(); //绘图区高度
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    //set the brush
    QBrush brush;
    painter.translate(W/2, H/2);
    painter.setBrush(brush);


    QVector<QVector<QPointF>> GG = MyLayers.Layers[MW->ui->CurLayNum->value()];
    QVector<QPointF> ECP = MyLayers.ECPointArray[MW->ui->CurLayNum->value()];
    QVector<QPointF> CP = MyLayers.CPointArray[MW->ui->CurLayNum->value()];
    QPointF to_Point(0,0);
    QColor qc;
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

void Widget::MakeTxt(QString filename)
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
    LayerCom MyLayers_txt(
                MW->ui->RouteType->currentIndex(),
                IF_Interlaced,//是否隔行
                IF_I2O, // 是否从内向外
                MW->ui->TiltAngle->value(),//倾斜角
                QPointF(MW->ui->BaseMidPointX->value(),MW->ui->BaseMidPointY->value()),
                MW->ui->RotateAngle->value(),
                MW->ui->LayerSliceThickness->value(),//激光切片层厚
                MW->ui->sheetThickness->value(),//薄片厚度
                MW->ui->sheetWidth->value(),//薄片宽度
                MW->ui->sheetHeight->value(),//薄片高度
                MW->ui->BaseLayerNum->value(),//基台层数
                MW->ui->TreeVeinDif->value(), //树形筋间距
                MW->ui->ExtendedContourFillSpace->value(), //拓展轮廓间距
                MW->ui->ContourFillSpace->value(),   //轮廓和填充间距
                MW->ui->FillSpace->value(),  //填充间距
                MW->ui->ExtendedContourPower->value(), //拓展轮廓功率
                MW->ui->ExtendedContourSpeed->value(), //拓展轮廓速度
                MW->ui->ContourPower->value(), //轮廓功率
                MW->ui->ContourSpeed->value(), //轮廓速度
                MW->ui->FillPower->value(), //填充功率
                MW->ui->FillSpeed->value() //填充速度
            );

    QTime filetimedebuge;//声明一个时钟对象
    filetimedebuge.start();//开始计时

    QFile file(filename);
    //对文件进行写操作
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        MW->ui->plainTextEdit->clear();
        MW->ui->plainTextEdit->appendPlainText(QString("文件打开失败!"));
        MW->ui->plainTextEdit->show();
    }
    MW->ui->plainTextEdit->clear();
    MW->ui->plainTextEdit->appendPlainText(QString("准备开始生成文件 保存位置为: ")+QString(filename));

    //向文件中写入两行字符串
    QTextStream stream(&file);
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec); //解决汉字乱码问题
    stream.setCodec("UTF-8");
    //stream.setEncoding (QStringConverter::System);
    //stream.setCodec(QTextCodec::codecForName("GBK"));
    file.write("#这是用于工艺测试的文件模板，支持填充线段、折线、圆弧路径。行首#用于行注释/注销\n");
    file.write("#文件头，打印件信息\n");
    stream <<"Article"<<endl;
    stream <<"Thickness,"+QString::number(MW->ui->LayerSliceThickness->value(), 10, 3)<<endl;
    stream << QString("Xmin," + QString::number(MyLayers_txt.x_min, 10, 4)) << endl;
    stream << QString("Ymin," + QString::number(MyLayers_txt.y_min, 10, 4)) << endl;
    stream << QString("Zmin," + QString::number(MyLayers_txt.z_min, 10, 4)) << endl;
    stream << QString("Xmax," + QString::number(MyLayers_txt.x_max, 10, 4)) << endl;
    stream << QString("Ymax," + QString::number(MyLayers_txt.y_max, 10, 4)) << endl;
    stream << QString("Zmax," + QString::number(MyLayers_txt.z_max, 10, 4)) << endl;
    stream << QString("LayerNumber," + QString::number(MyLayers_txt.SingleLayerNum, 10, 4)) << endl;
    file.write("#这是工艺参数：\n");
    stream << QString("#hatch_space," + QString::number(MyLayers_txt.FillSpace, 10, 4)) << endl;
    stream << QString("#fill_power," + QString::number(MyLayers_txt.FillPower, 10, 4)) << endl;
    stream << QString("#fill_speed," + QString::number(MyLayers_txt.FillSpace, 10, 4)) << endl;
    stream << QString("#contour_power," + QString::number(MyLayers_txt.ContourPower, 10, 4)) << endl;
    stream << QString("#contour_speed," + QString::number(MyLayers_txt.ContourSpeed, 10, 4)) << endl;
    stream << QString("#extra_contour_power," + QString::number(MyLayers_txt.ExtendedContourPower, 10, 4)) << endl;
    stream << QString("#extra_contour_speed," + QString::number(MyLayers_txt.ExtendedContourSpeed, 10, 4)) << endl;
    file.write("#打印件轨迹信息\n");
    for(unsigned int i = 0; i < MyLayers_txt.SingleLayerNum;i++){
    file.write("#Layer,层开始:");
    stream <<i<<endl;
    stream <<"Layer"<<endl;
    //输出轮廓
    stream <<"#ContourSpace"<<endl;
    stream <<"#Layer,Polygon"<<endl;
    stream << QString("Power," + QString::number(MyLayers_txt.ContourPower, 10, 4)) << endl;
    stream << QString("Speed," + QString::number(MyLayers_txt.ContourSpeed, 10, 4)) << endl;
    stream <<"Polygon,";
    for(int j = 0; j < MyLayers_txt.CPointArray[i].size();j++){
        stream << QString(QString::number(MyLayers_txt.CPointArray[i][j].x(), 10, 4) +","+QString::number(MyLayers_txt.CPointArray[i][j].y(), 10, 4)+",");
    }
    stream << QString::number(MyLayers_txt.CPointArray[i][0].x(), 10, 4) +","+QString::number(MyLayers_txt.CPointArray[i][0].y());
    stream <<endl;
    //如果有，那么输出拓展轮廓
    if(MyLayers_txt.ExtendedContourSpace > DBL_EPSILON){
        stream <<"#ExtendedContourSpace"<<endl;
        stream <<"#Layer,Polygon"<<endl;
        stream << QString("Power," + QString::number(MyLayers_txt.ExtendedContourPower, 10, 4)) << endl;
        stream << QString("Speed," + QString::number(MyLayers_txt.ExtendedContourSpeed, 10, 4)) << endl;
        stream <<"Polygon,";
        for(int j = 0; j < MyLayers_txt.ECPointArray[i].size();j++){
            stream << QString::number(MyLayers_txt.ECPointArray[i][j].x(), 10, 4) +","+QString::number(MyLayers_txt.ECPointArray[i][j].y(), 10, 4)+",";
            }
        stream << QString::number(MyLayers_txt.ECPointArray[i][0].x(), 10, 4) +","+QString::number(MyLayers_txt.ECPointArray[i][0].y());
        stream <<endl;
    }
    //输出填充路径
    stream <<"#FillSpace"<<endl;
    if(MyLayers_txt.Type == 0){
        stream <<"#Layer,Segment"<<endl;
        stream << QString("Power," + QString::number(MyLayers_txt.FillPower, 10, 4)) << endl;
        stream << QString("Speed," + QString::number(MyLayers_txt.FillSpeed, 10, 4)) << endl;
        for(int j = 0; j< MyLayers_txt.Layers[i].size();j++){
            for(int k = 0;k<MyLayers_txt.Layers[i][j].size();k+=2){
                stream << "Segment,"<<QString::number(MyLayers_txt.Layers[i][j][k].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k].y(), 10, 4);
                stream << ","+QString::number(MyLayers_txt.Layers[i][j][k+1].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k+1].y(), 10, 4) <<endl;
            stream <<endl;
            }
        }
    }
    if(MyLayers_txt.Type == 1){
        stream <<"#Layer,Segment"<<endl;
        stream << QString("Power," + QString::number(MyLayers_txt.FillPower, 10, 4)) << endl;
        stream << QString("Speed," + QString::number(MyLayers_txt.FillSpeed, 10, 4)) << endl;
        if(i%2 == 0){
            for(int j = 0; j< MyLayers_txt.Layers[i].size();j++){
                for(int k = 0;k<MyLayers_txt.Layers[i][j].size();k+=2){
                    stream << "Segment,"<<QString::number(MyLayers_txt.Layers[i][j][k].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k].y(), 10, 4);
                    stream << ","+QString::number(MyLayers_txt.Layers[i][j][k+1].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k+1].y(), 10, 4) <<endl;
                stream <<endl;
                }
            }
        }
        else{
            for(int j = 0; j< MyLayers_txt.Layers[i].size();j++){
                for(int k = 0;k<MyLayers_txt.Layers[i][j].size();k+=2){
                    stream << "Segment,"<<QString::number(MyLayers_txt.Layers[i][j][k].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k].y(), 10, 4);
                    stream << ","+QString::number(MyLayers_txt.Layers[i][j][k+1].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k+1].y(), 10, 4) <<endl;
                stream <<endl;
                }
            }
        }

    }
    if(MyLayers_txt.Type == 2){
        stream <<"#Layer,Polygon"<<endl;
        stream << QString("Power," + QString::number(MyLayers_txt.FillPower, 10, 4)) << endl;
        stream << QString("Speed," + QString::number(MyLayers_txt.FillSpeed, 10, 4)) << endl;
        for(int j = 0; j< MyLayers_txt.Layers[i].size();j++){
            stream << "Polygon,";
            for(int k = 0;k<MyLayers_txt.Layers[i][j].size();k++){
                stream << QString::number(MyLayers_txt.Layers[i][j][k].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k].y(), 10, 4)+",";
            }
            stream<<QString::number(MyLayers_txt.Layers[i][j][0].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][0].y(),10,4);
            stream <<endl;
        }
    }
    if(MyLayers_txt.Type == 3){
        stream <<"#Layer,Polyline"<<endl;
        stream << QString("Power," + QString::number(MyLayers_txt.FillPower, 10, 4)) << endl;
        stream << QString("Speed," + QString::number(MyLayers_txt.FillSpeed, 10, 4)) << endl;
        for(int j = 0; j< MyLayers_txt.Layers[i].size();j++){
            stream << "Polygon,";
            int k = 0;
            for(k = 0;k<MyLayers_txt.Layers[i][j].size()-1;k++){
                stream << QString::number(MyLayers_txt.Layers[i][j][k].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k].y(), 10, 4)+",";
            }
            stream<<QString::number(MyLayers_txt.Layers[i][j][k].x(), 10, 4) +","+QString::number(MyLayers_txt.Layers[i][j][k].y(),10,4);
            stream <<endl;
        }
    }
    file.write("#Layer,层结束:");
    stream <<i<<endl;
    stream <<endl;
    }

    //关闭文件
    file.close();
    QString spendTime;
    if(filetimedebuge.elapsed() < 1000.0){
        spendTime = QString::number(filetimedebuge.elapsed(),10,0)+"ms";
    }
    else if(filetimedebuge.elapsed() < 60000.0){
        int sec = filetimedebuge.elapsed()/1000;
        int msec = filetimedebuge.elapsed()%1000;
        spendTime = QString::number(sec,10,0)+"s"+ QString::number(msec,10,0)+"ms";
    }
    else{
        int min = filetimedebuge.elapsed()/60000;
        int sec = filetimedebuge.elapsed()%60000;
        int msec = sec % 1000;
        sec = sec/1000;
        spendTime = QString::number(min,10,0)+"min"+QString::number(sec,10,0)+"s"+ QString::number(msec,10,0)+"ms";
    }
    MW->ui->plainTextEdit->clear();
    MW->ui->plainTextEdit->appendPlainText(QString("文件生成成功! \n保存位置为: ")+QString(filename));
    MW->ui->plainTextEdit->appendPlainText(QString("文件生成耗时: ")+spendTime);
    MW->ui->plainTextEdit->appendPlainText(QString("\n"));
    //MW->ui->plainTextEdit->appendPlainText(QString("文件生成耗时: ")+QString::number(filetimedebuge.elapsed(),10,0)+"ms");
    MW->ui->plainTextEdit->appendPlainText(QString("总层数为 " + QString::number(MyLayers_txt.SingleLayerNum, 10, 0)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("单层的短边长 " + QString::number(MyLayers_txt.SingleLayerLength, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("单层的长边长 " + QString::number(MyLayers_txt.SingleLayerWidth, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前层数 " + QString::number(MW->ui->CurLayNum->value(), 10, 0)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前层数中心点位置: x " + QString::number(MyLayers_txt.BaseMidPointArray[MW->ui->CurLayNum->value()-1].x(), 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前层数中心点位置: y " + QString::number(MyLayers_txt.BaseMidPointArray[MW->ui->CurLayNum->value()-1].y(), 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前X_min 为 " + QString::number(MyLayers_txt.x_min, 10, 4)).toUtf8()+QString(" X_max 为 " + QString::number(MyLayers_txt.x_max, 10, 4)).toUtf8()+QString(" x方向差值为 " + QString::number(MyLayers_txt.x_max-MyLayers_txt.x_min, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前Y_min 为 " + QString::number(MyLayers_txt.y_min, 10, 4)).toUtf8()+QString(" Y_max 为 " + QString::number(MyLayers_txt.y_max, 10, 4)).toUtf8()+QString(" y方向差值为 " + QString::number(MyLayers_txt.y_max-MyLayers_txt.y_min, 10, 4)).toUtf8());
    MW->ui->plainTextEdit->appendPlainText(QString("当前Z_min 为 " + QString::number(MyLayers_txt.z_min, 10, 4)).toUtf8()+QString(" Z_max 为 " + QString::number(MyLayers_txt.z_max, 10, 4)).toUtf8()+QString(" z方向差值为 " + QString::number(MyLayers_txt.z_max-MyLayers_txt.z_min, 10, 4)).toUtf8());

    MW->ui->plainTextEdit->show();
//    //重新打开文件，对文件进行读操作
//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
//        qDebug()<<"文件打开失败";
//    }
//    //每次都去文件中的一行，然后输出读取到的字符串
//    char * str = new char[100];
//    qint64 readNum = file.readLine(str,100);
//    //当读取出现错误（返回 -1）或者读取到的字符数为 0 时，结束读取
//    while((readNum !=0) && (readNum != -1)){
//        qDebug() << str;
//        readNum = file.readLine(str,100);
//    }
}
void Widget::myLines()
{
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

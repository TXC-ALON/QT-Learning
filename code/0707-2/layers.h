#ifndef LAYERS_H
#define LAYERS_H


#include<vector>
#include<iostream>
#include <algorithm>
#include <cmath>
#include<QVector>
#include<QPointF>
double deg2Rad(double angle);
#define DBL_EPSILON 0.00000000000001
class Pointf{
public:
    Pointf() = default;
    Pointf(double Ax,double Ay) :
        x(Ax),
        y(Ay)
    {
        if(fabs(x)<DBL_EPSILON) x = 0;
        if(fabs(y)<DBL_EPSILON) y = 0;
    }
    ~Pointf(){}
public:
    double x ;
    double y ;
public:
    void PointRotate(double rad);
    void PointTranslate(Pointf toPoint);
    void PointTranslate(double to_x,double to_y);
    void PointNormalize();
    void PointPrint();
};
void FixDouble2Zero(double &temp);
void FixPoint2Zero(Pointf &tempPoint);
void PrintPointArray(std::vector<Pointf> Pointarray);
void PrintPointArray(QVector<QPointF> Pointarray);
void PrintTwoDimVector(std::vector<std::vector<Pointf>> Point2Array);
void PrintTwoDimVector(QVector<QVector<QPointF>> Point2Array);
class CommonTreePath{
public:
    CommonTreePath() = default;
    CommonTreePath(
            bool    IF_Interlaced,//是否隔行
            double  TypeTreeVeinDif, //树形筋间距
            double  FillSpace,  //填充间距
            QPointF  MidPoint,
            double  PathAreaLength,    //填充轮廓范围长（这里其实是较小的一段）
            double  PathAreaWidth    //填充轮廓范围宽
            )
            :
            IF_Interlaced(IF_Interlaced),
            TypeTreeVeinDif(TypeTreeVeinDif),
            FillSpace(FillSpace),
            BaseMidPoint(MidPoint),
            PathAreaLength(PathAreaLength),
            PathAreaWidth(PathAreaWidth)
    {
        if(SingleTreeInit() && BuildUpForest()){
            std::cout<<"TreeVeinNum is "<<TreeVeinNum<<std::endl;
            std::cout<<"TreeLeafWidth is "<<TreeLeafWidth<<std::endl;
            std::cout<<"TreeLeafNum is "<<TreeLeafNum<<std::endl;
        }
        std::cout<<"07071424"<<std::endl;

    }
public:
    bool    IF_Interlaced;//是否隔行
    QPointF  BaseMidPoint;//模型中心点
    double  PathAreaLength;    //填充轮廓范围长（这里其实是较小的一段）
    double  PathAreaWidth;     //填充轮廓范围宽
    //间距
    double  TypeTreeVeinDif; //树形筋间距
    double  FillSpace;  //填充间距
    QVector<QPointF> TreeMidPointArray; // 中心点路径点集
    QVector<QPointF> TreePointArray; // 单个树路径点集
    QVector<QVector<QPointF>> ForestPointArray; // 所有路径点集

private:
    unsigned int TreeVeinNum;
    double TreeLeafWidth;
    unsigned int TreeLeafNum;
    bool SingleTreeInit();
    bool BuildUpForest();
    bool BuildUpSingleTree(QPointF MidPoint);
};
class BoxPath{
public:
    BoxPath() = default;
    BoxPath(
            bool    IF_Interlaced,//是否隔行
            bool    IF_I2O, //是否从内向外
            double  FillSpace,  //填充间距
            QPointF  MidPoint,
            double  PathAreaLength,    //填充轮廓范围长（这里其实是较小的一段）
            double  PathAreaWidth    //填充轮廓范围宽
            )
            :
            IF_Interlaced(IF_Interlaced),
            IF_I2O(IF_I2O), //是否从内向外
            FillSpace(FillSpace),
            BaseMidPoint(MidPoint),
            PathAreaLength(PathAreaLength),
            PathAreaWidth(PathAreaWidth)
            {
                if(SingleBoxInit() && BuildUpComBox()){
                    std::cout<<"BoxNum is "<<BoxNum<<std::endl;
                }
            }
public:
    bool    IF_Interlaced;//是否隔行
    bool    IF_I2O; //是否从内向外
    QPointF  BaseMidPoint;//模型中心点
    double  PathAreaLength;    //填充轮廓范围长（这里其实是较小的一段）
    double  PathAreaWidth;     //填充轮廓范围宽
    //间距
    double  FillSpace;  //填充间距

    QVector<QPointF> BoxLUPointArray; // 每个盒子左上点路径点集
    QVector<QPointF> BoxPointArray; // 单个盒子路径点集
    QVector<QVector<QPointF>> ComBoxPointArray; // 所有路径点集
private:
    unsigned int BoxNum;
    double WLradio;
    bool SingleBoxInit();
    bool BuildUpComBox();
    bool BuildUpSingleBox(QPointF LUPoint);
};
class UniCursalPath{
public:
    UniCursalPath() = default;
    ~UniCursalPath(){}
    UniCursalPath(
            bool    IF_Interlaced,//是否隔行
            bool    IF_I2O, //是否从内向外
            double  FillSpace,  //填充间距
            QPointF  MidPoint,
            double  PathAreaLength,    //填充轮廓范围长（这里其实是较小的一段）
            double  PathAreaWidth    //填充轮廓范围宽
    )
            :
            IF_Interlaced(IF_Interlaced),
            IF_I2O(IF_I2O), //是否从内向外
            FillSpace(FillSpace),
            BaseMidPoint(MidPoint),
            PathAreaLength(PathAreaLength),
            PathAreaWidth(PathAreaWidth)
    {
        std::cout<<"PathAreaLength is "<<PathAreaLength<<std::endl;
        std::cout<<"PathAreaWidth is "<<PathAreaWidth<<std::endl;
        if(SingleUniCursalInit() && BuildUpComUniCursal()){
            std::cout<<"UniCursalNum is "<<ComUniCursalPointArray.size()<<std::endl;
            std::cout<<"UniCursalPoint is "<<ComUniCursalPointArray.size()*ComUniCursalPointArray[0].size()<<std::endl;
            std::cout<<"--------PathAreaLength is "<<PathAreaLength<<std::endl;
            std::cout<<"--------PathAreaWidth is "<<PathAreaWidth<<std::endl;
        }
    }
public:
    bool    IF_Interlaced;//是否隔行
    bool    IF_I2O; //是否从内向外
    QPointF  BaseMidPoint;//模型中心点
    double  PathAreaLength;    //填充轮廓范围长（这里其实是较小的一段）
    double  PathAreaWidth;     //填充轮廓范围宽
    //间距
    double  FillSpace;  //填充间距
    QVector<QPointF> UniCursalLUPointArray; // 一笔画以4倍数的点集合
    QVector<QPointF> UniCursalPointArray; // 单个一笔画路径点集
    QVector<QVector<QPointF>> ComUniCursalPointArray; // 所有一笔画路径点集
private:
    unsigned int UniCursalNum;
    double WLradio;
    bool SingleUniCursalInit();
    bool BuildUpSingleUniCursal();
    bool BuildUpComUniCursal();

};
class SingleLayer
{
public:
    SingleLayer() = default;
    SingleLayer(
            unsigned int Type,
            bool    IF_Interlaced,//是否隔行
            Pointf  MidPoint,
            double  SliceLength,    //切片长（这里其实是较小的一段）
            double  SliceWidth,    //切片宽
            double  TypeTreeVeinDif, //树形筋间距
            double  ExtendedContourSpace, //拓展轮廓间距
            double  ContourFillSpace,   //轮廓和填充间距
            double  FillSpace  //填充间距

    )
            :
            Type(Type),
            IF_Interlaced(IF_Interlaced),
            BaseMidPoint(MidPoint),
            SliceLength(SliceLength),
            SliceWidth(SliceWidth),
            TypeTreeVeinDif(TypeTreeVeinDif),
            ExtendedContourSpace(ExtendedContourSpace),
            ContourFillSpace(ContourFillSpace),
            FillSpace(FillSpace)
    {}
    ~SingleLayer(){}

public:
    //路径类型及切片层基本参数
    unsigned int Type;
    bool    IF_Interlaced;//是否隔行
    Pointf  BaseMidPoint;//模型中心点
    double  SliceLength;    //切片长（这里其实是较小的一段）
    double  SliceWidth;     //切片宽
    //间距
    double  TypeTreeVeinDif; //树形筋间距
    double  ExtendedContourSpace; //拓展轮廓间距
    double  ContourFillSpace;   //轮廓和填充间距
    double  FillSpace;  //填充间距
public:
    std::vector<Pointf> PathPointArray; // 路径点集
    std::vector<Pointf> ContourPointArray; // 轮廓路径点集
    std::vector<Pointf> ExtendedContourPointArray; // 拓展轮廓路径点集
private:
    void BaseMidPointArrayInit();

};
class LayerCom{
public:
    LayerCom() = default;
    LayerCom(
            unsigned int Type,
            bool    IF_Interlaced,//是否隔行
            double  TiltAngle,//倾斜角
            Pointf  ToPoint,
            double  RotateAngle,
            double  SliceThickness,//激光切片层厚
            double  sheetThickness,//薄片厚度
            double  sheetWidth,//薄片宽度
            double  sheetHeight,//薄片高度
            double  TypeTreeVeinDif, //树形筋间距
            double  ExtendedContourSpace, //拓展轮廓间距
            double  ContourFillSpace,   //轮廓和填充间距
            double  FillSpace,  //填充间距
            double  ExtendedContourPower, //拓展轮廓功率
            double  ExtendedContourSpeed, //拓展轮廓速度
            double  ContourPower, //轮廓功率
            double  ContourSpeed, //轮廓速度
            double  FillPower, //填充功率
            double  FillSpeed //填充速度
            )
            :
            Type(Type),
            IF_Interlaced(IF_Interlaced),
            TiltAngle(deg2Rad(TiltAngle)),
            BaseMidPoint(Pointf(0,0)),
            ToPoint(ToPoint),        //模型移动到指定位置
            RotateAngle(deg2Rad(RotateAngle)),    //物件旋转角 （逆时针）
            SliceThickness(SliceThickness),
            sheetThickness(sheetThickness),
            sheetWidth(sheetWidth),
            sheetHeight(sheetHeight),
            TypeTreeVeinDif(TypeTreeVeinDif),
            ExtendedContourSpace(ExtendedContourSpace),
            ContourFillSpace(ContourFillSpace),
            FillSpace(FillSpace),
            ExtendedContourPower(ExtendedContourPower),
            ExtendedContourSpeed(ExtendedContourSpeed),
            ContourPower(ContourPower),
            ContourSpeed(ContourSpeed),
            FillPower(FillPower),
            FillSpeed(FillSpeed)
            {
            if(LayerInit()&&MidPointArrayInit()){
                std::cout<<"SingleLayerNum is "<<SingleLayerNum<<std::endl;
                std::cout<<"SingleLayerLength is "<<SingleLayerLength<<std::endl;
                std::cout<<"SingleLayerwidth is "<<SingleLayerWidth<<std::endl;
                std::cout<<"LayerLengthh is "<<LayerLength<<std::endl;
            }
            else{
                std::cout<<"error"<<std::endl;
            }
            }
    void MidPointTranslate(Pointf toPoint);
public:
    //路径类型及薄片基本参数
    unsigned int Type;
    bool    IF_Interlaced;//是否隔行
    double  TiltAngle;//倾斜角
    Pointf  BaseMidPoint;//模型中心点
    Pointf  ToPoint;        //模型移动到指定位置
    double  RotateAngle;    //物件旋转角 （逆时针）
    double  SliceThickness;//激光切片层厚
    double  sheetThickness;//薄片厚度
    double  sheetWidth;//薄片宽度
    double  sheetHeight;//薄片高度
    //间距
    double  TypeTreeVeinDif; //树形筋间距
    double  ExtendedContourSpace; //拓展轮廓间距
    double  ContourFillSpace;   //轮廓和填充间距
    double  FillSpace;  //填充间距
    //功率与速度
    double  ExtendedContourPower; //拓展轮廓功率
    double  ExtendedContourSpeed; //拓展轮廓速度
    double  ContourPower; //轮廓功率
    double  ContourSpeed; //轮廓速度
    double  FillPower; //填充功率
    double  FillSpeed; //填充速度
    //提供给下一层的参数
    double SingleLayerLength;       //单片的长
    double SingleLayerWidth;        //单片的宽
    unsigned int SingleLayerNum;    //切片总数
    std::vector<Pointf> BaseMidPointArray; //中心点路径点集
public:
    void PointArrayRotate(double rad);
private:
    double LayerLength;
    Pointf MainNormal= Pointf(1,0);
    bool LayerInit();
    bool MidPointArrayInit();
};
#endif // LAYERS_H

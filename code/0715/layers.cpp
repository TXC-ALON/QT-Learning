#include "layers.h"
#include <algorithm>

double deg2Rad(double angle){
    double rad = (angle/180)*M_PI;
    return rad;
}

void FixDouble2Zero(double &temp){
    if(fabs(temp)<DBL_EPSILON) temp = 0;
}

void FixPoint2Zero(Pointf &tempPoint){
    FixDouble2Zero(tempPoint.x);
    FixDouble2Zero(tempPoint.y);
}
void FixPoint2Zero(QPointF &tempPoint){
    FixDouble2Zero(tempPoint.rx());
    FixDouble2Zero(tempPoint.ry());
}

bool sortPointf(Pointf A, Pointf B){
    return A.y<B.y;
}
bool sortQPointf(QPointF A, QPointF B){
    if(A.y()<B.y()){
        return true;
    }
    return false;
}

void PrintPointArray(std::vector<Pointf> Pointarray)
{
    for(unsigned int i = 0;i<Pointarray.size();i++){
        std::cout<<"-------the "<< i <<" Point is "<<" ("<<Pointarray[i].x <<","<<Pointarray[i].y <<")"<<std::endl;
    }

}
void PrintTwoDimVector(std::vector<std::vector<Pointf>> ForestPointArray){
    for(unsigned int i = 0;i<ForestPointArray.size();i++){
        std::cout<<"the "<<i <<" Dim of "<< ForestPointArray.size()<< " is "<<std::endl;
        PrintPointArray(ForestPointArray[i]);
    }
}

void PointArrayRotate(std::vector<Pointf> &Pointarray,double degree){
    double rad = deg2Rad(degree);
    for(unsigned int i = 0; i<Pointarray.size();i++){
        Pointarray[i].PointRotate(rad);
    }
}
void PointArrayRotate(QVector<QPointF> &Pointarray,double degree){
    double rad = deg2Rad(degree);
    for(unsigned int i = 0; i<Pointarray.size();i++){
        double tx = Pointarray[i].x();
        double ty = Pointarray[i].y();
        Pointarray[i].rx() = tx * cos(rad) - ty * sin(rad);
        Pointarray[i].ry() = tx * sin(rad) + ty * cos(rad);
    }
}
void PointArrayTranslate(std::vector<Pointf> &Pointarray,double x,double y){
    for(unsigned int i = 0; i<Pointarray.size();i++){
        Pointarray[i].x += x;
        Pointarray[i].y += y;
    }
}
void PointArrayTranslate(QVector<QPointF> &Pointarray,double x,double y){
    for(unsigned int i = 0; i<Pointarray.size();i++){
        Pointarray[i].rx() += x;
        Pointarray[i].ry() += y;
    }
}

void PrintPointArray(QVector<QPointF> Pointarray)
{
    for(int i = 0;i<Pointarray.size();i++){
        std::cout<<"-------the "<< i <<" Point is "<<" ("<<Pointarray[i].x() <<","<<Pointarray[i].y() <<")"<<std::endl;
    }
}

void PrintTwoDimVector(QVector<QVector<QPointF> > ForestPointArray)
{
    for( int i = 0;i<ForestPointArray.size();i++){
        std::cout<<"the "<<i <<" Dim of "<< ForestPointArray.size()<< " is "<<std::endl;
        PrintPointArray(ForestPointArray[i]);
    }
}

void Pointf::PointRotate(double rad) {
    Pointf resPoint;
    resPoint.x = x * cos(rad) - y * sin(rad);
    resPoint.y = x * sin(rad) + y * cos(rad);
    FixPoint2Zero(resPoint);
    this->x = resPoint.x;
    this->y = resPoint.y;
}
void Pointf::PointTranslate(Pointf toPoint) {
    x = toPoint.x;
    y = toPoint.y;
}
void Pointf::PointTranslate(double to_x, double to_y) {
    x = to_x;
    y = to_y;
}
void Pointf::PointNormalize() {
    double m = sqrt(x*x + y*y);
    x /= m;
    y /= m;
}
void Pointf::PointPrint() {
    std::cout<<"PointPrint:: the Point is "<<" ("<<x <<","<<y <<")"<<std::endl;
}

void QPointFTranslate(QPointF Point,QPointF toPoint) {
    Point.rx() = toPoint.x();
    Point.ry() = toPoint.y();
}
void QPointFRotate(QPointF Point,double rad) {
    QPointF resPoint;
    resPoint.rx() = Point.x() * cos(rad) - Point.y() * sin(rad);
    resPoint.ry() = Point.x() * sin(rad) + Point.y() * cos(rad);
    FixPoint2Zero(resPoint);
    Point.rx() = resPoint.x();
    Point.ry() = resPoint.y();
}
bool LayerCom::LayerInit() {
    SingleLayerLength = sheetThickness / sin(TiltAngle);
    SingleLayerWidth = sheetWidth;
    sheetHeight += BaseHeight;
    SingleLayerNum = ceil (sheetHeight / SliceThickness); //向上取整
    LayerLength = 0.5*sheetThickness / sin(TiltAngle) + sheetHeight/tan(TiltAngle);
    return true;
}

bool LayerCom::MidPointArrayInit() {
    QPointF toPoint = ToPoint;
    QPointFTranslate(BaseMidPoint,toPoint);
    double rad = RotateAngle;
    QPointFRotate(MainNormal,rad);
    double dif = LayerLength / SingleLayerNum;
    for(unsigned int i = 0;i<SingleLayerNum;i++){
        QPointF tempPoint = BaseMidPoint;
        QPointFTranslate(tempPoint,QPointF(BaseMidPoint.x() + dif*i*MainNormal.x(),BaseMidPoint.y()+dif*i*MainNormal.y()));
        BaseMidPointArray.push_back(tempPoint);
    }
    //PrintPointArray(BaseMidPointArray);
    return true;
}

bool LayerCom::BuildUPLayers()
{
    for(unsigned int i = 0;i<SingleLayerNum;i++){
        SingleLayer pp(
                    Type,
                    i,//LayNum
                    IF_Interlaced,//是否隔行
                    IF_I2O,
                    BaseMidPointArray[i],
                    SingleLayerLength,    //切片长（这里其实是较小的一段）
                    SingleLayerWidth,    //切片宽
                    TypeTreeVeinDif, //树形筋间距
                    ExtendedContourSpace, //拓展轮廓间距
                    ContourFillSpace,   //轮廓和填充间距
                    FillSpace  //填充间距
                    );
        Layers.push_back(pp.PathPointArray);
        ECPointArray.push_back(pp.ExtendedContourPointArray);
        CPointArray.push_back(pp.ContourPointArray);
    }
    return true;
}

bool CommonTreePath::SingleTreeInit() {
    TreeLeafWidth = TypeTreeVeinDif;
    TreeVeinNum = 1;
    TreeLeafNum = ceil(PathAreaLength / FillSpace);
    FixPoint2Zero(BaseMidPoint);
    TreeMidPointArray.push_back(BaseMidPoint);
    QPointF tempPoint1(BaseMidPoint.x(),BaseMidPoint.y() - TypeTreeVeinDif);
    QPointF tempPoint2(BaseMidPoint.x(),BaseMidPoint.y() + TypeTreeVeinDif);
    while(tempPoint1.ry() > BaseMidPoint.y()-0.5*PathAreaWidth){
        FixPoint2Zero(tempPoint1);
        FixPoint2Zero(tempPoint2);
        TreeMidPointArray.push_back(tempPoint1);
        TreeMidPointArray.push_back(tempPoint2);
        tempPoint1.ry() -= TypeTreeVeinDif;
        tempPoint2.ry() += TypeTreeVeinDif;
        TreeVeinNum +=2;
    }
    //PrintPointArray(TreeMidPointArray);
    return true;
}
bool CommonTreePath::BuildUpSingleTree(QPointF MidPoint) {
    TreePointArray.clear();
    double P_x = MidPoint.x() - PathAreaLength/2;
    double Q_x = MidPoint.x() + PathAreaLength/2;
    QPointF LeftPoint(P_x,MidPoint.y());
    QPointF RightPoint(Q_x,MidPoint.y());
    TreePointArray.push_back(LeftPoint);
    TreePointArray.push_back(RightPoint);
    QPointF tempPoint1,tempPoint2;
    double TreeVeinDif = TypeTreeVeinDif;
    if( fabs(MidPoint.y()) + TreeVeinDif > PathAreaWidth/2){
        if(MidPoint.y() > DBL_EPSILON){
            tempPoint1 = QPointF (LeftPoint.x(),MidPoint.y()-TreeVeinDif/2);
            tempPoint2 = QPointF (LeftPoint.x(),PathAreaWidth/2);
        }
        else{
            tempPoint1 = QPointF (LeftPoint.x(),-PathAreaWidth/2);
            tempPoint2 = QPointF (LeftPoint.x(),MidPoint.y()+TreeVeinDif/2);
        }
    }
    else{
        tempPoint1 = QPointF (LeftPoint.x(),MidPoint.y()-TreeVeinDif/2);
        tempPoint2 = QPointF (LeftPoint.x(),MidPoint.y()+TreeVeinDif/2);
    }
    double theFillSpace = FillSpace;
    if(IF_Interlaced){

        QPointF secondPoint1 = QPointF(tempPoint1.x()+FillSpace,tempPoint1.y());
        QPointF secondPoint2 = QPointF(tempPoint2.x()+FillSpace,tempPoint2.y());
        theFillSpace = 2*FillSpace;
        for(unsigned int i = 0;(tempPoint1.x()<MidPoint.x()+PathAreaLength/2);i++){
            FixPoint2Zero(tempPoint1);
            FixPoint2Zero(tempPoint2);
            if(i % 2 == 0){
                TreePointArray.push_back(tempPoint1);
                TreePointArray.push_back(tempPoint2);
            }
            else{
                TreePointArray.push_back(tempPoint2);
                TreePointArray.push_back(tempPoint1);
            }
            tempPoint1.rx() += theFillSpace;
            tempPoint2.rx() += theFillSpace;
        }
        for(unsigned int i = 0;(secondPoint1.x()<MidPoint.x()+PathAreaLength/2);i++){
            FixPoint2Zero(secondPoint1);
            FixPoint2Zero(secondPoint1);
            if(i % 2 == 0){
                TreePointArray.push_back(secondPoint1);
                TreePointArray.push_back(secondPoint2);
            }
            else{
                TreePointArray.push_back(secondPoint2);
                TreePointArray.push_back(secondPoint1);
            }
            secondPoint1.rx() += theFillSpace;
            secondPoint2.rx() += theFillSpace;
        }

    }
    else{
        for(unsigned int i = 0;i<TreeLeafNum;i++){
            FixPoint2Zero(tempPoint1);
            FixPoint2Zero(tempPoint2);
            if(i % 2 == 0){
                TreePointArray.push_back(tempPoint1);
                TreePointArray.push_back(tempPoint2);
            }
            else{
                TreePointArray.push_back(tempPoint2);
                TreePointArray.push_back(tempPoint1);
            }
            tempPoint1.rx() += theFillSpace;
            tempPoint2.rx() += theFillSpace;
        }
    }


    if(tempPoint1.x()-PathAreaLength/2 < DBL_EPSILON){
        QPointF RUPoint(PathAreaLength/2,tempPoint1.y());
        QPointF RDPoint(PathAreaLength/2,tempPoint2.y());

        TreePointArray.push_back(RUPoint);
        TreePointArray.push_back(RDPoint);
    }

    //std::cout<<"-------------------------------------------"<<std::endl;
    //PrintPointArray(TreePointArray);
    return true;
}
bool CommonTreePath::BuildUpForest() {
    std::sort(TreeMidPointArray.begin(),TreeMidPointArray.end(), sortQPointf);
    //std::cout<<"****print the forest****"<<std::endl;
    for(unsigned int i = 0;i<TreeMidPointArray.size();i++){
        BuildUpSingleTree(TreeMidPointArray[i]);
        ForestPointArray.push_back(TreePointArray);
    }
    //PrintTwoDimVector(ForestPointArray);
    return true;
}

bool BoxPath::SingleBoxInit() {
    BoxNum = ceil(0.5*PathAreaLength/FillSpace);
    QPointF LUPoint(-PathAreaLength/2,PathAreaWidth/2);
    BoxLUPointArray.push_back(LUPoint);
    for(unsigned int i = 1;i<BoxNum;i++){
        LUPoint = QPointF(LUPoint.rx()+FillSpace,LUPoint.ry()- FillSpace);
        BoxLUPointArray.push_back(LUPoint);
    }
    PrintPointArray(BoxLUPointArray);
    return true;
}

bool BoxPath::BuildUpSingleBox(QPointF LUPoint) {
    QPointF LDPoint(LUPoint.x(),-LUPoint.y());
    QPointF RDPoint(-LUPoint.x(),-LUPoint.y());
    QPointF RUPoint(-LUPoint.x(),LUPoint.y());
    BoxPointArray.push_back(LUPoint);
    BoxPointArray.push_back(LDPoint);
    BoxPointArray.push_back(RDPoint);
    BoxPointArray.push_back(RUPoint);
    //PrintPointArray(BoxPointArray);
    return true;
}

bool BoxPath::BuildUpComBox() {
    std::cout<<"print the Boxs"<<std::endl;
    if(IF_Interlaced){
        for(unsigned int i = 0 ;i<BoxNum;i+=2){
            BoxPointArray.clear();
            BuildUpSingleBox(BoxLUPointArray[i]);
            ComBoxPointArray.push_back(BoxPointArray);
        }
        for(unsigned int i = 1 ;i<BoxNum;i+=2){
            BoxPointArray.clear();
            BuildUpSingleBox(BoxLUPointArray[i]);
            ComBoxPointArray.push_back(BoxPointArray);
        }
    }
    else{
        for(unsigned int i = 0; i<BoxNum;i++){
            BoxPointArray.clear();
            BuildUpSingleBox(BoxLUPointArray[i]);
            ComBoxPointArray.push_back(BoxPointArray);
        }
    }
    if(IF_I2O){
        for(int i = 0,j = ComBoxPointArray.size()-1;i<j;i++,j--){
            ComBoxPointArray[i].swap(ComBoxPointArray[j]);
        }
    }

    //PrintTwoDimVector(ComBoxPointArray);
    return true;
}

bool UniCursalPath::SingleUniCursalInit() {
    if(IF_Interlaced){
        FillSpace = 2*FillSpace;
    }
    QPointF tempPoint = QPointF(-PathAreaLength/2,PathAreaWidth/2);
    while(((tempPoint.x() ) <= FillSpace && tempPoint.x() < DBL_EPSILON) && tempPoint.y() > DBL_EPSILON){
        UniCursalLUPointArray.push_back(tempPoint);
        tempPoint.rx() += FillSpace;
        tempPoint.ry() -= FillSpace;
    }
    PrintPointArray(UniCursalLUPointArray);
    std::cout<<"UniCursalLUPointArray.size()  "<<UniCursalLUPointArray.size()<<std::endl;
    return true;
}

bool UniCursalPath::BuildUpSingleUniCursal() {
    UniCursalPointArray.clear();
//    if(IF_Interlaced){
//        UniCursalPointArray.push_back(QPointF(-PathAreaLength/2,-PathAreaWidth/2+FillSpace/2));
//    }
//    else{
//        UniCursalPointArray.push_back(QPointF(PathAreaLength/2,PathAreaWidth/2));
//        UniCursalPointArray.push_back(QPointF(PathAreaLength/2,-PathAreaWidth/2));
//        UniCursalPointArray.push_back(QPointF(-PathAreaLength/2,-PathAreaWidth/2));
//    }
//    for(unsigned int i = 1; i <UniCursalLUPointArray.size();i++){
//        QPointF tempPoint1 = UniCursalLUPointArray[i-1];
//        QPointF tempPoint2 = QPointF(-tempPoint1.x()-FillSpace,tempPoint1.y());
//        QPointF tempPoint3 = QPointF(-tempPoint1.x()-FillSpace,-tempPoint1.y()+FillSpace);
//        QPointF tempPoint4 = QPointF(tempPoint1.x()+FillSpace,-tempPoint1.y()+FillSpace);
//        UniCursalPointArray.push_back(tempPoint1);
//        UniCursalPointArray.push_back(tempPoint2);
//        UniCursalPointArray.push_back(tempPoint3);
//        UniCursalPointArray.push_back(tempPoint4);
//    }
//    if(UniCursalLUPointArray.back().x()+FillSpace/2 <DBL_EPSILON){
//       UniCursalPointArray.push_back(UniCursalLUPointArray.back());
//    }

    QPointF tempPoint(-PathAreaLength/2,PathAreaWidth/2);
    QPointF tempPoint1(PathAreaLength/2,PathAreaWidth/2);
    QPointF tempPoint2(PathAreaLength/2,-PathAreaWidth/2);
    QPointF tempPoint3(-PathAreaLength/2,-PathAreaWidth/2);
    if(IF_Interlaced == false){
        UniCursalPointArray.push_back(tempPoint1);
        UniCursalPointArray.push_back(tempPoint2);
        UniCursalPointArray.push_back(tempPoint3);
        UniCursalPointArray.push_back(tempPoint);
    }
    else{
        UniCursalPointArray.push_back(QPointF(tempPoint3.x(),tempPoint3.y()+FillSpace/2));
        UniCursalPointArray.push_back(tempPoint);
    }


    int p_x[4] = {1,0,-1,0};
    int p_y[4] = {0,-1,0,1};
    int i = 0;
    double x_step = PathAreaLength;
    double y_step = PathAreaWidth;
    //while(fabs(tempPoint.x()) > FillSpace/4 && fabs(tempPoint.x()) <= PathAreaLength){
    while(std::min(x_step,y_step) >= 1.5*FillSpace && fabs(tempPoint.x()) <= PathAreaLength){
        x_step -= FillSpace*abs(p_x[i]);
        y_step -= FillSpace*abs(p_y[i]);
        tempPoint.rx()+=x_step*p_x[i];
        tempPoint.ry()+=y_step*p_y[i];
        i++;
        if(i == 4) i = 0;
        FixPoint2Zero(tempPoint);
        UniCursalPointArray.push_back(tempPoint);

        FixPoint2Zero(tempPoint);
        std::cout<<"tempPoint   "<<tempPoint.x() <<" " << tempPoint.y()<<std::endl;
        std::cout<<i<<" x_step   "<<x_step <<"   y_step   " <<y_step<< std::endl;

    }
    QPointF recordPoint = UniCursalPointArray[UniCursalPointArray.size()-2];

    x_step -= FillSpace*abs(p_x[i]);
    y_step -= FillSpace*abs(p_y[i]);
    tempPoint.rx()+=x_step*p_x[i];
    tempPoint.ry()+=y_step*p_y[i];
    std::cout<<"**************************"<<std::endl;
    std::cout<<"tempPoint   "<<tempPoint.x() <<" " << tempPoint.y()<<std::endl;
    std::cout<<i<<" x_step   "<<x_step <<"   y_step   " <<y_step<< std::endl;
    std::cout<<"recordPoint   "<<recordPoint.x() <<" " << recordPoint.y()<<std::endl;


    if(fabs(fabs(tempPoint.x() - recordPoint.x()) - FillSpace) < DBL_EPSILON ){
        std::cout<<tempPoint.x()-recordPoint.x() <<std::endl;
        UniCursalPointArray.push_back(tempPoint);
    }



    //UniCursalPointArray.push_back(QPointF(PathAreaLength/2,PathAreaWidth/2));
    if(IF_I2O){
        QVector<QPointF> tempvec;
        for(int i = UniCursalPointArray.size()-1;i>=0;i--){
            tempvec.push_back(UniCursalPointArray[i]);

        }
        UniCursalPointArray = tempvec;
    }
    PrintPointArray(UniCursalPointArray);
    return true;
}

bool UniCursalPath::BuildUpComUniCursal() {
    if(IF_Interlaced){
        BuildUpSingleUniCursal();
        QVector<QPointF> secondUniCursal = UniCursalPointArray;
        PointArrayRotate(secondUniCursal,180);
        //ComUniCursalPointArray.push_back(secondUniCursal);
        PointArrayTranslate(secondUniCursal,-0.5*FillSpace,0.5*FillSpace);
        ComUniCursalPointArray.push_back(secondUniCursal);
        IF_Interlaced = false;
        BuildUpSingleUniCursal();
        ComUniCursalPointArray.push_back(UniCursalPointArray);

    }
    else{
        BuildUpSingleUniCursal();
        ComUniCursalPointArray.push_back(UniCursalPointArray);
    }

    PrintTwoDimVector(ComUniCursalPointArray);
    return true;
}

void Q2Point_Move(QVector<QVector<QPointF>> &Q2P,QPointF des){
    for (unsigned int i = 0;i<Q2P.size();i++){
        for (unsigned int j = 0; j<Q2P[0].size();j++){
            Q2P[i][j].rx() += des.x();
            Q2P[i][j].ry() += des.y();
        }
    }

}
void QPoint_Trans(QVector<QPointF> &QP,QPointF des,double radio){

    for (unsigned int i = 0;i<QP.size();i++){
        QP[i].rx() = QP[i].rx()*radio + des.x();
        QP[i].ry() = QP[i].ry()*radio + des.y();
    }
}
void Q2Point_Trans(QVector<QVector<QPointF>> &Q2P,QPointF des,double radio){

    for (unsigned int i = 0;i<Q2P.size();i++){
        for (unsigned int j = 0; j<Q2P[i].size();j++){
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


void SingleLayer::SingleLayerInit()
{

    int nx[4] = {-1,-1,1,1};
    int ny[4] = {1,-1,-1,1};
    for(unsigned int i = 0;i<4;i++){
        ContourPointArray.push_back(QPointF(BaseMidPoint.x()+SliceLength/2*nx[i],BaseMidPoint.y()+SliceWidth/2*ny[i]));
        ExtendedContourPointArray.push_back(QPointF(BaseMidPoint.x()+(SliceLength/2-ExtendedContourSpace)*nx[i],BaseMidPoint.y()+(SliceWidth/2-ExtendedContourSpace)*ny[i]));

    }
    PathAreaLength = SliceLength-2*ExtendedContourSpace-2*ContourFillSpace;
    PathAreaWidth = SliceWidth-2*ExtendedContourSpace-2*ContourFillSpace;
}

void SingleLayer::BuildtheTypePath()
{
    if(Type == 0)// 树
    {
        PathPointArray = CommonTreePath(
                    IF_Interlaced,
                    TypeTreeVeinDif,
                    FillSpace,
                    BaseMidPoint,
                    PathAreaLength,
                    PathAreaWidth
                    ).ForestPointArray;
    }
    else if(Type == 1) // xoy 正交树
    {
        if(LayNum % 2 == 0){
            PathPointArray = CommonTreePath(
                        IF_Interlaced,
                        TypeTreeVeinDif,
                        FillSpace,
                        BaseMidPoint,
                        PathAreaLength,
                        PathAreaWidth
                        ).ForestPointArray;
        }
        else{
            PathPointArray = XOY_TreePath(
                        FillSpace,
                        BaseMidPoint,
                        PathAreaLength,
                        PathAreaWidth
                        ).ForestPointArray;
        }

    }
    else if(Type == 2) // Box
    {
        PathPointArray = BoxPath(
                    IF_Interlaced,
                    IF_I2O,
                    FillSpace,
                    BaseMidPoint,
                    PathAreaLength,
                    PathAreaWidth
                    ).ComBoxPointArray;
    }
    else if(Type == 3) // UniCursal
    {
        PathPointArray = UniCursalPath(
                    IF_Interlaced,
                    IF_I2O,
                    FillSpace,
                    BaseMidPoint,
                    PathAreaLength,
                    PathAreaWidth
                    ).ComUniCursalPointArray;
    }
}

bool XOY_TreePath::SingleTreeInit()
{
    TreeLeafNum = ceil(PathAreaWidth / FillSpace);
    FixPoint2Zero(BaseMidPoint);
    return true;
}

bool XOY_TreePath::BuildUpSingleTree()
{
    TreePointArray.clear();
    double P_y = BaseMidPoint.y() - PathAreaWidth/2;
    double Q_y = BaseMidPoint.y() + PathAreaWidth/2;
    QPointF UPPoint(BaseMidPoint.x(),P_y);
    QPointF DownPoint(BaseMidPoint.x(),Q_y);
    TreePointArray.push_back(UPPoint);
    TreePointArray.push_back(DownPoint);
    QPointF tempPoint1,tempPoint2;
    tempPoint1 = QPointF (BaseMidPoint.x() - PathAreaLength/2,Q_y);
    tempPoint2 = QPointF (BaseMidPoint.x() + PathAreaLength/2,Q_y);
    for(unsigned int i = 0;i<TreeLeafNum;i++){
        if(i%2 == 0){
        TreePointArray.push_back(tempPoint1);
        TreePointArray.push_back(tempPoint2);
        }
        else{
        TreePointArray.push_back(tempPoint2);
        TreePointArray.push_back(tempPoint1);
        }
        tempPoint1.ry()-=FillSpace;
        tempPoint2.ry()-=FillSpace;
    }
//    if((tempPoint1.ry()  + PathAreaWidth/2) < DBL_EPSILON){
//        tempPoint1.ry() = P_y;
//        tempPoint2.ry() = P_y;
//        TreePointArray.push_back(tempPoint2);
//        TreePointArray.push_back(tempPoint1);
//    }
    ForestPointArray.push_back(TreePointArray);
    return true;
}

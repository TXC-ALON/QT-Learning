#include "widget.h"
#include <QApplication>
#include "layers.h"
int main(int argc, char *argv[])
{
    Pointf toPoint(5,6);
    //LayerCom testComLayer(1, false, 30, toPoint,45,0.03, 2, 20, 40, 0.5, 0.5, 0.5, 0.3, 50, 50, 50, 50, 50, 50);
    //CommonTreePath(true,0.3,0.2,Pointf(0,0),2,10);


    //UniCursalPath(true,0.2,Pointf(0,0),2,10);
    std::cout << "Hello, World!" << std::endl;
    QApplication a(argc, argv);
    std::cout<<"before build widget"<<std::endl;
    Widget w;
    std::cout<<"before show"<<std::endl;
    w.show();

    return a.exec();
}

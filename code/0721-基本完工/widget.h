#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "layers.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QTime>
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
    }
    Widget(QWidget *parent);
    ~Widget();
    MainWindow *MW;
    void PrintAllPara();
    void PrintLayer();
    void MakeTxt(QString filename);
    LayerCom tMyLayer;
private:
    void myLines();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

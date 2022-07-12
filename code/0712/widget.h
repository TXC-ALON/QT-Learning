#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "objects.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
public:
    Widget(QWidget *parent,MainWindow *tt){MW = tt;}
    Widget(QWidget *parent);
    ~Widget();
    MainWindow *MW;
        void PrintAllPara();
private:
    void myDrawGradient();
    void myLines();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

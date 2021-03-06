#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    void myDrawGradient();
    void myLines();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

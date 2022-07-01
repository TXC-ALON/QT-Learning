#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setPalette(QPalette(Qt::white));
    //setAutoFillBackground(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int W = this->width()/2;
    int H = this->height()/2;

    QPen pen;
    pen.setWidth(20);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DashLine);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    QRect rect(W/2,H/2,W,H);
    painter.drawRect(rect);
}

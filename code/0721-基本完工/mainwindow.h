#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "layers.h"
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();
Ui::MainWindow *ui;
    LayerCom MyLayer;

private slots:
    void on_DrawButton_clicked();
    void on_actSave_triggered();
    void on_actSaveOtherPlace_triggered();
//    void on_actOpen_triggered();
};

#endif // MAINWINDOW_H

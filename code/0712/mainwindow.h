#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
Ui::MainWindow *ui;
private slots:

    void on_actionDrawbut_triggered();

    void on_DrawButton_clicked();

};

#endif // MAINWINDOW_H

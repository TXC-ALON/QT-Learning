#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_CheckBoxUnderline_clicked(bool checked);

    void on_CheckBoxItalic_clicked(bool checked);

    void on_CheckBoxBold_clicked(bool checked);

    void setTextFontColor();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

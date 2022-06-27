#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QCheckBox>
#include <QRadioButton>
#include<QPushButton>
#include<QPlainTextEdit>
class Dialog : public QDialog
{
    Q_OBJECT
private:
    QCheckBox *checkBoxUnderLine;
    QCheckBox *checkBoxItalic;
    QCheckBox *checkBoxBold;

    QRadioButton *rBtnBlack;
    QRadioButton *rBtnBlue;
    QRadioButton *rBtnRed;

    QPlainTextEdit *plainTextEdit;

    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    void initUI();
    void initSignal();
private slots:
    void on_checkUnderline(bool checked);
    void on_checkItalic(bool checked);
    void on_checkBold(bool checked);
    void setTextFontColor();
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
};

#endif // DIALOG_H

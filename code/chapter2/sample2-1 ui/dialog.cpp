#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->radioButtonBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    QObject::connect(ui->radioButton_Red,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    QObject::connect(ui->radioButton_Yellow,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    QObject::connect(ui->radioButton_Green,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_CheckBoxUnderline_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_CheckBoxItalic_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_CheckBoxBold_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet = ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text,Qt::black);
    if(ui->radioButtonBlue->isChecked()){
        plet.setColor(QPalette::Text,Qt::blue);
    }
    else if(ui->radioButton_Red->isChecked()){
        plet.setColor(QPalette::Text,Qt::red);
    }
    else if(ui->radioButton_Yellow->isChecked()){
        plet.setColor(QPalette::Text,Qt::yellow);
    }
    else if(ui->radioButton_Green->isChecked()){
        plet.setColor(QPalette::Text,Qt::green);
    }
    ui->plainTextEdit->setPalette(plet);
}

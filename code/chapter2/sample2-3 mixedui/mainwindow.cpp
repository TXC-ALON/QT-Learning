#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::initUI()
{
    fLabCurFile = new QLabel;
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText("当前文件：");
    ui->statusBar->addWidget(fLabCurFile);
    progressBar = new QProgressBar;
    progressBar->setMinimum(5);
    progressBar->setMaximum(50);
    progressBar->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar);
    spinFontSize = new QSpinBox;
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    ui->mainToolBar->addWidget(new QLabel("字体大小"));
    ui->mainToolBar->addWidget(spinFontSize);
    comboFont = new QFontComboBox;
    ui->mainToolBar->addWidget(new QLabel("字体"));
    ui->mainToolBar->addWidget(comboFont);

    setCentralWidget(ui->textEdit);

}

void MainWindow::iniSingalSlots()
{
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_comboFont_currentIndexChanged(const QString&)));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    iniSingalSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    QTextCharFormat fmt; //格式
    fmt=ui->textEdit->currentCharFormat();//获取当前选择文字的格式

    if (checked) // 相当于调用ui->actFontBold->isChecked();读取Action的check状态
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);

    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actFontItalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actFontUnderline_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    ui->actFontItalic->setChecked(fmt.fontItalic());
    ui->actFontBold->setChecked(fmt.font().bold()); //是否粗体
    ui->actFontUnderline->setChecked(fmt.fontUnderline()); //是否有下划线
}

void MainWindow::on_spinBoxFontSize_valueChanged(int aFontSize)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize); //设置字体大小
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar->setValue(aFontSize);
}


void MainWindow::on_comboFont_currentIndexChanged(const QString &arg1)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);//设置字体名称
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

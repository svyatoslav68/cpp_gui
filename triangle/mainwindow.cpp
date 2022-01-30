#include <QLocale>
#include <QDoubleValidator>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), pixmapTriangle(new QPixmap(":/images/t_cos.png"))
{
    ui->setupUi(this);
    ui->lineEditSideB->setValidator( new QDoubleValidator(0.0, 100.0, 2, this) );
    connect(ui->lineEditSideB, &QLineEdit::editingFinished, this, &MainWindow::calculate);
    ui->lineEditSideC->setValidator( new QDoubleValidator(0.0, 100.0, 2, this) );
    connect(ui->lineEditSideC, &QLineEdit::editingFinished, this, &MainWindow::calculate);
    ui->labelPIcture->setPixmap(*pixmapTriangle);
    angleValidator = new QDoubleValidator(0.0, 180.0, 2);
    ui->lineEditAngleAlpha->setValidator(angleValidator);
    connect(ui->lineEditAngleAlpha, &QLineEdit::editingFinished, this, &MainWindow::calculate);
    connect(ui->radioButtonDegree, &QRadioButton::toggled, this, &MainWindow::onChangedRadioButton);
}

MainWindow::~MainWindow()
{
    delete angleValidator;
    delete pixmapTriangle;
    delete ui;
}

void MainWindow::onChangedRadioButton()
{
    const double pi = std::acos(-1);
    if(ui->radioButtonDegree)
       angleValidator->setTop(180.0);
    else
       angleValidator->setTop(1);
    calculate();
}

void MainWindow::calculate()
{
    const double pi = std::acos(-1);
	bool ok;
    double sideB = 0.0;
    double sideC = 0.0;
    double sideA = 0.0;
    double angleAlpha = 0.0;
	QLocale c(QLocale::German);
    if (!ui->lineEditSideB->text().isEmpty())
        sideB = c.toDouble(ui->lineEditSideB->text(), &ok);
    if (!ui->lineEditSideC->text().isEmpty())
        sideC = c.toDouble(ui->lineEditSideC->text(), &ok);
    if (!ui->lineEditAngleAlpha->text().isEmpty()) {
        if (ui->radioButtonDegree->isChecked())
            angleAlpha = (c.toDouble(ui->lineEditAngleAlpha->text())*pi)/180;
        else
            angleAlpha = c.toDouble(ui->lineEditAngleAlpha->text());
    }
    sideA = std::sqrt(sideC*sideC + sideB*sideB - 2*sideC*sideB*std::cos(angleAlpha));
    /*qDebug() << "alpha = " << angleAlpha << "; cos = " << cos(angleAlpha);
    qDebug() << "sideA = " << sideA;*/
    ui->labelSideA->setText(QString::number(sideA));
}


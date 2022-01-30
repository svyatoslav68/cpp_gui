#include <QDoubleValidator>
#include <QDebug>
#include <QLocale>
#include <cmath>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),coefficientA(0),coefficientB(0),coefficientC(0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditA->setValidator( new QDoubleValidator(-100, 100, 2, this) );
    ui->lineEditB->setValidator( new QDoubleValidator(-100, 100, 2, this) );
    ui->lineEditC->setValidator( new QDoubleValidator(-100, 100, 2, this) );
    connect(ui->lineEditA, &QLineEdit::editingFinished, this, &MainWindow::on_lineEdit_editingFinished);
    connect(ui->lineEditB, &QLineEdit::editingFinished, this, &MainWindow::on_lineEdit_editingFinished);
    connect(ui->lineEditC, &QLineEdit::editingFinished, this, &MainWindow::on_lineEdit_editingFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_editingFinished()
{
    bool ok;
    /* Здесь пришлось выбрать QLocale::German, потому валидатор принимает
     * запятую в качестве разделителя целой и дробной части, а преобразоватеь строки в double - точку.
     * Как сделать правильно? Не понял. */
    QLocale c(QLocale::German);
    //qDebug() << ui->lineEditA->text();
    QString stringFirstMember("<span style=\" font-size:18pt;\">%1%2x</span><span style=\" font-size:18pt; vertical-align:super;\">2</span>");
    QString stringSecondMember("%1%2x");
    QString stringThirdMember("%1%2");
    coefficientA = c.toDouble(ui->lineEditA->text(), &ok);
    /* Как я понял, когда LineEdit становится пустым, не вызывается editingFinished(),
     * хотелось бы, чтобы coefficientA в таком случае становился бы равным 0,
     * но не получилось так сделать */
    if((coefficientA!=0)||!ok){
        stringFirstMember = stringFirstMember.arg((coefficientA<0)?'-':'\0').arg(std::abs(coefficientA));
    }
    else {
        coefficientA = 0;
        stringFirstMember.clear();
    }
    coefficientB = c.toDouble(ui->lineEditB->text(), &ok);
    if((coefficientB!=0)||!ok){
        stringSecondMember = stringSecondMember.arg((coefficientB<0)?'-':((coefficientA!=0)?'+':'\0')).arg(std::abs(coefficientB));
    }
    else {
        coefficientB = 0;
        stringSecondMember.clear();
    }
    coefficientC = c.toDouble(ui->lineEditC->text());
    if((coefficientC!=0)||!ok){
        stringThirdMember = stringThirdMember.arg((coefficientC<0)?'-':((coefficientA==0)&&(coefficientB==0))?'\0':'+').arg(std::abs(coefficientC));
    }
    else {
        coefficientC = 0;
        stringThirdMember.clear();
    }
    ui->labelCondition->setTextFormat(Qt::RichText);
    ui->labelCondition->setText(QString("<html><head/><body><p><span style=\" font-size:18pt;\">%1%2%3=0</span></p></body></html>").arg(stringFirstMember).arg(stringSecondMember).arg(stringThirdMember));
    std::pair<double, double> result = solution();
    if (std::isnan(result.first)) {
        ui->labelX1->hide();
        ui->labelX2->hide();
        ui->labelValue1->setText("Уравнение не имеет корней");
        ui->labelValue2->hide();
    }
    else
        if(std::isnan(result.second)){
            ui->labelValue1->setText("Уравнение имеет один корень");
            ui->labelValue2->setText(QString::number(result.first));
            ui->labelX1->hide();
            ui->labelX2->show();
            ui->labelValue2->show();
        }
        else {
            ui->labelX1->show();
            ui->labelX2->show();
            ui->labelValue2->show();
            ui->labelValue1->setText(QString::number(result.first));
            ui->labelValue2->setText(QString::number(result.second));
        }
}

/*double MainWindow::smartConversion(QString value) {
    //Здесь пришлось выбрать QLocale::German, потому валидатор принимает
     // запятую в качестве разделителя целой и дробной части, а преобразоватеь строки в double - точку.
     //Как сделать правильно? Не понял.
    QLocale c(QLocale::German);
}*/

std::pair<double, double> MainWindow::solution(){
    if (coefficientA == 0)
        return std::make_pair(-coefficientC/coefficientB, std::nan("0"));
    double discriminant = coefficientB*coefficientB - 4*coefficientA*coefficientC;
    if (discriminant < 0) {
        return std::make_pair(std::nan("0"), std::nan("0"));
    }
    if (discriminant == 0)
        return std::make_pair(-coefficientB/(2*coefficientA), std::nan("0"));
    else
        return std::make_pair((-coefficientB-std::sqrt(discriminant))/(2*coefficientA), (-coefficientB+std::sqrt(discriminant))/(2*coefficientA));
}

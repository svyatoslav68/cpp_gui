#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAdd_clicked()
{
    ui->plainTextEditDestination->appendPlainText(ui->plainTextEditSource->toPlainText());
}


void MainWindow::on_pushButtonReplace_clicked()
{
    ui->plainTextEditDestination->setPlainText(ui->plainTextEditSource->toPlainText());
}


void MainWindow::on_pushButtonAddText_clicked()
{
    /* Мне кажется, что в QPlainTextEdit нельзя вставить html-код?
     * Или я что-то не правильно понял?
     * QString text;
    ui->plainTextEditSource->insertPlainText();*/
    QMessageBox::warning(this,"Сообщение", "Мне кажется, что в QPlainTextEdit\nнельзя вставить html-код?");
}


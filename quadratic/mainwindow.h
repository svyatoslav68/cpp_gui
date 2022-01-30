#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_editingFinished();
    std::pair<double, double> solution();
private:
    double coefficientA;
    double coefficientB;
    double coefficientC;
    Ui::MainWindow *ui;
    double smartConversion(QString);
};
#endif // MAINWINDOW_H

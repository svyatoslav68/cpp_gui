#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QDoubleValidator;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap *pixmapTriangle;
    QDoubleValidator *angleValidator;
private slots:
    void onChangedRadioButton();
    void calculate();
};
#endif // MAINWINDOW_H

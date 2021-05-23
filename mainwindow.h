#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "myglwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QButtonGroup>
#include <QLineEdit>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SwitchState();
    void CalculateRoute();
public:
    QButtonGroup* G=new QButtonGroup;
    QGridLayout *grid;
    myGLWidget *openGLW;
    QPushButton *btn_calc;
    QLineEdit* LE_ent1;
    QLineEdit* LE_ent2;
    QLabel *L_res;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

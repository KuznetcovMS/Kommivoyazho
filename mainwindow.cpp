#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //widgets
    //extern QLineEdit* ent1;
    //extern QLineEdit* ent2;
    //create ui
    LE_ent1=new QLineEdit;
    LE_ent2=new QLineEdit;
    grid=new QGridLayout();
    openGLW=new myGLWidget(this);
    btn_calc=new QPushButton;
    L_res = new QLabel;
    for (int i=0;i<5;i++)
    {
        QPushButton* btn=new QPushButton;
        if (i != 1 && i != 2)
        {
            btn->setFixedSize(206,50);
            grid->addWidget(btn,i,1,1,2);
        }
        connect(btn,&QPushButton::clicked,this,&MainWindow::SwitchState);
        G->addButton(btn,i);
    }
    //texts
    G->button(0)->setText("ADD POINT");
    G->button(1)->setText("-->");
    G->button(2)->setText("<->");
    G->button(3)->setText("MOVE POINT");
    G->button(4)->setText("DELETE POINT");
    btn_calc->setText("CALCULATE ROUTE");
    //style
    G->button(0)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    G->button(1)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    G->button(2)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    G->button(3)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    G->button(4)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    btn_calc->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    LE_ent1->setStyleSheet("border-color: rgb(10, 10, 10); color: rgb(255, 255, 255); border-style: solid; border-width: 1px; border-radius: 3px");
    LE_ent2->setStyleSheet("border-color: rgb(10, 10, 10); color: rgb(255, 255, 255); border-style: solid; border-width: 1px; border-radius: 3px");
    L_res->setStyleSheet("color: rgb(255, 255, 255);");
    //sizes
    G->button(1)->setFixedSize(100,50);
    G->button(2)->setFixedSize(100,50);
    btn_calc->setFixedSize(206,50);
    LE_ent1->setFixedSize(100,50);
    LE_ent2->setFixedSize(100,50);
    //locations
    grid->addWidget(openGLW,0,0,8,1);
    grid->addWidget(LE_ent1,1,1);
    grid->addWidget(LE_ent2,2,1);
    grid->addWidget(G->button(1),1,2, 1, 1);
    grid->addWidget(G->button(2),2,2);
    grid->addWidget(btn_calc,7,1,1,2);
    grid->addWidget(L_res, 6, 1, 1, 2);
    connect(btn_calc,&QPushButton::clicked, this, &MainWindow::CalculateRoute);
    ui->centralwidget->setLayout(grid);
    this->resize(1280, 720);
}
void MainWindow::SwitchState()
{
    //control button state
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int buttonID = G->id(button);
    for (int i=0;i<5;i++)
    {
        G->button(i)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255) }\n");
    }
    if (buttonID!=4) G->button(buttonID)->setStyleSheet("QPushButton { background-color: rgb(255,140,0); color: rgb(255, 255, 255); border-color: rgb(0, 255, 0);border-style: solid; border-width: 1px; border-radius: 3px}\n");
    extern QString status;
    extern QString text_for_arrows;
    extern QString statusBook[7];
    if (buttonID==1) text_for_arrows=LE_ent1->text();
    if (buttonID==2) text_for_arrows=LE_ent2->text();
    status=statusBook[buttonID];
}

void MainWindow::CalculateRoute()
{
    //calculation route
    extern int len;
    extern QVector <QVector<int>> matrix;
    QVector <int> result_arr_1;
    QVector <int> result_arr_2;
    int sum=0;
    bool flag=true;
    int M=1000;
    QVector <QVector<int>> data=matrix;
    for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (i==k || data[i][k]==0) data[i][k]=M;
    while (flag)
    {
        QVector <int> row(len);
        row.fill(M);
        QVector <int> column(len);
        column.fill(M);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) row[i]=qMin(row[i],data[i][k]);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (row[i]!=M && data[i][k]!=M) data[i][k]-=row[i];
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) column[k]=qMin(column[k],data[i][k]);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (column[k]!=M && data[i][k]!=M) data[i][k]-=column[k];
        int max_mark_x;
        int max_mark_y;
        int max_mark=-1;
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]==0)
        {
            int min1=M;
            int min2=M;
            for (int j=0;j<len;j++) if (j!=k) min1=qMin(min1,data[i][j]);
            for (int j=0;j<len;j++) if (j!=i) min2=qMin(min2,data[j][k]);
            if (min1+min2>max_mark)
            {
                max_mark=min1+min2;
                max_mark_x=i;
                max_mark_y=k;
            }
        }
        sum+=matrix[max_mark_x][max_mark_y];
        data[max_mark_y][max_mark_x]=M;
        for (int i=0;i<len;i++)
        {
            data[max_mark_x][i]=M;
            data[i][max_mark_y]=M;
        }
        result_arr_1.push_back(max_mark_x+1);
        result_arr_2.push_back(max_mark_y+1);
        flag=false;
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]!=M) flag=true;
    }
    QString result="->"+QString::number(result_arr_1[0])+"->"+QString::number(result_arr_2[0]);
    int x=result_arr_2[0];
    result_arr_1.erase(result_arr_1.begin());
    result_arr_2.erase(result_arr_2.begin());
    while (result_arr_1.size()!=0)
    {
        for (int i=0;i<result_arr_1.size();i++) if (result_arr_1[i]==x)
        {
            result+="->"+QString::number(result_arr_2[i]);
            x=result_arr_2[i];
            result_arr_1.erase(result_arr_1.begin()+i);
            result_arr_2.erase(result_arr_2.begin()+i);
            break;
        }
    }
    result[0]=' ';
    result[1]=' ';
    result+=" = "+QString::number(sum);
    L_res->setText("Результат: " + result);
}
MainWindow::~MainWindow()
{
    delete ui;
}


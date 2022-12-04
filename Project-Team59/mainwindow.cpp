#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int strnum = 1;// The defult strength is 1 when the machine is turned on.
    ui->Strength->display(strnum);// Display the number of defult strength
    connect(ui->Up, &QPushButton::clicked, this, &MainWindow::goUp);
    connect(ui->Down, &QPushButton::clicked, this, &MainWindow::goDown);

    connect(ui->min20, SIGNAL(pressed()), this, SLOT(min20()));
    connect(ui->Min45, SIGNAL(pressed()), this, SLOT(min45()));
    connect(ui->hrs3, SIGNAL(pressed()), this, SLOT(hrs3()));
    connect(ui->UD, SIGNAL(pressed()), this, SLOT(UD()));
    connect(ui->MET, SIGNAL(pressed()), this, SLOT(MET()));
    connect(ui->SD, SIGNAL(pressed()), this, SLOT(SD()));
    connect(ui->theta, SIGNAL(pressed()), this, SLOT(Theta()));
    connect(ui->Alpha, SIGNAL(pressed()), this, SLOT(Alpha()));
    connect(ui->Beta1, SIGNAL(pressed()), this, SLOT(Beta1()));
    connect(ui->Beta2, SIGNAL(pressed()), this, SLOT(Beta2()));
    connect(ui->Hz1000, SIGNAL(pressed()), this, SLOT(Hz1000()));
    connect(ui->Power, SIGNAL(pressed()), this, SLOT(Power()));
    connect(ui->delta, SIGNAL(pressed()), this, SLOT(delta()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::goUp(int strnum/*transport the defult value as a variable*/) {
    qDebug() << strnum << endl;// I don't know why it shows 0 every time when i click the button
    if(strnum < 8)
    {
        strnum = strnum + 1;
        ui->Strength->display(strnum);
        return strnum;
    }
    else
    {
        qDebug("Mixmun");
    }
}

int MainWindow::goDown(int strnum/*transport the defult value as a variable*/) {
    qDebug() << strnum << endl;//the down button has same problem with up button
    if(strnum > 2)
    {
        strnum = strnum - 1;
        ui->Strength->display(strnum);
        return strnum;
    }
    else
    {
        qDebug("Minimun");
    }
}

void MainWindow::min20(){
    qDebug("20 minutes on...");
}
void MainWindow::min45(){
    qDebug("45 minutes on...");
}
void MainWindow::hrs3(){
    qDebug("3 hours on...");
}
void MainWindow::UD(){
    qDebug("User designed on...");
}
void MainWindow::MET(){
    qDebug("Microcurrent Electrical Therapy on...");
}
void MainWindow::SD(){
    qDebug("Sub Delta...");
}
void MainWindow::delta(){
    qDebug("Delta on...");
}
void MainWindow::Theta(){
    qDebug("Theta on...");
}
void MainWindow::Alpha(){
    qDebug("Alpha on...");
}
void MainWindow::Beta1(){
    qDebug("Beta 1 no...");
}
void MainWindow::Beta2(){
    qDebug("Beta 2 on...");
}
void MainWindow::Hz1000(){
    qDebug("1000 Hz on...");
}
void MainWindow::Power(){
    qDebug("Power...");
}

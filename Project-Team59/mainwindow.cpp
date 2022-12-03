#include "mainwindow.h"
#include "ui_mainwindow.h"
//m
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Up, SIGNAL(pressed()), this, SLOT(goUp()));
    connect(ui->Down, SIGNAL(pressed()), this, SLOT(goDown()));
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

void MainWindow::goUp() {
    qDebug("Num going up...");
}
void MainWindow::goDown() {
    qDebug("Num going down...");
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

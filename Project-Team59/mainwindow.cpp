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


void MainWindow::on_btnPower_released()
{
    //check if power is on already
    //if it is not
        //initialize everything
        //display battery level
        //set 2 minute timeout
    //if power is on already
        //ask or check whether the button was held for one second of just tapped
            //if it was held we power off

            //if it was tapped then we soft off
}

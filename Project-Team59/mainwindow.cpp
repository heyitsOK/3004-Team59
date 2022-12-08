#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QPushButton>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    strnum = 0;// The defult strength is 0 when the machine is off.
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

    powerStatus = false;
    activeSession = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::goUp() {
    if (!powerStatus) {
        return 0;
    }
    if(strnum < 8)
    {
        strnum = strnum + 1;
        ui->Strength->display(strnum);
        return strnum;
    }
    else
    {
        qDebug("Maximum");
    }
}

int MainWindow::goDown() {
    if (!powerStatus) {
        return 0;
    }
    if(strnum > 1)
    {
        strnum = strnum - 1;
        ui->Strength->display(strnum);
        return strnum;
    }
    else
    {
        qDebug("Minimum");
    }
}

void MainWindow::min20(){
    if (!powerStatus) {
        return;
    }
    qDebug("20 minutes on...");
}
void MainWindow::min45(){
    if (!powerStatus) {
        return;
    }
    qDebug("45 minutes on...");
}
void MainWindow::hrs3(){
    if (!powerStatus) {
        return;
    }
    qDebug("3 hours on...");
}
void MainWindow::UD(){
    if (!powerStatus) {
        return;
    }
    qDebug("User designed on...");
}
void MainWindow::MET(){
    if (!powerStatus) {
        return;
    }
    qDebug("Microcurrent Electrical Therapy on...");
}
void MainWindow::SD(){
    if (!powerStatus) {
        return;
    }
    qDebug("Sub Delta...");
}
void MainWindow::delta(){
    if (!powerStatus) {
        return;
    }
    qDebug("Delta on...");
}
void MainWindow::Theta(){
    if (!powerStatus) {
        return;
    }
    qDebug("Theta on...");
}
void MainWindow::Alpha(){
    if (!powerStatus) {
        return;
    }
    qDebug("Alpha on...");
}
void MainWindow::Beta1(){
    if (!powerStatus) {
        return;
    }
    qDebug("Beta 1 no...");
}
void MainWindow::Beta2(){
    if (!powerStatus) {
        return;
    }
    qDebug("Beta 2 on...");
}
void MainWindow::Hz1000(){
    if (!powerStatus) {
        return;
    }
    qDebug("1000 Hz on...");
}
void MainWindow::Power(){
    qDebug("Power...");
    //check if power is on already
        QTextStream out(stdout);
        if (powerStatus) {
            //if power is on already
            //ask or check whether the button was held for one second of just tapped
            /*QMessageBox msgBox;
            msgBox.setText("Power off or Soft off?");
            msgBox.setInformativeText("Are you holding the button (power off)?");
            msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();
            switch (ret) {
                case QMessageBox::Yes:
                    //if it was held we power off
                    powerOff();
                    break;
                case QMessageBox::No:
                    //if it was tapped then we soft off
                    softOff();
                    break;*/
            if (activeSession) {
                softOff();
            } else {
                powerOff();
            }
        } else {
            //if it is not
            out << "Powering on" << endl;
            powerStatus = true;
            //initialize everything
            strnum = 1; //default strength is 1 when machine is turned on
            toggleUI(true); //pass true to this function to initialize the UI
            //display battery level
            //set 2 minute timeout
            elapsed_timer.start();
            QTimer* timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
            timer->start(1000);
        }
}

void MainWindow::timeout() {
    QTextStream out(stdout);
    if (elapsed_timer.elapsed() > 120000 && powerStatus) {
        elapsed_timer.restart();
        if (activeSession) {
            out << "Session active no timeout necessary" << endl;
        } else {
            out << "No session selected before time out." << endl;
            powerOff();
        }
    }
}

void MainWindow::toggleUI(bool onOrOff) {
    if (onOrOff) {
        ui->Strength->display(strnum);
    } else {
        ui->Strength->display(0);
    }
}

void MainWindow::powerOff() {
    QTextStream out(stdout);
    out << "Powering off" << endl;
    toggleUI(false); //pass false to this function to set UI to off defaults
    powerStatus = false;
}

void MainWindow::softOff() {
    QTextStream out(stdout);
    out << "Soft off" << endl;
    //bring intensity down to 1 slowly
    //run powerOff() function
}

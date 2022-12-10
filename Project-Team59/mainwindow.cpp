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

    connect(ui->Up, &QPushButton::clicked, this, &MainWindow::goUp);
    connect(ui->Down, &QPushButton::clicked, this, &MainWindow::goDown);

    connect(ui->Power, SIGNAL(pressed()), this, SLOT(Power()));

    powerStatus = false; //the default power status is false because the power is off when the program starts
    activeSession = false;
    sessionSelect = false;
    toggleUI(false);
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

void MainWindow::Power(){
    qDebug("Power...");
    //check if power is on already
        QTextStream out(stdout);
        if (powerStatus) {
            //if power is on already
            //ask or check whether the button was held for one second of just tapped
            QMessageBox msgBox;
            msgBox.setText("Power off or Selecting a Session?");
            msgBox.setInformativeText("Are you holding the button (power off)?");
            msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();
            switch (ret) {
                case QMessageBox::Yes:
                    //if it was held we power off
                    if (activeSession) {
                        softOff();
                    } else {
                        powerOff();
                    }
                    break;
                case QMessageBox::No:
                    //if it was tapped then we soft off
                    out << "Selecting a session" << endl;
                    sessionSelect = true;

                    break;
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
        ui->Power->setStyleSheet("border: 5px solid rgb(32, 74, 135);");
        ui->grpSession->setEnabled(true);
        ui->rdb20->setEnabled(true); //not sure why this is necessary but this radio button stays disabled without it
        ui->spbMinutes->setEnabled(false);
        ui->grpTypes->setEnabled(true);
        ui->Up->setEnabled(true);
        ui->Down->setEnabled(true);
    } else {
        ui->Strength->display(0);
        ui->Power->setStyleSheet("");
        ui->grpSession->setEnabled(false);
        ui->grpTypes->setEnabled(false);
        ui->Up->setEnabled(false);
        ui->Down->setEnabled(false);
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

void MainWindow::on_rdbUserDes_toggled(bool checked)
{
    ui->spbMinutes->setEnabled(checked);
}

void MainWindow::on_btnSelect_released()
{
    QTextStream out(stdout);
    int group = 0;
    int ud = 0;
    int type = 0;
    if (ui->rdb20->isChecked()) {
        group = 1;
    } else if (ui->rdb45->isChecked()) {
        group = 2;
    } else if (ui->rdbUserDes->isChecked()){
        group = 3;
        ud = ui->spbMinutes->value();
    }
    if (ui->rdbMET->isChecked()) {
        type = 1;
    } else if (ui->rdbSubDelta->isChecked()) {
        type = 2;
    } else if (ui->rdbDelta->isChecked()) {
        type = 3;
    } else if (ui->rdbTheta->isChecked()) {
        type = 4;
    }
    if (group == 0 || type == 0) {
        QMessageBox error;
        error.setText("Make sure you select the session group and session type before pressing the select button.");
        error.exec();
        return;
    }
    out << "The session group is: " << group << endl;
    out << "The session type is: " << type << endl;
    if (ud != 0 || group == 3) {
        out << "The user designated value is: " << ud << endl;
    }
}

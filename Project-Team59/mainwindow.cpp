#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QPushButton>
#include <QTimer>
#include <unistd.h>
#include <QElapsedTimer>

#include <QProgressBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentSessionMinutes = 0;

    strnum = gischecked();//default strength is 0, it will be 1 when machine is turned on and a group is selected
    connect(ui->Up, &QPushButton::clicked, this, &MainWindow::goUp);
    connect(ui->Down, &QPushButton::clicked, this, &MainWindow::goDown);

    connect(ui->rdb20, &QPushButton::clicked, this, &MainWindow::gischecked);
    connect(ui->rdb45, &QPushButton::clicked, this, &MainWindow::gischecked);
    connect(ui->rdbUserDes, &QPushButton::clicked, this, &MainWindow::gischecked);

    connect(ui->Power, SIGNAL(pressed()), this, SLOT(Power()));

    connect(ui->btnSelect, &QPushButton::clicked, this, &MainWindow::cd_num);
    cdnum = new QTimer(this);
    cdnum->setInterval(1000);
    currvalue = 6;
    connect(cdnum, &QTimer::timeout, this, &MainWindow::cdTimeOut);

    powerStatus = false; //the default power status is false because the power is off when the program starts
    activeSession = false;
    toggleUI(false);


    // Battery Status
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
            ui->progressBar, SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::gischecked()
{
    if (ui->rdb20->isChecked() == true || ui->rdb45->isChecked() == true || ui->rdbUserDes->isChecked() == true)
    {
        strnum = 1;
        ui->Strength->display(strnum);
        return strnum;
    }
    else
    {
        strnum = 0;
        ui->Strength->display(strnum);
        return strnum;
    }
}

void MainWindow::cd_num()
{
    cdnum->start();
}


int MainWindow::cdTimeOut()
{
    QTextStream out(stdout);
    if(currvalue > 1)
    {
        currvalue = currvalue - 1;
        out << currvalue << endl;
        return currvalue;
    }else {
        out << "Session starting..." << endl;
        cdnum->stop();
    }
}

int MainWindow::goUp() {
    QTextStream out(stdout);
    if (!powerStatus) {
        return 0;
    }
    if(strnum < 8)
    {
        if(strnum == 0 )
        {
            out << "Please choose the group first" << endl;
            return 0;
        }
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
    QTextStream out(stdout);
    if (!powerStatus) {
        return 0;
    }
    if(strnum != 0)
    {
        if(strnum > 1)
        {
            strnum = strnum - 1;
            ui->Strength->display(strnum);
            return strnum;
        }
        else {
            qDebug("Minimum");
        }
    }
    else
    {
        out << "Please choose the group first" << endl;
        return 0;
    }
}

void MainWindow::Power(){
    //check if power is on already
        QTextStream out(stdout);
        if (powerStatus) {
            //if power is on already
            if (!activeSession) {
                //ask or check whether the button was held for one second of just tapped
                /*QMessageBox msgBox;
                msgBox.setText("Power off or Selecting a Session?");
                msgBox.setInformativeText("Are you holding the button (power off)?");
                msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
                msgBox.setDefaultButton(QMessageBox::Yes);
                int ret = msgBox.exec();
                switch (ret) {
                    case QMessageBox::Yes:
                        powerOff();
                        break;
                    case QMessageBox::No:
                        //if it was tapped then we soft off
                        out << "Selecting a session" << endl;
                        sessionSelect = true;

                        break;
                }*/
                powerOff();
            } else {
                softOff();
            }
        } else {
            //if it is not
            out << "Powering on" << endl;
            //initialize everything
            powerStatus = true;
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
        if (activeSession) {
            out << "Session active no timeout necessary" << endl;
        } else {
            elapsed_timer.restart();
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

void MainWindow::group_show(int G)
{
    ui->groups->display(G);
}

void MainWindow::powerOff() {
    QTextStream out(stdout);
    out << "Powering off" << endl;
    toggleUI(false); //pass false to this function to set UI to off defaults
    powerStatus = false;out << "The strength is: " << strnum << endl;
    activeSession = false;
}

void MainWindow::softOff() {
    QTextStream out(stdout);
    out << "Soft off" << endl;
    //bring intensity down to 1 slowly
    for (;strnum >= 1; strnum--) {
        sleep(1);
        out << "Intensity: " << strnum << endl;

    }
    //run powerOff() function
    powerOff();
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
        group = 20;
        group_show(group);
    } else if (ui->rdb45->isChecked()) {
        group = 45;
        group_show(group);
    } else if (ui->rdbUserDes->isChecked()){
        group = (ui->spbMinutes->value())*60;
        ud = ui->spbMinutes->value();
        group_show(group);
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

    if (group != 0 || type != 0) {
        out << "Session starting after 5 seconds..." << endl;
    }


    //set activeSession to true
    activeSession = true;
    switch (type) {
    case 1:
        out << "MET running for " << group << " minutes." << endl;
        out << "0.5-3 Hz, short pulses." << endl;
        out << "The strength is: " << strnum << endl;
        break;
    case 2:
        out << "Sub-Delta running for " << group << " minutes." << endl;
        out << "0.5-3 Hz, 50% duty cycle pulses" << endl;
        out << "The strength is: " << strnum << endl;
        break;
    case 3:
        out << "Delta running for " << group << " minutes." << endl;
        out << "2.5-5 Hz" << endl;
        out << "The strength is: " << strnum << endl;
        break;
    case 4:
        out << "Theta running for " << group << " minutes." << endl;
        out << "6-8 Hz" << endl;
        out << "The strength is: " << strnum << endl;
        break;
    default:
        break;
    }

    currentSessionMinutes = group;
    elapsed_timer.restart();
    ui->grpSession->setEnabled(false);
    ui->grpTypes->setEnabled(false);
    session_timer.start();
    QTimer* stimer = new QTimer(this);
    connect(stimer, SIGNAL(timeout()), this, SLOT(sessionTimeout()));
    stimer->start(1000);

}

void MainWindow::sessionTimeout() {
    QTextStream out(stdout);
    if (session_timer.elapsed() > currentSessionMinutes * 60000 && activeSession && powerStatus) {
        session_timer.restart();
        out << "Session complete." << endl;
        softOff();
    }
}

void MainWindow::on_progressBar_valueChanged(int value)
{
    if(value <= 0) {
        ui->Power->setEnabled(false);
        ui->grpTypes->setEnabled(false);
        ui->grpSession->setEnabled(false);
        ui->Up->setEnabled(false);
        ui->Down->setEnabled(false);
        ui->Strength->setEnabled(false);
        ui->groups->setEnabled(false);
    }
    else if(value >= 1 && value <= 100) {
        ui->Power->setEnabled(true);
        //ui->grpTypes->setEnabled(true);
        //ui->grpSession->setEnabled(true);
        //ui->Up->setEnabled(true);
        //ui->Down->setEnabled(true);
        //ui->Strength->setEnabled(true);
        //ui->groups->setEnabled(true);
    }

    if(value >= 1 && value <= 10) {
       // QMessageBox::information(this, "Warning", "Battery Low", QMessageBox::Ok);
        ui->warning->setVisible(true);

    }
    else {
        ui->warning->setVisible(false);
    }
}

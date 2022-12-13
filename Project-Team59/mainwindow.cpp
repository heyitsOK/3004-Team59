#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <QPushButton>
#include <unistd.h>
#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connecting ui elements with slots
    connect(ui->Up, &QPushButton::clicked, this, &MainWindow::goUp);
    connect(ui->Down, &QPushButton::clicked, this, &MainWindow::goDown);
    connect(ui->Power, SIGNAL(pressed()), this, SLOT(Power()));

    //setting default values and making sure UI is turned off by default
    powerStatus = false; //the default power status is false because the power is off when the program starts
    activeSession = false;
    currentSessionMinutes = 0;
    currentSessionType = 0;
    connection = 1;
    strnum = 1; //default strength is 1
    alice = User();
    bob = User();
    currentUser = &alice;
    toggleUI(false);

    // setting battery warning to invisible and initializing battery and timer
    ui->warning->setVisible(false);
    battery = 100.0;
    battery_timer = new QTimer(this);
    connect(battery_timer, SIGNAL(timeout()), this, SLOT(updateBattery()));

    //initializing countdown timer
    cdnum = new QTimer(this);
    cdnum->setInterval(1000);
    currvalue = 6;
    connect(cdnum, &QTimer::timeout, this, &MainWindow::cdTimeOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::cdTimeOut()
{
    QTextStream out(stdout);

    if(currvalue > 1) {
        //if the countdown is not complete
        currvalue = currvalue - 1;
        out << "Session starting in " << currvalue << " seconds..." << endl;
        return currvalue;
    } else {
        //if the countdown is complete
        out << "Session starting..." << endl;
        cdnum->stop();
        //check what the session type is and output the appropriate information
        switch (currentSessionType) {
        case 1:
            out << "MET running for " << currentSessionMinutes << " minutes." << endl;
            out << "0.5-3 Hz, short pulses." << endl;
            out << "The strength is: " << strnum << endl;
            break;
        case 2:
            out << "Sub-Delta running for " << currentSessionMinutes << " minutes." << endl;
            out << "0.5-3 Hz, 50% duty cycle pulses" << endl;
            out << "The strength is: " << strnum << endl;

            break;
        case 3:
            out << "Delta running for " << currentSessionMinutes << " minutes." << endl;
            out << "2.5-5 Hz" << endl;
            out << "The strength is: " << strnum << endl;
            break;
        case 4:
            out << "Theta running for " << currentSessionMinutes << " minutes." << endl;
            out << "6-8 Hz" << endl;
            out << "The strength is: " << strnum << endl;
            break;
        default:
            break;
        }
        //set activeSession to true
        activeSession = true;

        //restarting the elapsed timer so there is no session timeout after 2 minutes
        elapsed_timer.restart();
        //disabling ui elements while in active session
        ui->grpSession->setEnabled(false);
        ui->grpTypes->setEnabled(false);
        //starting the session timer to know when the session ends
        session_timer.start();
        QTimer* stimer = new QTimer(this);
        connect(stimer, SIGNAL(timeout()), this, SLOT(sessionTimeout()));
        stimer->start(1000);
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
        out << "Maximum" << endl;
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
            out << "Minimum" << endl;
        }
    }
    else
    {
        out << "Please choose the group first" << endl;
        return 0;
    }
}

void MainWindow::Power(){
    QTextStream out(stdout);
    //check if power is on already
    if (powerStatus) {
        //if power is on already
        //check if there is an active session
        if (!activeSession) {
            //if there is no active session power off
            powerOff();
        } else {
            //if there is an active session soft off
            softOff();
        }
    } else {
        //if power is not on
        if (battery < 1.0) {
            out << "Battery Low: Replace the battery before turning on" << endl;
            return;
        }
        out << "Powering on" << endl;
        //initialize everything
        powerStatus = true;
        activeSession = false;
        strnum = 1;
        currvalue = 6;
        toggleUI(true); //pass true to this function to initialize the UI

        //set 2 minute timeout
        elapsed_timer.start();
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
        timer->start(1000);
        //start the battery timer
        battery_timer->start(1000);
    }
}

void MainWindow::timeout() {
    QTextStream out(stdout);
    //check if 2 minutes have elapsed and if the power is on
    if (elapsed_timer.elapsed() > 120000 && powerStatus) {
        if (activeSession) {
            //if a session is active then dont do anything
            out << "Session active no timeout necessary" << endl;
        } else {
            //if there is no session active restart the timer and timeout/power off
            elapsed_timer.restart();
            out << "No session selected before time out." << endl;
            powerOff();
        }
    }
}

void MainWindow::toggleUI(bool onOrOff) {
    if (onOrOff) {
        //enable UI elements
        ui->Strength->display(strnum);
        ui->Power->setStyleSheet("border: 5px solid rgb(32, 74, 135);");
        ui->grpSession->setEnabled(true);
        ui->rdb20->setEnabled(true); //not sure why this is necessary but this radio button stays disabled without it
        ui->spbMinutes->setEnabled(false);
        ui->grpTypes->setEnabled(true);
        ui->Up->setEnabled(true);
        ui->Down->setEnabled(true);
        ui->btnRecord->setEnabled(true);
        ui->btnReplay->setEnabled(true);
        ui->lblStatus->setStyleSheet("background-color: rgb(136, 138, 133);");

    } else {
        //disable UI elements
        ui->Strength->display(0);
        ui->Power->setStyleSheet("");
        ui->grpSession->setEnabled(false);
        ui->grpTypes->setEnabled(false);
        ui->Up->setEnabled(false);
        ui->Down->setEnabled(false);
        ui->btnRecord->setEnabled(false);
        ui->btnReplay->setEnabled(false);
        ui->lblStatus->setStyleSheet("background-color: rgb(136, 138, 133);");
    }
}

void MainWindow::powerOff() {
    QTextStream out(stdout);
    out << "Powering off" << endl;
    toggleUI(false); //pass false to this function to set UI to off defaults
    powerStatus = false;
    //out << "The strength is: " << strnum << endl;
    activeSession = false;
    //stop the battery timer when the power is off
    battery_timer->stop();
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
    //enable the minutes spinbox when the user designated radio button is checked
    ui->spbMinutes->setEnabled(checked);
}

void MainWindow::on_btnSelect_released()
{
    QTextStream out(stdout);

    //initialize variables to 0
    currentSessionMinutes = 0;
    currentSessionType = 0;

    //check which radio button is checked and change currentSessionMinutes to the correct int
    if (ui->rdb20->isChecked()) {
        currentSessionMinutes = 20;
    } else if (ui->rdb45->isChecked()) {
        currentSessionMinutes = 45;
    } else if (ui->rdbUserDes->isChecked()){
        currentSessionMinutes = (ui->spbMinutes->value());
    }

    //check which radio button is checked and change currentSessionType to the correct int
    if (ui->rdbMET->isChecked()) {
        currentSessionType = 1;
    } else if (ui->rdbSubDelta->isChecked()) {
        currentSessionType = 2;
    } else if (ui->rdbDelta->isChecked()) {
        currentSessionType = 3;
    } else if (ui->rdbTheta->isChecked()) {
        currentSessionType = 4;
    }

    //if either of the variables are still 0 send a message box and return
    if (currentSessionMinutes == 0 || currentSessionType == 0) {
        QMessageBox error;
        error.setText("Make sure you select the session group and session type before pressing the select button.");
        error.exec();
        return;
    }

    //run the connection test, which runs the countdown timer, which starts the sessions
    connectionTest();
}

void MainWindow::connectionTest() {
    QTextStream out(stdout);
    out << "Running connection test" << endl;
    switch (connection) {
    case 1:
        ui->lblStatus->setStyleSheet("background-color: rgb(138, 226, 52);");
        out << "Connection is good!" << endl;
        break;
    case 2:
        ui->lblStatus->setStyleSheet("background-color: rgb(252, 233, 79);");
        out << "Connection is OK!" << endl;
        break;
    case 3:
        ui->lblStatus->setStyleSheet("background-color: rgb(239, 41, 41);");
        out << "Connection is bad!" << endl;
        break;
    }

    if (connection < 3) {
        //runs the countdown timer and to start the session
        cdnum->start();
    } else {
        out << "Connection is bad, please adjust and try again." << endl;
    }
}

void MainWindow::sessionTimeout() {
    QTextStream out(stdout);
    //checks if the session timer has passed the number of minutes
    if (session_timer.elapsed() > currentSessionMinutes * 60000 && activeSession && powerStatus) {
        session_timer.restart();
        out << "Session complete." << endl;
        softOff();
    }
}

void MainWindow::updateBattery() {
    QTextStream out(stdout);
    if (battery <= 0.2) {
        if (activeSession) {
            softOff();
        } else {
            powerOff();
        }
    } else if (battery <= 10) {
        ui->warning->setVisible(true);
    } else {
        ui->warning->setVisible(false);
    }
    //calculate how much battery was used based on whether ativeSession = true and intensity level
    double change = 0.028;
    if (activeSession) {
        change = change * 2 + (strnum * 0.01);
    }
    //update battery variable
    battery = battery - change;
    //update the GUI with the new battery
    ui->progressBar->setValue(int(battery));

}

void MainWindow::on_btnRecord_released()
{
    QTextStream out(stdout);
    //check if there is an active session
    if (activeSession) {
        //if there is an active session open input box and ask user to enter a record name
        bool ok;
        QString name = QInputDialog::getText(this, tr("Enter a name"), tr("Enter a name for the new record:"), QLineEdit::Normal, tr("Name"), &ok);
        if (ok && !name.isEmpty()) {
            //create a new session record and add it to our sessions list
            Session *newRecord = new Session(currentSessionMinutes, currentSessionType, strnum, name);
            currentUser->addSession(newRecord);
        } else {
            //if the user doesn't enter a name throw an error
            QMessageBox error;
            error.setText("You need to enter a name to record a session");
            error.exec();
            return;
        }
    } else {
        //if the user is not in an active session throw an error
        QMessageBox error;
        error.setText("You need to be in an active session to record");
        error.exec();
        return;
    }
}

void MainWindow::on_btnReplay_released()
{
    QTextStream out(stdout);
    if (activeSession) {
        //if the user is in an active sesion throw an error
        QMessageBox error;
        error.setText("You need to end the current session to choose an older session");
        error.exec();
        return;
    } else {
        //if the user is not in an active session
        //check if there are recorded sessions yet
        if (currentUser->numSessions() < 1) {
            // if there are no recorded sessions throw an error and return
            QMessageBox error;
            error.setText("There are no sessions recorded yet.");
            error.exec();
            return;
        }
        //make a input dialog box with a combo box to choose from the names of the sessions
        QStringList records = currentUser->getSessionList();
        bool ok;
        //save the input into item
        QString item = QInputDialog::getItem(this, tr("Choose record"), tr("Choose from recorded sessions: "), records, 0, false, &ok);
        //find the session whose name matches item
        Session *session;
        currentUser->getSession(item, &session);
        out << "Running recorded session: " << item << endl;

        currentSessionType = session->getType();
        currentSessionMinutes = session->getGroup();
        strnum = session->getIntensity();
        ui->Strength->display(strnum);
        //run this function to start the connection test
        connectionTest();

    }
}

//simulation menu action slots
void MainWindow::on_actionGood_triggered()
{
    QTextStream out(stdout);
    connection = 1;
    out << "Connection set to good" << endl;
}

void MainWindow::on_actionOK_triggered()
{
    QTextStream out(stdout);
    connection = 2;
    out << "Connection set to OK" << endl;
}

void MainWindow::on_actionBad_triggered()
{
    QTextStream out(stdout);
    connection = 3;
    out << "Connection set to bad" << endl;
}

void MainWindow::on_actionBattery_Full_triggered()
{
    battery = 100.0;
}

void MainWindow::on_actionBattery_Low_triggered()
{
    battery = 11.0;
}

void MainWindow::on_actionBattery_End_triggered()
{
    battery = 1.0;
}

void MainWindow::on_actionAlice_triggered()
{
    QTextStream out(stdout);
    out << "Changing user to Alice" << endl;
    currentUser = &alice;
    //change the user
}

void MainWindow::on_actionBob_triggered()
{
    QTextStream out(stdout);
    out << "Changing user to Bob" << endl;
    currentUser = &bob;
    //change the user
}

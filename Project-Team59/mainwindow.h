#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QPushButton>
#include <QElapsedTimer>
#include <QTimer>
#include <QList>
#include "session.h"
#include "user.h"

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
    bool powerStatus;
    bool activeSession;
    int strnum;
    int currentSessionMinutes;
    int currentSessionType;
    int currvalue;
    int connection;
    double battery;
    QElapsedTimer elapsed_timer;
    QElapsedTimer session_timer;
    QStringList header;
    QTimer *cdnum;
    QTimer *battery_timer;
    //QList<Session *> sessions;
    User alice;
    User bob;
    User *currentUser;
    void toggleUI(bool onOrOff);
    void OperationTime(int T);
    void connectionTest();

private slots:
    int goUp();
    int goDown();
    int cdTimeOut();
    void Power();
    void powerOff();
    void softOff();
    void timeout();
    void sessionTimeout();
    void on_rdbUserDes_toggled(bool checked);
    void on_btnSelect_released();
    void updateBattery();
    void on_btnRecord_released();
    void on_btnReplay_released();
    //simulation menu action slots
    void on_actionGood_triggered();
    void on_actionOK_triggered();
    void on_actionBad_triggered();
    void on_actionBattery_Full_triggered();
    void on_actionBattery_Low_triggered();
    void on_actionBattery_End_triggered();
    void on_actionAlice_triggered();
    void on_actionBob_triggered();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QPushButton>
#include <QElapsedTimer>

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
    int strnum;
    bool activeSession;
    int currentSessionMinutes;
    int battery_num;
    int currvalue;
    QElapsedTimer elapsed_timer;
    QElapsedTimer session_timer;
    QTimer *cdnum;
    void toggleUI(bool onOrOff);
    void OperationTime(int T);
    void group_show(int G);

private slots:
    int goUp();
    int goDown();
    void Power();
    void powerOff();
    void softOff();
    void timeout();
    void sessionTimeout();
    void on_rdbUserDes_toggled(bool checked);
    void on_btnSelect_released();
    int gischecked();
    void cd_num();
    int cdTimeOut();
};
#endif // MAINWINDOW_H

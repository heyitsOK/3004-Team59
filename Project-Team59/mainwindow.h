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
    int row;
    QElapsedTimer elapsed_timer;
    QElapsedTimer session_timer;
    QStringList header;
    QTimer *cdnum;
    int g2;
    int c2;
    int s2;
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
    void on_progressBar_valueChanged(int value);
    void history(int g, int c, int s);
    void Cclick(int rw, int col);
};
#endif // MAINWINDOW_H

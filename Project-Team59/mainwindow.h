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
    QElapsedTimer elapsed_timer;
    QElapsedTimer session_timer;
    void toggleUI(bool onOrOff);


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
};
#endif // MAINWINDOW_H

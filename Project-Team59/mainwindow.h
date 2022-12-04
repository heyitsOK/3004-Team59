#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QPushButton>

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


private slots:
    int goUp();
    int goDown();
    void min20();
    void min45();
    void hrs3();
    void UD();
    void MET();
    void SD();
    void delta();
    void Theta();
    void Alpha();
    void Beta1();
    void Beta2();
    void Hz1000();
    void Power();
    void powerOff();
    void softOff();
};
#endif // MAINWINDOW_H

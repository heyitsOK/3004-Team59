/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QPushButton *Power;
    QLCDNumber *lcdNumber;
    QPushButton *Up;
    QPushButton *Down;
    QPushButton *min20;
    QPushButton *Min45;
    QPushButton *hrs3;
    QPushButton *UD;
    QPushButton *MET;
    QPushButton *theta;
    QPushButton *SD;
    QPushButton *Beta2;
    QPushButton *Beta1;
    QPushButton *Alpha;
    QPushButton *Hz1000;
    QLCDNumber *lcdNumber_2;
    QPushButton *delta;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(20, 10, 361, 551));
        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(400, 10, 361, 551));
        Power = new QPushButton(centralwidget);
        Power->setObjectName(QString::fromUtf8("Power"));
        Power->setGeometry(QRect(520, 410, 121, 71));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(50, 440, 151, 91));
        Up = new QPushButton(centralwidget);
        Up->setObjectName(QString::fromUtf8("Up"));
        Up->setGeometry(QRect(250, 440, 80, 25));
        Down = new QPushButton(centralwidget);
        Down->setObjectName(QString::fromUtf8("Down"));
        Down->setGeometry(QRect(250, 500, 80, 25));
        min20 = new QPushButton(centralwidget);
        min20->setObjectName(QString::fromUtf8("min20"));
        min20->setGeometry(QRect(150, 60, 80, 25));
        Min45 = new QPushButton(centralwidget);
        Min45->setObjectName(QString::fromUtf8("Min45"));
        Min45->setGeometry(QRect(150, 110, 80, 25));
        hrs3 = new QPushButton(centralwidget);
        hrs3->setObjectName(QString::fromUtf8("hrs3"));
        hrs3->setGeometry(QRect(150, 160, 80, 25));
        UD = new QPushButton(centralwidget);
        UD->setObjectName(QString::fromUtf8("UD"));
        UD->setGeometry(QRect(80, 220, 221, 25));
        MET = new QPushButton(centralwidget);
        MET->setObjectName(QString::fromUtf8("MET"));
        MET->setGeometry(QRect(420, 110, 80, 25));
        theta = new QPushButton(centralwidget);
        theta->setObjectName(QString::fromUtf8("theta"));
        theta->setGeometry(QRect(600, 250, 80, 25));
        SD = new QPushButton(centralwidget);
        SD->setObjectName(QString::fromUtf8("SD"));
        SD->setGeometry(QRect(540, 110, 80, 25));
        Beta2 = new QPushButton(centralwidget);
        Beta2->setObjectName(QString::fromUtf8("Beta2"));
        Beta2->setGeometry(QRect(660, 190, 80, 25));
        Beta1 = new QPushButton(centralwidget);
        Beta1->setObjectName(QString::fromUtf8("Beta1"));
        Beta1->setGeometry(QRect(540, 190, 80, 25));
        Alpha = new QPushButton(centralwidget);
        Alpha->setObjectName(QString::fromUtf8("Alpha"));
        Alpha->setGeometry(QRect(420, 190, 80, 25));
        Hz1000 = new QPushButton(centralwidget);
        Hz1000->setObjectName(QString::fromUtf8("Hz1000"));
        Hz1000->setGeometry(QRect(480, 250, 81, 21));
        lcdNumber_2 = new QLCDNumber(centralwidget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(50, 300, 291, 91));
        delta = new QPushButton(centralwidget);
        delta->setObjectName(QString::fromUtf8("delta"));
        delta->setGeometry(QRect(650, 110, 81, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Power->setText(QApplication::translate("MainWindow", "Power", nullptr));
        Up->setText(QApplication::translate("MainWindow", "Up", nullptr));
        Down->setText(QApplication::translate("MainWindow", "Down", nullptr));
        min20->setText(QApplication::translate("MainWindow", "20 min", nullptr));
        Min45->setText(QApplication::translate("MainWindow", "45 min", nullptr));
        hrs3->setText(QApplication::translate("MainWindow", "3 hrs", nullptr));
        UD->setText(QApplication::translate("MainWindow", "User designed", nullptr));
        MET->setText(QApplication::translate("MainWindow", "MET", nullptr));
        theta->setText(QApplication::translate("MainWindow", "Theta", nullptr));
        SD->setText(QApplication::translate("MainWindow", "SD", nullptr));
        Beta2->setText(QApplication::translate("MainWindow", "Beta 2", nullptr));
        Beta1->setText(QApplication::translate("MainWindow", "Beta 1", nullptr));
        Alpha->setText(QApplication::translate("MainWindow", "Alpha", nullptr));
        Hz1000->setText(QApplication::translate("MainWindow", "1000 Hz", nullptr));
        delta->setText(QApplication::translate("MainWindow", "Delta", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

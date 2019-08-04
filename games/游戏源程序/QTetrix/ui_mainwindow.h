/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Fri Sep 4 15:11:50 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *startbtn;
    QPushButton *overbtn;
    QPushButton *pausebtn;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *levellcd;
    QLabel *label_3;
    QLCDNumber *scorelcd;
    QPushButton *upbtn;
    QPushButton *leftbtn;
    QPushButton *downbtn;
    QPushButton *rightbtn;
    QPushButton *didownbtn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(720, 520);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        startbtn = new QPushButton(centralWidget);
        startbtn->setObjectName(QString::fromUtf8("startbtn"));
        startbtn->setGeometry(QRect(260, 210, 91, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        startbtn->setFont(font1);
        overbtn = new QPushButton(centralWidget);
        overbtn->setObjectName(QString::fromUtf8("overbtn"));
        overbtn->setGeometry(QRect(260, 260, 91, 31));
        overbtn->setFont(font1);
        pausebtn = new QPushButton(centralWidget);
        pausebtn->setObjectName(QString::fromUtf8("pausebtn"));
        pausebtn->setGeometry(QRect(260, 310, 91, 31));
        pausebtn->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 10, 151, 21));
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 210, 54, 13));
        label_2->setFont(font1);
        levellcd = new QLCDNumber(centralWidget);
        levellcd->setObjectName(QString::fromUtf8("levellcd"));
        levellcd->setGeometry(QRect(390, 240, 91, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setStrikeOut(false);
        levellcd->setFont(font2);
        levellcd->setAutoFillBackground(false);
        levellcd->setFrameShadow(QFrame::Raised);
        levellcd->setSegmentStyle(QLCDNumber::Filled);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 290, 54, 13));
        QFont font3;
        font3.setPointSize(12);
        label_3->setFont(font3);
        scorelcd = new QLCDNumber(centralWidget);
        scorelcd->setObjectName(QString::fromUtf8("scorelcd"));
        scorelcd->setGeometry(QRect(390, 310, 91, 31));
        scorelcd->setFont(font3);
        scorelcd->setSegmentStyle(QLCDNumber::Filled);
        upbtn = new QPushButton(centralWidget);
        upbtn->setObjectName(QString::fromUtf8("upbtn"));
        upbtn->setGeometry(QRect(340, 350, 61, 51));
        upbtn->setFont(font3);
        leftbtn = new QPushButton(centralWidget);
        leftbtn->setObjectName(QString::fromUtf8("leftbtn"));
        leftbtn->setGeometry(QRect(270, 410, 61, 51));
        leftbtn->setFont(font3);
        downbtn = new QPushButton(centralWidget);
        downbtn->setObjectName(QString::fromUtf8("downbtn"));
        downbtn->setGeometry(QRect(340, 410, 61, 51));
        downbtn->setFont(font3);
        rightbtn = new QPushButton(centralWidget);
        rightbtn->setObjectName(QString::fromUtf8("rightbtn"));
        rightbtn->setGeometry(QRect(410, 410, 61, 51));
        rightbtn->setFont(font3);
        didownbtn = new QPushButton(centralWidget);
        didownbtn->setObjectName(QString::fromUtf8("didownbtn"));
        didownbtn->setGeometry(QRect(410, 350, 61, 51));
        didownbtn->setFont(font3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        startbtn->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        overbtn->setText(QApplication::translate("MainWindow", "Game Over", 0, QApplication::UnicodeUTF8));
        pausebtn->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "The Next Tetrix:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Level:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Score:", 0, QApplication::UnicodeUTF8));
        upbtn->setText(QApplication::translate("MainWindow", "UP", 0, QApplication::UnicodeUTF8));
        leftbtn->setText(QApplication::translate("MainWindow", "LEFT", 0, QApplication::UnicodeUTF8));
        downbtn->setText(QApplication::translate("MainWindow", "DOWN", 0, QApplication::UnicodeUTF8));
        rightbtn->setText(QApplication::translate("MainWindow", "RIGHT", 0, QApplication::UnicodeUTF8));
        didownbtn->setText(QApplication::translate("MainWindow", "DDown", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QRect>
#include <QMessageBox>
#include <QTest>
#include <QT>
#include "TetrixGame.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage *memimg;
    QImage *bkimg;
    QImage *acttriimg;
    QImage *darktriimg;
    QImage *cleartriimg;
    QImage *notetriimg;
    QImage *notebackimg;
    QTimer *timer;

    CTetrixGame m_tetrixGame;
    int timeInterval;
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void drawall();
    void drawnote();
private slots:
    void on_rightbtn_clicked();
    void on_downbtn_clicked();
    void on_leftbtn_clicked();
    void on_didownbtn_clicked();
    void on_upbtn_clicked();
    void on_pausebtn_clicked();
    void on_overbtn_clicked();
    void on_startbtn_clicked();
    void timerOut();
};

#endif // MAINWINDOW_H

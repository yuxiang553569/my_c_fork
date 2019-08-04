#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    memimg       = new QImage(MAPWIDTH, MAPHEIGHT, QImage::Format_RGB16);
    bkimg        = new QImage(tr("E:/xieying/QTetrix/image/back.bmp"));
    if (bkimg->isNull())
    {
        QMessageBox::information(this, tr("Image Viewer"),
            tr("Cannot load %1.").arg("/image/back.bmp"));
        //return;
    };

    acttriimg    = new QImage(tr("E:/xieying/QTetrix/image/activetri.bmp"));
    darktriimg   = new QImage(tr("E:/xieying/QTetrix/image/darktri.bmp"));
    cleartriimg  = new QImage(tr("E:/xieying/QTetrix/image/cleartri.bmp"));
    notetriimg   = new QImage(tr("E:/xieying/QTetrix/image/notetri.bmp"));
    notebackimg  = new QImage(tr("E:/xieying/QTetrix/image/back.bmp"));
    ui->setupUi(this);
    timeInterval = 1000;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(timerOut()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startbtn_clicked()
{
    timer->start(timeInterval);
    int gflag = m_tetrixGame.GameStart();
    if( gflag != 0 )
    {
        QMessageBox::information(this, tr("Eroor!"),
            tr("Fail to Generate a Tetrix!"));
        return;
    }

    ui->levellcd->display(m_tetrixGame.GetGameLevel());
    ui->scorelcd->display(m_tetrixGame.GetGameScore());
    update();
}

void MainWindow::on_overbtn_clicked()
{
    m_tetrixGame.GameOver();
    timer->stop();
    QMessageBox::information(this, tr("NOTING!"),
                             tr("Game Over!"));

}

void MainWindow::on_pausebtn_clicked()
{
    if(m_tetrixGame.GetGameStatus() == GAMERUNNING)
        m_tetrixGame.SetGameStatus(GAMEPAUSE);
    else
        if(m_tetrixGame.GetGameStatus() == GAMEPAUSE)
            m_tetrixGame.SetGameStatus(GAMERUNNING);
}

void MainWindow::on_upbtn_clicked()
{
    if(0 == m_tetrixGame.DoRotate())
    {
        //重绘游戏区
        update();
    }
}

void MainWindow::on_didownbtn_clicked()
{
    SINT res = m_tetrixGame.DoDirectDrop();

    if( ( res == 3 ) || ( res == 5 ) )		//出下界或重叠
    {
        //将停止的方块的位置设置为STOPPING
        SINT arsize = m_tetrixGame.PrepareClear();
        if(arsize > 0)
        {
            m_tetrixGame.SetClearStatus(CLEARING);
            repaint();
            QTest::qSleep(300);
            m_tetrixGame.SetClearStatus(BLANK);
            repaint();
            QTest::qSleep(200);
            m_tetrixGame.DoClear();
            repaint();
            QTest::qSleep(300);
            SINT flagu = m_tetrixGame.UpdateScoreAndLevel();
            ui->levellcd->display(m_tetrixGame.GetGameLevel());

            ui->scorelcd->display(m_tetrixGame.GetGameScore());
            if(flagu == 0)
            {
                //重新设定时间间隔以适合不同等级
                INT interval=(INT)(1000 / m_tetrixGame.GetGameLevel());
                //重新定义记时器
                timer->start(interval);

            }
            update();
        }
        SINT flag = m_tetrixGame.GenNew();
        if( 1 == flag)
        {
            timer->stop();
            QMessageBox::information(this, tr("NOTING!"),
                                        tr("Game Over!"));
        }
    }
    else
        if(res != 0)
                return;
    //重绘游戏区
    update();
}

void MainWindow::on_leftbtn_clicked()
{
    if(0 == m_tetrixGame.GoLeft())
    {
        //重绘游戏区
        update();
    }
}

void MainWindow::on_downbtn_clicked()
{
    SINT res = m_tetrixGame.DoDrop();
    if( ( res == 3 ) || ( res == 5 ) )		//出下界或重叠
    {
        //将停止的方块的位置设置为STOPPING
        SINT arsize = m_tetrixGame.PrepareClear();
        if(arsize > 0)
        {
            m_tetrixGame.SetClearStatus(CLEARING);
            repaint();
            QTest::qSleep(300);
            m_tetrixGame.SetClearStatus(BLANK);
            repaint();
            QTest::qSleep(200);
            m_tetrixGame.DoClear();
            repaint();
            QTest::qSleep(300);
            SINT flagu = m_tetrixGame.UpdateScoreAndLevel();
            ui->levellcd->display(m_tetrixGame.GetGameLevel());
            ui->scorelcd->display(m_tetrixGame.GetGameScore());
            if(flagu == 0)
            {
                //重新设定时间间隔以适合不同等级
                INT interval=(INT)(1000 / m_tetrixGame.GetGameLevel());
                //重新定义记时器
                timer->start(interval);

            }
            update();
        }
        SINT flag = m_tetrixGame.GenNew();
        if( 1 == flag)
        {
            timer->stop();
            QMessageBox::information(this, tr("NOTING!"), tr("Game Over!"));
        }
    }
    else
        if(res != 0)
                return;
    //重绘游戏区
    update();
}

void MainWindow::on_rightbtn_clicked()
{
    if(0 == m_tetrixGame.GoRight())
    {
        //重绘游戏区
        update();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(m_tetrixGame.GetGameStatus() != GAMERUNNING)
        return;


    switch(event->key())
    {
    case Qt::Key_Left:
        this->on_leftbtn_clicked();
        break;
    case Qt::Key_Right:
        this->on_rightbtn_clicked();
        break;
    case Qt::Key_Down:
        this->on_downbtn_clicked();
        break;
    case Qt::Key_Up:
        this->on_upbtn_clicked();
        break;
    case Qt::Key_Space:
        this->on_didownbtn_clicked();
        break;
    }

}

void MainWindow::timerOut()
{
    if(m_tetrixGame.GetGameStatus() == GAMERUNNING)
        on_downbtn_clicked();
}

void MainWindow::drawall()
{
    QPainter paint;
    paint.begin(this);
    QRect target(LEFTSPAN, TOPSPAN, MAPWIDTH, MAPHEIGHT);
    paint.drawImage(target, *bkimg);
    for( INT i = 0; i < XLEN; i++ )
        for( INT j = 0; j < YLEN; j++ )
        {
            INT xpos = i * TETRIXLEN;
            INT ypos = j * TETRIXLEN;
            if(m_tetrixGame.JudgeMatrixStatus(i,j, RUNNING))
            {
                QRect rectr(LEFTSPAN + xpos, TOPSPAN + ypos, TETRIXLEN, TETRIXLEN);
                paint.drawImage(rectr, *acttriimg);
            }
            else
                if(m_tetrixGame.JudgeMatrixStatus(i,j, STOPPING))
                {
                    QRect rects(LEFTSPAN + xpos, TOPSPAN + ypos, TETRIXLEN, TETRIXLEN);
                    paint.drawImage(rects, *darktriimg);
                }
                else
                    if( m_tetrixGame.JudgeMatrixStatus(i,j, CLEARING))
                    {
                        QRect rectc(LEFTSPAN + xpos, TOPSPAN + ypos, TETRIXLEN, TETRIXLEN);
                        paint.drawImage(rectc, *cleartriimg);
                    }
        }
    paint.end();
}

void MainWindow::drawnote()
{
    if(m_tetrixGame.GetGameStatus() == GAMEOVER)
        return;
    QPainter paint;
    paint.begin(this);
    QRect target(NOTELEFTSPAN, NOTETOPSPAN, NOTEMAPWIDTH, NOTEMAPWIDTH);
    paint.drawImage(target, *notebackimg);

    for( INT i =1;  i < 5; i++ )
    {
        INT xpos = m_tetrixGame.GetNoteTriXPos(i) * TETRIXLEN;
        INT ypos = m_tetrixGame.GetNoteTriYPos(i) * TETRIXLEN;
        QRect rect(NOTELEFTSPAN + xpos, NOTETOPSPAN + ypos, TETRIXLEN, TETRIXLEN);
        paint.drawImage(rect, *notetriimg);
    }
    paint.end();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    drawall();
    drawnote();
}


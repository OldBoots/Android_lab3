#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QTimer>
#include "bug.h"
#include <QRandomGenerator>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void slot_each_sec();
    void slot_start_game();
    void slot_chec_stop();

private:
    QSize ss;
    int sh;
    int sw;
    QTimer *timer_game;
    QTimer *timer_bug;
    QVector <Bug *> vec_bugs;
    QGraphicsRectItem *rect_end;
    QGraphicsScene *scene;
    QGraphicsTextItem *game_over;
    int time;
    int uan;
    Ui::MainWindow *ui;
};

int Rand(int min, int max);

#endif // MAINWINDOW_H

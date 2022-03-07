#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QTimer>
#include "bug.h"

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
    void slot_charge_timer();
    void slot_start_game();
    void slot_spawn_bug();
    void slot_chec_stop();

private:
    void stop_game();
private:
    QSize ss;
    int sh;
    int sw;
    QTimer *timer_game;
    QTimer *timer_bug;
    QVector <Bug *> vec_bugs;
    QGraphicsRectItem *rect_end;
    QGraphicsScene * scene;
//    QGraphicsLineItem *border;
    QGraphicsTextItem *game_over;
    int time;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

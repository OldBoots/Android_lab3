#ifndef BUG_H
#define BUG_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPainter>
#include <QTouchEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QThread>


class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject * prnt = nullptr);
private slots:
    void slot_timer_ev(bool cur_s, int cur_f, int y, int speed);
signals:
    void gopa(int hh, int gg);
};

class Bug : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bug(bool type, QObject * prnt = nullptr);
    bool get_cur_state();
    int get_reward();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void set_damage(int dmg);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

private slots:
    void slot_gopa(int y, int cur_f);

private:
    QPixmap *skin;
    int hp;
    bool current_state;
    int current_frame;
    int speed;
    bool type;
    QMediaPlayer *se;
    QAudioOutput *ao;
    QThread *th;
    Worker *wr;
signals:
    void sig_timer_ev(bool cur_s, int cur_f, int y, int speed);
};

#endif // BUG_H

#ifndef BUG_H
#define BUG_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPainter>
#include <QTouchEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>


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
    void mousePressEvent (QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

private:
    QPixmap *skin;
    int hp;
    int current_frame;
    int speed;
    bool current_state;
    bool type;
    QMediaPlayer *se;
    QAudioOutput *ao;

signals:
    void sig_timer();

private slots:
    void slot_next_frame();
    void slot_timer_ev();
};

#endif // BUG_H

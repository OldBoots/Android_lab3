#ifndef BUG_H
#define BUG_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPainter>

class Bug : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bug(bool type, QObject * prnt = nullptr);
    void set_damage(int dmg);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
private:
    QPixmap *skin;
    int hp;
    int current_frame;
    int speed;
    bool current_status;

signals:
    void sig_timer();

private slots:
    void slot_next_frame();
    void slot_timer_ev();
};

#endif // BUG_H

#include "bug.h"

Bug::Bug(bool type, QObject *prnt) : QObject (prnt), QGraphicsRectItem()
{
    current_frame = 0;
    current_status = true;
    if(type){
        skin = new QPixmap(":/WarriorBug.png");
        speed = 2;
    } else {
        skin = new QPixmap(":/WorkBug.png");
        speed = 1;
    }
    connect(this, SIGNAL(sig_timer()), this, SLOT(slot_next_frame()));
}

void Bug::slot_timer_ev(){
    this->setY(this->y() + 5 * speed), emit sig_timer();
}

void Bug::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, *skin, current_frame, 0, 64, 64);
}

void Bug::slot_next_frame(){
    if(current_status){
        current_frame += 64;
        if (current_frame > 64){
            current_frame = 0;
        }
        this->update(/*this->x(), this->y()*/0, 0, 64, 64);
    }
}

void Bug::set_damage(int dmg){
    if(current_status){
        hp -= dmg;
        if(hp < 0){
            current_status = false;
        }
    }
}

QRectF Bug::boundingRect() const{
    return QRectF(0, 0, 64, 64);
}

QPainterPath Bug::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

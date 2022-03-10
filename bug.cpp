#include "bug.h"
//PUBLIC

Worker::Worker(QObject *prnt) : QObject (prnt){
}

Bug::Bug(bool type, QObject *prnt) : QObject (prnt), QGraphicsRectItem()
{
    current_frame = 0;
    current_state = true;
    this->type = type;
    se = new QMediaPlayer(this);
    ao = new QAudioOutput(this);
    se->setAudioOutput(ao);
    if(type){
        skin = new QPixmap(":/WarriorBug.png");
        speed = 2;
        hp = 100;
        se->setSource(QUrl("qrc:/RB2.mp3"));
        ao->setVolume(50);
    } else {
        skin = new QPixmap(":/WorkBug.png");
        speed = 1;
        hp = 50;
        se->setSource(QUrl("qrc:/RB1.mp3"));
        ao->setVolume(25);
    }
    th = new QThread(this);
    wr = new Worker();
wr->moveToThread(th);
        connect(this, SIGNAL(sig_timer_ev(bool,int,int,int)), wr, SLOT(slot_timer_ev(bool,int,int,int)));
        connect(wr, SIGNAL(gopa(int,int)), this, SLOT(slot_gopa(int,int)));
        qDebug("");
        th->start();
        slot_gopa(this->y(), current_frame);

}

void Bug::slot_gopa(int y, int cur_f){
    setY(y);
    current_frame = cur_f;
    update(0, 0, 64, 64);
    emit sig_timer_ev(current_state, current_frame, this->y(), speed);
}

bool Bug::get_cur_state(){
    return current_state;
}

int Bug::get_reward(){
    if(type){
        return 3;
    } else {
        return 1;
    }
}

//PRIVATE
void Bug::mousePressEvent (QGraphicsSceneMouseEvent *event){
    if (event->buttons() & Qt::LeftButton)
    {
        if(!current_state){
            se->setSource(QUrl("qrc:/Shot.mp3"));
        }
        se->stop();
        se->play();
        set_damage(25);
    }
}

void Bug::set_damage(int dmg){
    if(current_state){
        hp -= dmg;
        if(hp <= 0){
            current_state = false;
        }
    }
}

void Bug::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, *skin, current_frame, 0, 64, 64);
}

QRectF Bug::boundingRect() const{
    return QRectF(0, 0, 64, 64);
}

QPainterPath Bug::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

//PRIVATE SLOTS
void Worker::slot_timer_ev(bool cur_s, int cur_f, int y, int speed){
    int hh = y, gg = cur_f;
        QThread::currentThread()->msleep(250);
        if(cur_s){
            hh += 5 * speed;
            gg += 64;
            if (gg > 64){
                gg = 0;
            }
        } else {
            gg = 128;
        }
        emit gopa(hh, gg);
}


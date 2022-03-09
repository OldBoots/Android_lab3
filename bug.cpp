#include "bug.h"
//PUBLIC
Bug::Bug(bool type, QObject *prnt) : QObject (prnt), QGraphicsRectItem()
{
    current_frame = 0;
    current_state = true;
    this->type = type;
    se = new QMediaPlayer(this);
    ao = new QAudioOutput(this);
    se->setAudioOutput(ao);
    connect(se, SIGNAL(errorOccurred(QMediaPlayer::Error error, const QString &errorString)), this, SLOT());
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
    connect(this, SIGNAL(sig_timer()), this, SLOT(slot_next_frame()));
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
void Bug::slot_next_frame(){
    if(current_state){
        current_frame += 64;
        if (current_frame > 64){
            current_frame = 0;
        }
    } else {
        current_frame = 128;
    }
    this->update(0, 0, 64, 64);
}

void Bug::slot_timer_ev(){
    if(current_state){
        this->setY(this->y() + 5 * speed);
    }
    emit sig_timer();
}


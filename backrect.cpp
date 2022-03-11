#include "backrect.h"

BackRect::BackRect(QObject *parent) : QObject (parent), QGraphicsRectItem()
{
    se = new QMediaPlayer(this);
    ao = new QAudioOutput(this);
    se->setAudioOutput(ao);
    se->setSource(QUrl("qrc:/Shot.mp3"));
    ao->setVolume(70);
}

void BackRect::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->buttons() & Qt::LeftButton)
    {
        se->stop();
        se->play();
    }
}

#include "mygraphscene.h"

MyGraphScene::MyGraphScene(QObject *parent)
    : QGraphicsScene{parent}
{
    se = new QMediaPlayer(this);
    ao = new QAudioOutput(this);
    se->setSource(QUrl("qrc:/Shot.mp3"));
    se->setAudioOutput(ao);
    ao->setVolume(50);
}

void MyGraphScene::mousePressEvent (QGraphicsSceneMouseEvent *event){
    if (event->buttons() & Qt::LeftButton){
        se->stop();
        se->play();
    }
}

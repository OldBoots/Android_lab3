#ifndef MYGRAPHSCENE_H
#define MYGRAPHSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
//#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MyGraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphScene(QObject *parent = nullptr);
private:
    QMediaPlayer *se;
    QAudioOutput *ao;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // MYGRAPHSCENE_H

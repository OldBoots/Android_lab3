#ifndef BACKRECT_H
#define BACKRECT_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>

class BackRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit BackRect(QObject *parent = nullptr);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QMediaPlayer *se;
    QAudioOutput *ao;

signals:

};

#endif // BACKRECT_H

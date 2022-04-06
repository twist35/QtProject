#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>


class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    QTimer* timer;
    QGraphicsTextItem* qgti;
    QGraphicsRectItem* qgri;

public:
    MyScene(QObject* parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    virtual ~MyScene();

public slots:
    void update();

};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H

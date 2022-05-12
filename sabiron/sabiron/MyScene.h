#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include "includes.h"
#include "PersoItem.h"


class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    QTimer* timer;
    QGraphicsPixmapItem* qgpiBg;
    QGraphicsPixmapItem* qgpiMap;
    QGraphicsPixmapItem* qgpiChest;
    QPixmap background;
    QGraphicsRectItem* rDessous;
    QGraphicsRectItem* rDessus;

public:
    PersoItem* perso;
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();
    void drawBackground(QPainter* painter, const QRectF& rect);

protected:
     void keyPressEvent(QKeyEvent* event);
    // void keyReleaseEvent(QKeyEvent* event);

public slots:
    void update();

};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H

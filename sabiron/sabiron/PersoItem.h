#ifndef PERSOITEM_H
#define PERSOITEM_H

#include "includes.h"

class PersoItem : public QGraphicsPixmapItem
{
private:
    QString direction = "bas";
    bool isJumped = false;
    bool voidBelow = true;
    QString dirJump = "droite";
    int countJump = 0;
    QPoint debJump;
public:
    PersoItem(QString imageFileName): QGraphicsPixmapItem(QPixmap(imageFileName)){};
    void move();
    void jump(int n);
    QString getDirection();
    void setDirection(QString nDiection);
    bool getIsJump();
    void setIsJump(bool nJump);
    bool getVoidBelow(){return this->voidBelow;}
    void setVoidBelow(bool nVoid){this->voidBelow = nVoid;}
    int getCountJump();
    void setCountJump(int nCount);
    void setDirJump(QString nDirJump);
    QString getDirJump();
    QPointF getDebJump();
    void setDebJump(QPointF nP);


};

#endif // PERSOITEM_H

#ifndef PERSOITEM_H
#define PERSOITEM_H

#include "includes.h"

class PersoItem : public QGraphicsPixmapItem
{
private:
    QString direction = "bas";
    QString dirJump = "droite";
    bool isJumped = false;
    bool voidBelow = true;
    bool voidAbove = true;
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
    bool getVoidAbove(){return this->voidAbove;}
    void setVoidAbove(bool nVoid){this->voidAbove = nVoid;}
    int getCountJump();
    void setCountJump(int nCount);
    void setDirJump(QString nDirJump);
    QString getDirJump();
    QPointF getDebJump();
    void setDebJump(QPointF nP);



};

#endif // PERSOITEM_H

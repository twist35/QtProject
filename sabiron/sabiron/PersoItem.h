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
    bool win = false;
    bool won = false;
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
    bool getIsWin(){return this->win;}
    void setIsWin(bool nWin){this->win = nWin;}
    bool getIsWon(){return this->won;}
    void setIsWon(bool nWin){this->won = nWin;}
    int getCountJump();
    void setCountJump(int nCount);
    void setDirJump(QString nDirJump);
    QString getDirJump();
    QPointF getDebJump();
    void setDebJump(QPointF nP);



};

#endif // PERSOITEM_H

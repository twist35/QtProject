#ifndef PERSOITEM_H
#define PERSOITEM_H

#include "includes.h"

class PersoItem : public QGraphicsPixmapItem
{
private:
    QString direction = "bas";
    bool isJumped = false;
    int countJump = 0;
public:
    PersoItem(QString imageFileName): QGraphicsPixmapItem(QPixmap(imageFileName)){};
    void move();
    void jump(int n);
    QString getDirection();
    void setDirection(QString nDiection);
    bool getIsJump();
    void setIsJump(bool nJump);
    int getCountJump();
    void setCountJump(int nCount);


};

#endif // PERSOITEM_H

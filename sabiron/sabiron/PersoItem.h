#ifndef PERSOITEM_H
#define PERSOITEM_H

#include "includes.h"

class PersoItem : public QGraphicsPixmapItem
{
private:
    QString direction;
    bool isJumped;
public:
    PersoItem(QString imageFileName): QGraphicsPixmapItem(QPixmap(imageFileName)){};
    void move();
    void jump(/*MyScene* s*/);
    QString getDirection();
    void setDirection(QString nDiection);
    bool getIsJump();
    void setIsJump(bool nJump);


};

#endif // PERSOITEM_H

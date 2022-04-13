#include "includes.h"
#include "PersoItem.h"

void PersoItem::move() {


    QPointF pos = this->pos();

    /*if (pos.x() > this->scene()->width()) {
        qDebug() << "droite";
        this->moveBy(-5,0);
    }*/
    if (pos.x() <0) {
        qDebug() << "gauche";
        this->moveBy(5,0);
    }
    if (pos.y() <0) {
        qDebug() << "haut";
        this->moveBy(0,5);
    }
    if (pos.y() > 810) {
        qDebug() << "bas";
        this->moveBy(0,-5);
    }


}

QString PersoItem::getDirection()
{
    return this->direction;
}
void PersoItem::setDirection(QString nDiection)
{
    this->direction = nDiection;
}
bool PersoItem::getIsJump()
{
    return this->isJumped;
}
void PersoItem::setIsJump(bool nJump)
{
    this->isJumped = nJump;
}

void PersoItem::jump(/*MyScene* s*/)
{
    QPointF pos1 = this->pos();
    for(int i=0; i< 384; i++)
    {
        this->setPos(pos1.x()+i,pos1.y()-i*i+3);
        //s->update();
    }

}

#include "includes.h"
#include "PersoItem.h"

void PersoItem::move() {
    //this->moveBy(0, 5);
    QPointF pos = this->pos();


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
    }/*
    if(this->getIsJump() == true)
    {
        this->setPos(pos.x()+5, pos.y()-5);
        this->setIsJump(false);
        //this->jump();
    }*/



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

void PersoItem::jump(int n)
{
    int dir = 1;
    QPointF pos1 = this->pos();
    if (this->direction == "gauche") //gérer la direction du saut
        dir = -1;
    else if(this->direction == "droite")
        dir = 1;

    if (n < 50)
        this->setPos(pos1.x() + 5*dir, pos1.y() - 5);
    else
        this->setPos(pos1.x() + 5*dir, pos1.y() + 5);

}
int PersoItem::getCountJump()
{
    return this->countJump;
}
void PersoItem::setCountJump(int nCount)
{
    this->countJump = nCount;
}

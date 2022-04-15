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

    int dir = 1;  //gérer la direction du saut
    QPointF pos1 = this->pos();
    if (this->direction == "gauche")
        dir = -1;
    else
        dir = 1;

    /*if (n < 224)
        this->setPos(pos1.x() + 1*dir, pos1.y() - 1);
    else
        this->setPos(pos1.x() + 1*dir, pos1.y() + 1);*/
    this->setPos(pos1.x() + 1*dir*2, this->getDebJump().y() - ((int)(-0.025*(n-112)*(n+112)))); // simulation de la parabole de saut
     qDebug() << n << "      " << (int)(-0.25*(n-112)*(n+112));

}
int PersoItem::getCountJump()
{
    return this->countJump;
}
void PersoItem::setCountJump(int nCount)
{
    this->countJump = nCount;
}
QPointF PersoItem::getDebJump()
{
    return this->debJump;
}
void PersoItem::setDebJump(QPointF nP)
{
    this->debJump.setX(nP.x());
    this->debJump.setY(nP.y());
}

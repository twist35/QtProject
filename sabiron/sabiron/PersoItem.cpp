#include "includes.h"
#include "PersoItem.h"

void PersoItem::move() {
    if(this->getVoidBelow() && !this->getIsJump())
        this->moveBy(0, 4);

    QPointF pos = this->pos();

    if (pos.x() <0) {
        qDebug() << "gauche";
        this->moveBy(5,0);
    }
    if (pos.y() <0) {
        qDebug() << "haut";
        this->moveBy(0,5);
        //this->setIsJump(false);
    }
    if (pos.y() > 810) // touche le vide
    {
        qDebug() << "bas";
        this->setPos(0,400);
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

void PersoItem::jump(int n)
{

    int dir = 1;  //gérer la direction du saut
    QPointF pos1 = this->pos();
    if (this->getDirJump() == "droite")
        dir = 1;
    else if (this->getDirJump() == "gauche")//par défaut vers la droite
        dir = -1;

    this->setPos(pos1.x() + 1*dir*2, this->getDebJump().y() - ((int)(-0.025*(n-112)*(n+112)))); // simulation de la parabole de saut
     //qDebug() << n << "      " << (int)(-0.025*(n-112)*(n+112));

     // gestion des collision pendant le saut
     if (this->getCountJump() < 112)
         this->setDirection("haut");
     if (this->getCountJump() > 112)
         this->setDirection("bas");
     if (this->getCountJump() >= 224)
     {
          qDebug() << n << "fin saut";
          //this->moveBy(0,-10);
     }

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
QString PersoItem::getDirJump()
{
    return this->dirJump;
}
void PersoItem::setDirJump(QString nDirJump)
{
    this->dirJump = nDirJump;
}

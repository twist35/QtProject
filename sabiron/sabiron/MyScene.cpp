#include "MyScene.h"


MyScene::MyScene(QObject* parent)   : QGraphicsScene(parent) {

    this->background.load(":/images/bg");
    this->setSceneRect(0, 0, background.width(), background.height());

    // this->setSceneRect(0,0, 900, 900);

    this->qgpiMap = new QGraphicsPixmapItem(QPixmap("img/mapB.png"));
    this->addItem(qgpiMap);
    qgpiMap->setPos(0, 0);

    this->perso = new PersoItem("img/1.png");
    this->addItem(this->perso);
    this->perso->setPos(0,0);

    this->rDessous = new QGraphicsRectItem(this->perso->pos().x()+25, this->perso->pos().y()+90, 45, 1); // rectangle sous le personnage
    this->addItem(this->rDessous);
    //this->rDessous->setOpacity(0);



    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20); // =50fps
}

MyScene::~MyScene() {

}

void MyScene::update()
{
    this->perso->move();
    this->rDessous->setPos(this->perso->pos().x(), this->perso->pos().y());

    if (this->perso->collidesWithItem(this->qgpiMap)) { //gestion des collsions avec le bg
        /*QList<QGraphicsItem*> ListCollingItem = this->perso->collidingItems(); //recupere les item en collison avec
        qDebug() << ListCollingItem;*/

        if(this->perso->getDirection() == "bas")
        {
            this->perso->moveBy(0, -5);
        }
        else if(this->perso->getDirection() == "haut")
            this->perso->moveBy(0, 5);
        else if(this->perso->getDirection() == "gauche")
            this->perso->moveBy(5, 0);
        else if(this->perso->getDirection() == "droite")
            this->perso->moveBy(-5, 0);

        if(this->perso->getIsJump())
        {

            //this->perso->moveBy(0, -5);
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
        }

    }
        if(this->rDessous->collidesWithItem(this->qgpiMap)){
            //this->perso->moveBy(0,-5);
             this->perso->setVoidBelow(false);
        }
        else
        {
            this->perso->setVoidBelow(true);
        }



    QList<QGraphicsView*> ListVue= this->views(); //recupere toutes les vue
    //qDebug() <<"nbVue" << ListVue;

    ListVue[1]->centerOn(this->perso);


    //qDebug() << this->perso->getIsJump();
    if (this->perso->getIsJump())
    {
        if (this->perso->getCountJump() == 0)
            this->perso->setDirJump(this->perso->getDirection());
        if(this->perso->getCountJump() < 224)
        {
            this->perso->jump(this->perso->getCountJump() -112);
            this->perso->setCountJump(this->perso->getCountJump() + 1);
            qDebug() << "saut n°" <<this->perso->getCountJump() ;
        }
        else
        {
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
        }

    }
}

void MyScene::keyPressEvent(QKeyEvent* event){
    //if(this->perso->getIsJump() ==  false) // pour eviter de pouvoir se déplacer en même temps que le saut
    //{
    float jumpSpeed = 1.0;
    if(this->perso->getIsJump())
        jumpSpeed = 0.4;

    switch(event->key())
    {
        case Qt::Key_Up:
            this->perso->moveBy(0, -5*jumpSpeed);
            this->perso->setDirection("haut");
            break;
        case Qt::Key_Down:
            this->perso->moveBy(0, 5*jumpSpeed);
            this->perso->setDirection("bas");
            break;
        case Qt::Key_Right:
            this->perso->moveBy(5*jumpSpeed, 0);
            this->perso->setDirection("droite");
            //this->perso->setPos(this->perso->pos().x() +5,0);
            break;
        case Qt::Key_Left:
            this->perso->moveBy(-5*jumpSpeed, 0);
            this->perso->setDirection("gauche");
            break;
    }
    //}
    if( event->key() == Qt::Key_Space && (!this->perso->getIsJump())) // pour ne sauter alors qu'on est deja en train de sauter
    {

        this->perso->setIsJump(true);
        QPointF pos1 = this->perso->pos();
        this->perso->setDebJump(pos1);
    }

}
/*void MyScene::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Space)
    this->perso->setIsJump(false);

}*/


void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}


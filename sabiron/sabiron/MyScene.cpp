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
    this->perso->setIsJump(false);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20); // =50fps
}

MyScene::~MyScene() {

}

void MyScene::update()
{
    /*if (this->perso->getIsJump() ==  true)
    {
        this->perso->jump();
        this->perso->setIsJump(false);
    }*/

    //qgti->setPos(pos.rx(), pos.ry()+1); //incrémentation de la coordonnée y
    if (this->perso->collidesWithItem(this->qgpiMap)) { //gestion des collsions avec le bg
        /*QList<QGraphicsItem*> ListCollingItem = this->perso->collidingItems(); //recupere les item en collison avec
        qDebug() << ListCollingItem;*/
        if(this->perso->getDirection() == "bas")
            this->perso->moveBy(0, -5);
        else if(this->perso->getDirection() == "haut")
            this->perso->moveBy(0, 5);
        else if(this->perso->getDirection() == "gauche")
            this->perso->moveBy(5, 0);
        else if(this->perso->getDirection() == "droite")
            this->perso->moveBy(-5, 0);
    }



    QList<QGraphicsView*> ListVue= this->views(); //recupere toutes les vue
    //qDebug() <<"nbVue" << ListVue;
    ListVue[1]->centerOn(this->perso);
    this->perso->move();

}
void MyScene::keyPressEvent(QKeyEvent* event){


    if(event->key() == Qt::Key_Space) { // appui sur la touche espace du clavier
    //qDebug() << "Touche espace appuyée";
    /*QPointF pos1 = this->qgpiTest->pos(); //récupération de la position de l'objet qgti
    this->qgpiTest->moveBy(5,0);*/
    }

    switch(event->key())
    {
        case Qt::Key_Up:
            this->perso->moveBy(0, -5);
            this->perso->setDirection("haut");
            break;
        case Qt::Key_Down:
            this->perso->moveBy(0, 5);
            this->perso->setDirection("bas");
            break;
        case Qt::Key_Right:
            this->perso->moveBy(5, 0);
            this->perso->setDirection("droite");
            //this->perso->setPos(this->perso->pos().x() +5,0);
            break;
        case Qt::Key_Left:
            this->perso->moveBy(-5, 0);
            this->perso->setDirection("gauche");
            break;
        case Qt::Key_Space:
            this->perso->setIsJump(true);
            break;
    }
}
void MyScene::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Space)
    this->perso->setIsJump(false);

}


void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

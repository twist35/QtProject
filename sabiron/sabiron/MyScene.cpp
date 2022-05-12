#include "MyScene.h"


MyScene::MyScene(QObject* parent)   : QGraphicsScene(parent) {

    //QGraphicsTextItem *text = this->addText("Hello World");
    //text->setPos(100, 200);
    this->background.load(":/images/bg");
    this->setSceneRect(0, 0, background.width(), background.height());

    this->qgpiMap = new QGraphicsPixmapItem(QPixmap(":/images/map1"));
    this->addItem(qgpiMap);
    qgpiMap->setPos(0, 0);

    this->qgpiChest = new QGraphicsPixmapItem(QPixmap(":/images/tresor"));
    this->addItem(qgpiChest);
    qgpiChest->setPos(0, 0);

    this->perso = new PersoItem("img/1.png");
    this->addItem(this->perso);


    this->rDessous = new QGraphicsRectItem(this->perso->pos().x()+25, this->perso->pos().y()+90, 45, 1); // rectangle sous le personnage
    this->addItem(this->rDessous);
    this->rDessous->setOpacity(0);// rect du dessous si debug à enlever

    this->rDessus = new QGraphicsRectItem(this->perso->pos().x()+25, this->perso->pos().y()/*+90*/, 45, 1); // rectangle sur le personnage
    this->addItem(this->rDessus);
    this->rDessus->setOpacity(0);// rect du dessus si debug à enlever



    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(20); // =50fps
    this->perso->setPos(0,500);

}

MyScene::~MyScene() {

}

void MyScene::update()
{
    //qDebug() <<"void below ? :" << this->perso->getVoidBelow();
    //qDebug() <<"Jumped ? :" << this->perso->getIsJump() << " \n";

    this->perso->move();
    this->rDessous->setPos(this->perso->pos().x(), this->perso->pos().y());
    this->rDessus->setPos(this->perso->pos().x(), this->perso->pos().y());

    if (this->perso->collidesWithItem(this->qgpiChest))
        this->perso->setIstWin(true);


    if (this->perso->collidesWithItem(this->qgpiMap)) { //gestion des collsions avec le bg

        if(this->perso->getIsJump())
        {
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
            this->perso->setDirection("bas");
            qDebug() << "collison pdt sauttttttttttttttttttttttttttttttttttttttttt ";

            this->perso->moveBy(0, -5); // regles quelques bugs de collision lors de l'arrivée du saut
        }

            if(this->perso->getDirection() == "bas")
            {
                this->perso->moveBy(0, -5);
                qDebug() << "Collsion bas";
            }

            else if(this->perso->getDirection() == "haut")
            {
                this->perso->moveBy(0, 5);
                qDebug() << "Collsion haut";
            }

            else if(this->perso->getDirection() == "gauche")
            {
                qDebug() << "Collsion gauche";
                this->perso->moveBy(5, 0);
            }
            else if(this->perso->getDirection() == "droite")
            {
                this->perso->moveBy(-5, 0);
                qDebug() << "Collsion droite";
            }

    }
    if (this->perso->getIsJump())
    {
        //qDebug() << "saut en cours";
        if(this->perso->getCountJump() <= 224)
        {
            //this->perso->setDirJump(this->perso->getDirection());
            this->perso->jump(this->perso->getCountJump() - 112);
            this->perso->setCountJump(this->perso->getCountJump() + 1);
        }
        else
        {
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
            qDebug() << "fin du saut";
        }
    }

    if(this->rDessous->collidesWithItem(this->qgpiMap)){ // si le rectangle du dessous touche la map
        this->perso->setVoidBelow(false);
        this->perso->moveBy(0,-4); // remettre si bug ou le personnage rentre sol sans saut mais rajoute bug qu'il faut parfois appuyer 2 fois sur espace
        if (this->perso->getIsJump() && this->perso->getCountJump() > 5)
        {
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
            this->perso->setDirection("bas");
            this->perso->moveBy(0,-4);
            qDebug() << "collison rect dessous";
        }
    }
    else
    {
        this->perso->setVoidBelow(true);
    }

    if(this->rDessus->collidesWithItem(this->qgpiMap)){ // si le rectangle du dessus touche la map
        this->perso->setVoidAbove(false);
        this->perso->moveBy(0,4);
        if (this->perso->getIsJump() /*&& this->perso->getCountJump() > 5*/)
        {
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
            this->perso->setDirection("bas");
            this->perso->moveBy(0,4);
            qDebug() << "collison rect dessus";
        }
    }
    else
    {
        this->perso->setVoidAbove(true);
    }


    QList<QGraphicsView*> ListVue= this->views(); //recupere toutes les vues

    ListVue[1]->centerOn(this->perso);


}



/*void MyScene::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Space)
    this->perso->setIsJump(false);

}*/

void MyScene::keyPressEvent(QKeyEvent* event){
    float jumpSpeed = 1.0;
    if(this->perso->getIsJump())
        jumpSpeed = 0.35; // facteur de de vitesse de déplacement si saut

    switch(event->key())
    {
        case Qt::Key_Up:
            this->perso->moveBy(0, -5);
            break;
        case Qt::Key_Down:
            this->perso->setIsJump(false);
            this->perso->setCountJump(0);
            this->perso->setDirection("bas");
            break;
        case Qt::Key_Right:
            this->perso->moveBy(5*jumpSpeed, 0);
            this->perso->setDirection("droite");
            this->perso->setDirJump("droite");
            break;
        case Qt::Key_Left:
            this->perso->moveBy(-5*jumpSpeed, 0);
            this->perso->setDirection("gauche");
            this->perso->setDirJump("gauche");
            break;
        case Qt::Key_R: // restart
            this->perso->setPos(0,400);
            this->perso->setDirection("haut");
            break;
        case Qt::Key_F: // debug
            this->perso->setPos(12500, 500);
            break;

    }

    if( event->key() == Qt::Key_Space && (!this->perso->getIsJump() && !this->perso->getVoidBelow())) // pour ne sauter alors qu'on est deja en train de sauter
    {

        this->perso->setIsJump(true);
        QPointF pos1 = this->perso->pos();
        this->perso->setDebJump(pos1);
        qDebug() << "appuie sur \"espace\" ";
    }

}


void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}


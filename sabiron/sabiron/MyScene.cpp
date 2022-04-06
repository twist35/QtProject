#include "MyScene.h"


MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {
    this->qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);
    this->qgti = new QGraphicsTextItem("Fornite CIR2 Rennes");
    this->addItem(qgti);
    QGraphicsPixmapItem* qgpi = new QGraphicsPixmapItem(QPixmap("img.png"));
    this->addItem(qgpi);
    qgpi->setPos(50, 100);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30); //toutes les 30 millisecondes
}

MyScene::~MyScene() {

}

void MyScene::update()
{
    QPointF pos = qgti->pos(); //récupération de la position de l'objet qgti
    qgti->setPos(pos.rx(), pos.ry()+1); //incrémentation de la coordonnée y
    if (qgti->collidesWithItem(qgri)) {
     qDebug() << "Collision !";
    }
}
void MyScene::keyPressEvent(QKeyEvent* event){
 if(event->key() == Qt::Key_Space) { // appui sur la touche espace du clavier
    qDebug() << "Touche espace appuyée";
 }
}

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);


    this->viewPerso = new QGraphicsView();
    this->viewPerso->setScene(mainScene);
    this->viewPerso->setWindowTitle("Perso");
    this->viewPerso->resize(1200,925);
    this->viewPerso->show();


    this->setWindowTitle("Le Jeu du Turfu");



    this->setCentralWidget(mainView);
    //this->setFixedSize(900, 900);
    this->resize(900,900);

    helpMenu = menuBar()->addMenu(tr("&A Propos"));
    QAction* actionHelp = new QAction(tr("&T'es prêt ?"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);



}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("Tu sors ? Ou je te sors ?!");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

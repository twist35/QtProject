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
    /*this->viewPerso->setMinimumSize(1200,925);
    this->viewPerso->setMaximumSize(1200,925);*/
    this->viewPerso->setFixedSize(900,900);

    this->setWindowTitle("Le Jeu du Turfu");


    this->setCentralWidget(mainView);
    //this->setFixedSize(900, 900);
    this->resize(900,900);

    helpMenu = menuBar()->addMenu(tr("&A Propos"));
    QAction* actionHelp = new QAction(tr("&T'es prêt ?"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

    QVBoxLayout* layout = new QVBoxLayout(viewPerso);
    this->scoreLabel = new QLabel("<h1>Score : 0\'00\"</h1>");
    layout->addWidget(this->scoreLabel);
    layout->addStretch(1);

    /*QLabel* scoreLabel = new QLabel("<h1>Score : 0000</h1>",this->viewPerso);
    scoreLabel->move(100,100);*/

    this->scoreTimer = new QTimer(this);
    connect(this->scoreTimer, SIGNAL(timeout()), this, SLOT(updateScore()));
    this->scoreTimer->start(1000);

    this->scoreFile = new QFile("Qt.txt");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!this->scoreFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "erreur ouverture de fichier";
        return;
    }


    QTextStream ecriture(scoreFile);
    ecriture.setCodec("UTF-8");
    //ecriture << "Bonjour," << "\n" << "Nous sommes le " << 3 << " avril " << 2009;

    QTextStream lecture(scoreFile);
    scoreFile->seek(0);
    qDebug() << lecture.readAll();
    /*while(!ecriture.atEnd())
    {
        QString line = lecture.readLine();//lecture lligne par ligne qui marche pas
        qDebug() << line + "\n";
    }*/
}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("Tu sors ? Ou je te sors ?!");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::updateScore()
{
    this->setScore(this->getScore() + 1);

    this->temps_s++;
    if(this->temps_s > 60)
    {
        this->temps_m++;
        this->temps_s = 0;
    }
    //qDebug() << this->getScore();
    //this->scoreLabel->setText("<h1>Score : " + QString::number(this->getScore()) + "</h1>");
    this->scoreLabel->setText("<h1>Score : " + QString::number(this->temps_m) + "\'"+ QString::number(this->temps_s)+ "\""+"</h1>");
}
void MainWindow::saveScore()
{

}

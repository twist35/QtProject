#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);


    this->viewPerso = new QGraphicsView();
    this->viewPerso->setScene(mainScene);
    this->viewPerso->setWindowTitle("Perso");
    this->viewPerso->setWindowIcon(QIcon(":/images/ico"));
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
    QAction* actionHelp = new QAction(tr("&Surprise ?"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

    QVBoxLayout* layout = new QVBoxLayout(viewPerso);
    this->scoreLabel = new QLabel("<h1>Score : 0\'00\"</h1>");
    layout->addWidget(this->scoreLabel);

    this->scoreTimer = new QTimer(this);
    connect(this->scoreTimer, SIGNAL(timeout()), this, SLOT(updateScore()));
    this->scoreTimer->start(1000); // pour incémenter d'une seconde à chaque fois

    this->gameTimer = new QTimer(this);
    connect(this->gameTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
    this->gameTimer->start(20); // =50fps



    this->highScoreLabel = new QLabel("<h1>Highscore : 0\'00\"</h1>");
    layout->addWidget(this->highScoreLabel);
    layout->addStretch(1);

    this->scoreFile = new QFile("score.txt");
    //this->scoreFile = new QFile(":/data/score"); // ne fonctionne pas, on garde en fichier dans le dossier debug
    if (!this->scoreFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "erreur ouverture de fichier";
        return;
    }

    this->diagMenu = new QDialog;
    this->vLayoutMenu = new QVBoxLayout(diagMenu);
    this->messageMenu = new QLabel("default");
    this->vLayoutMenu->addWidget(this->messageMenu);
    this->hLayoutMenu = new QHBoxLayout();
    this->vLayoutMenu->addLayout(this->hLayoutMenu);
    this->buttonRePlay = new QPushButton("Rejouer");
    this->buttonQuit = new QPushButton("Quittez");
    this->hLayoutMenu->addWidget(this->buttonRePlay);
    this->hLayoutMenu->addWidget(this->buttonQuit);
    this->diagMenu->setModal(true);


    //this->diagMenu->hide();
}


void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("Tu sors ? Ou je te sors ?!");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::updateScore()
{
    if (!this->mainScene->perso->getIsWon())
    {
        this->setScore(this->getScore() + 1);

        float m =floor(this->getScore()/60); //calcul des minutes

        this->scoreLabel->setText("<h1>Score : " + QString::number(m) + "\'"+ QString::number(this->getScore()-60*m)+ "\""+"</h1>");
    }
}

void MainWindow::saveScore()
{
    this->checkHighScore();


    if(this->score < this->highScore)
    {
        qDebug() << this->scoreFile->resize(0); // ecrase ce qui était ecris avant (l'ancien Hscore)
        QTextStream ecriture(scoreFile);
        ecriture.setCodec("UTF-8");
        ecriture << this->getScore() <<endl;
    }
}

void MainWindow::updateGame()
{
    QObject::connect(this->buttonQuit, SIGNAL(clicked()), this, SLOT(closef()));
    QObject::connect(this->buttonRePlay, SIGNAL(clicked()), this, SLOT(restart()));


    if (this->mainScene->perso->getIsWin() && !this->mainScene->perso->getIsWon()) // si le joueur est arrivé à la fin
    {
        this->mainScene->perso->setIsWon(true);
        this->saveScore();
        this->menu();
    }

    checkHighScore();
}

// pr récupérer le HighScore
void MainWindow::checkHighScore()
{

    this->scoreFile->seek(0);
    QTextStream lecture(this->scoreFile);

    QString line;
    while(!lecture.atEnd())
    {
        line = lecture.readLine();//lecture lligne par ligne
    }
    //qDebug() << line.split("\n")[0].toInt(); //
    this->highScore = line.split("\n")[0].toInt(); // pr enlever le retour à la ligne ettransformation en int

    float m = floor(this->highScore/60); // décompostion en minutes

    this->highScoreLabel->setText("<h1>Highscore : " + QString::number(m) + "\'"+ QString::number(this->highScore - m*60)+ "\""+"</h1>");
}
void MainWindow::menu()
{
    this->diagMenu->setWindowTitle("Menu");
    this->diagMenu->setFixedSize(200, 150);

    if(this->mainScene->perso->getIsWin())
    {
        this->messageMenu->setText("<strong> Bien joué !! <br> Vous Avez gagné <br>Que voulez vous faire ?</strong>");
    }

   this->diagMenu->show();
}

void MainWindow::closef() // on close le programme
{
    qDebug() << "test";
    exit(0); // on force mais au moins ça marche
}
void MainWindow::restart() // on redémarra la partie
{
    this->mainScene->perso->setPos(0,500);
    this->setScore(0);
    this->mainScene->perso->setCountJump(0);
    this->mainScene->perso->setIsJump(false);
    this->mainScene->perso->setVoidAbove(true);
    this->mainScene->perso->setVoidBelow(true);
    this->mainScene->perso->setIsWin(false);
    this->mainScene->perso->setIsWon(false);

    this->diagMenu->hide();
}

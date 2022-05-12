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
    if (!this->scoreFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "erreur ouverture de fichier";
        return;
    }


}

MainWindow::~MainWindow(){
    this->scoreFile->close();
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

    if (this->mainScene->perso->getIsWin()) // si le joueur est arrivé à la fin
        this->saveScore();
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

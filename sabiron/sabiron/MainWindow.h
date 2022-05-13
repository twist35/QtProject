#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H


#include "includes.h"
#include "MyScene.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QGraphicsView* viewPerso;
    QMenu* helpMenu;
    QTimer* scoreTimer;
    QTimer* gameTimer;
    QLabel* scoreLabel;
    QLabel* highScoreLabel;
    int score = 0;
    int highScore = 0;
    QFile* scoreFile;
    QDialog* diagMenu;
    QVBoxLayout* vLayoutMenu;
    QLabel* messageMenu;
    QHBoxLayout* hLayoutMenu;
    QPushButton* buttonRePlay;
    QPushButton* buttonQuit;

public:
    MainWindow(QWidget* parent = nullptr);
    //virtual ~MainWindow();
    int getScore(){return this->score;}
    void setScore(int nScore){this->score = nScore;}
    int getHighScore(){return this->highScore;}
    void setHighScore(int nScore){this->highScore = nScore;}
    void saveScore();
    void checkHighScore();
    void menu();

public slots:
    void slot_aboutMenu();
    void updateScore();
    void updateGame();
    void restart();
    void closef();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H

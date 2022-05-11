#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H


#include "MyScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QGraphicsView* viewPerso;
    QMenu* helpMenu;
    QTimer* scoreTimer;
    int score = 0;
    QLabel* scoreLabel;
    int temps_m = 0;
    int temps_s = 0;
    QFile* scoreFile;


public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
    int getScore(){return this->score;}
    void setScore(int nScore){this->score = nScore;}

public slots:
    void slot_aboutMenu();
    void updateScore();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H

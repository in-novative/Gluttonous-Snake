#include "game.h"
#include "mainwindow.h"
#include "interface.h"

game::game(int i){
    switch (i){
        case 1 : {
            soloChallenge();
            break;
        }
    }
}

game::~game(){
    delete _maze;
    _maze = nullptr;
    delete  _snack;
    _snack = nullptr;
    delete  _star;
    _star = nullptr;
    delete elapsedTimer;
    elapsedTimer = nullptr;
    //qDebug() << "game destruct";
}

void game::soloChallenge(){
    //qDebug() << "soloChallenge called";
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    _maze = new maze(mazeLength, mazeWidth);
    _snack = new snack(_maze, 0.1*SECOND);
    _star = new star(5*SECOND, 10*SECOND);

    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

    QObject::connect(_snack->getTimer(), &QTimer::timeout, [=]() {
        //qint64 elapsed = elapsedTimer->elapsed();d
        //qDebug() << "Elapsed time: " << elapsed << " ms";

        QChar operation = window->readKeyboard(DIRECTION2QChar(3 - _snack->getSnackTowards()));
        if(operation == '0'){
            operation = DIRECTION2QChar(_snack->getSnackTowards());
        }
        DIRECTION _operation = (operation=='a') ? LEFT
                                : (operation=='w') ? UP
                                : (operation=='s') ? DOWN
                                : (operation=='d') ? RIGHT
                                : _snack->getSnackTowards();

        MAZE_TYPE target = _snack->move(_operation);
        if(target == STAR){
            int misc = QRandomGenerator::global()->bounded(2*SECOND, 5*SECOND);
            _star->getTimer(1)->setInterval(misc);

            _star->timerStart(1);
            _star->timerStop(2);
        }
        else if(target==WALL){
            _star->timerStop(1);
            _star->timerStop(2);
            _snack->timerStop();
            crash("YOU HIT A WALL!");
        }
        else if(target==SNACK_HEAD || target==SNACK_BODY){
            _star->timerStop(1);
            _star->timerStop(2);
            _snack->timerStop();
            crash("YOU HIT YOUR BODY!");
        }
    });

    QObject::connect(_star->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while(1){
            x = QRandomGenerator::global()->bounded(1, mazeLength-1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth-1);
            if(_maze->getMaze(x, y) == BLANK)
                break;
        }
        _star->setStarPosition(x, y);
        _maze->modifyMaze(x, y, STAR);

        int misc = QRandomGenerator::global()->bounded(5*SECOND, 10*SECOND);
        _star->getTimer(2)->setInterval(misc);

        _star->timerStop(1);
        _star->timerStart(2);
    });

    QObject::connect(_star->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _star->getStarPosition().first;
        uint y = _star->getStarPosition().second;
        _star->timerStop(2);
        _maze->flashMaze(x, y, 2*SECOND, 0.4*SECOND, WALL);

        QTimer::singleShot(2*SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(2*SECOND, 5*SECOND);
            _star->getTimer(1)->setInterval(misc);
            _star->timerStart(1);
        });
    });
}

void crash(QString error_msg){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(window, "crashed", error_msg + "\nDo you want to continue?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        userInterface->endGame();
        window->clearImages();
        userInterface->startGame(1);
    } else {
        userInterface->endGame();
        window->clearImages();
        userInterface->beginInterface();
    }
}

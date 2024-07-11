#include "game.h"

void soloChallenge(){
    qDebug() << "soloChallenge called";
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    auto _maze = new maze(mazeLength, mazeWidth);
    auto _snack = new snack(_maze, 0.1*SECOND);
    auto _star = new star(5*SECOND, 10*SECOND);

    auto elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();


    QObject::connect(_snack->getTimer(), &QTimer::timeout, [=]() {
        qint64 elapsed = elapsedTimer->elapsed();
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
        _maze->modifyMaze(x, y, WALL);

        int misc = QRandomGenerator::global()->bounded(2*SECOND, 5*SECOND);
        _star->getTimer(1)->setInterval(misc);

        _star->timerStart(1);
        _star->timerStop(2);
    });
}

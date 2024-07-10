#include "game.h"

game::game(int misc){
    timer.setInterval(misc);
}

void soloChallenge(){
    qDebug() << "soloChallenge called";
    QVBoxLayout *layout = getMainWindowLayout();

    auto _G = new game(100);
    auto _M = new maze(mazeLength, mazeWidth);
    auto _S1 = new snack(_M);

    _G->timerStart();

    QObject::connect(_G->getTimer(), &QTimer::timeout, [=]() {
        QChar operation = window->readKeyboard(DIRECTION2QChar(5 - _S1->getSnackTowards()));
        if(operation == '0'){
            operation = DIRECTION2QChar(_S1->getSnackTowards());
        }
        DIRECTION _operation = (operation=='a') ? LEFT
                                : (operation=='w') ? UP
                                : (operation=='s') ? DOWN
                                : (operation=='d') ? RIGHT
                                : _S1->getSnackTowards();
        _S1->move(_operation);
    });
}

#ifndef GAME_H
#define GAME_H

#include "QtHeader.h"
#include "maze.h"
#include "snack.h"
#include "star.h"

class game{
public:
    game(int i);
    ~game();
    void soloChallenge();
private:
    maze* _maze = nullptr;
    snack* _snack = nullptr;
    star* _star = nullptr;
    QElapsedTimer * elapsedTimer = nullptr;
};

void crash(QString error_msg);

#endif // GAME_H

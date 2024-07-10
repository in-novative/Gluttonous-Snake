#ifndef GAME_H
#define GAME_H

#include "QtHeader.h"
#include "maze.h"
#include "snack.h"

class game{
public:
    game(int misc);
    inline void timerStart() { timer.start(); }
    inline void timerStop() { timer.stop(); }
    inline bool timerActive() { return timer.isActive(); }
    inline QTimer* getTimer() { return &timer; }
private:
    QTimer timer;
};

void soloChallenge();

#endif // GAME_H

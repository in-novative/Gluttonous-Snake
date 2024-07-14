#ifndef GAME_H
#define GAME_H

#include "QtHeader.h"
#include "maze.h"
#include "snack.h"
#include "star.h"

class game {
public:
    game(int i);
    ~game();
    void soloChallenge();
    void timeChallengeWithoutBomb();
protected:
    bool paused;
    maze* _maze = nullptr;
    snack* _snack = nullptr;
    star* _star = nullptr;
    bomb* _bomb = nullptr;
    sun* _sun=nullptr;
    QElapsedTimer * elapsedTimer = nullptr;
    QTimer* updateTimer;
    void updateScore(int timeElapsed);
    void resetStar();
    void handleCollision(QString errorMessage,int score,qint64 gameTime,uint type);
    void pauseGame(uint type);
    void resumeGame(uint type);
};

#endif // GAME_H

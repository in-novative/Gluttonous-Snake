#ifndef SNACK_H
#define SNACK_H
#include "QtHeader.h"
#include "maze.h"

typedef class snack {
public:
    snack(mazePtr M, int misc, int leftKey = Qt::Key_A, int upKey = Qt::Key_W, int rightKey = Qt::Key_D, int downKey = Qt::Key_S);
    ~snack();
    MAZE_TYPE move(DIRECTION D);
    void modify_snack();
    inline DIRECTION getSnackTowards() { return snack_towards; }
    inline uint getSnackLength() { return snack_length; }
    inline void timerStart() { timer.start(); }
    inline void timerStop() { timer.stop(); }
    inline bool timerActive() { return timer.isActive(); }
    inline QTimer* getTimer() { return &timer; }

private:
    std::deque<position> snack_body;                        //front=>head, back=>tail
    DIRECTION snack_towards = DIRECTION::UP;                //Movement in the opposite DIRECTION from [towards] is not allowed
    uint snack_length = 3;
    mazePtr M = nullptr;
    QTimer timer;
    int leftKey, upKey, rightKey, downKey;                   // Add key bindings for players
}*snackPtr;

#endif // SNACK_H

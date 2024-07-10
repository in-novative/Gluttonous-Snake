#ifndef SNACK_H
#define SNACK_H
#include "QtHeader.h"
#include "maze.h"

typedef class snack{
public:
    snack(mazePtr M);
    ~snack();
    void move(DIRECTION D);
    void modify_snack();
    void crash(QString error_msg);
    inline DIRECTION getSnackTowards() { return snack_towards; }
    inline uint getSnackLength() { return snack_length; }

private:
    std::deque<position> snack_body;                        //front=>head, back=>tail
    DIRECTION snack_towards = DIRECTION::UP;                //Movement in the opposite DIRECTION from [towards] is not allowed
    uint snack_length = 3;
    mazePtr M = nullptr;
}*snackPtr;

#endif // SNACK_H

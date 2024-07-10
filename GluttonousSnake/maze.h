#ifndef MAZE_H
#define MAZE_H

#include "QtHeader.h"

typedef class maze{
public:
    maze(uint length, uint width);
    ~maze();
    bool modifyMaze(uint x, uint y, MAZE_TYPE i);                           //Modify types other than WALL
    void drawMaze();                                                        //draw the entire maze
    void drawMaze(uint position_x, uint position_y, uint length, uint width, uint image);                       //draw the specific position of maze
    QString getImagePath(uint type);
    inline uint getMazeLength() { return maze_length; }
    inline uint getMazeWidth() { return maze_width; }
    inline MAZE_TYPE getMaze(uint x, uint y) { return _maze[x][y]; }

private:
    uint maze_length = 0, maze_width = 0, wall_num = 0;
    MAZE_TYPE **_maze = nullptr;
}*mazePtr;


#endif // MAZE_H

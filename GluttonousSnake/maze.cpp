#include "maze.h"

QVector<QPixmap> MazeImages;

maze::maze(uint length, uint width) : maze_length(length), maze_width(width)
{
    qDebug() << "maze called";
    /*maze initialization,size is [maze_length] * [maze_width]
    the outermost ring is initialized as a {WALL}, and the rest are {BLANK}*/
    _maze = new MAZE_TYPE*[maze_length];
    for(uint i=0; i<maze_length; ++i){
        _maze[i] = new MAZE_TYPE[maze_width];
    }
    for(uint i=0; i<maze_length; ++i){
        for(uint j=0; j<maze_width; ++j){
            if(i==0 || i==maze_length-1 || j==0 || j==maze_width-1){
                _maze[i][j] = MAZE_TYPE::WALL;
                ++wall_num;
            }
            else
                _maze[i][j] = MAZE_TYPE::BLANK;
        }
    }
    for(int i=0; i<MAZE_TYPE::M_COUNT; i++){
        QPixmap pixmap(getImagePath(i));
        MazeImages.push_back(pixmap);
    }
    drawMaze();
}

maze::~maze(){
    for(uint i=0; i<maze_length; ++i){
        delete(_maze[i]);
    }
    delete(_maze);
}

bool maze::modifyMaze(uint x, uint y, MAZE_TYPE i){
    if(_maze[x][y] != MAZE_TYPE::WALL){
        _maze[x][y] = i;
        drawMaze(XORIGIN+x*GRID, YORIGIN+y*GRID, GRID, GRID, i);
        if(i == MAZE_TYPE::WALL)
            ++wall_num;
        return true;
    }
    else
        return false;
}

void maze::drawMaze(){
    for(uint i=0; i<maze_length; ++i){
        for(uint j=0; j<maze_width; ++j){
            drawMaze(XORIGIN+i*GRID, YORIGIN+j*GRID, GRID, GRID, _maze[i][j]);
        }
    }
}

void maze::drawMaze(uint position_x, uint position_y, uint length, uint width, uint image){
    window->paintImage(MazeImages[image], position_x, position_y, length, width);
}

QString maze::getImagePath(uint type){
    switch(type){
        case WALL:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\wall.png";
        }
        case BLANK:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\blank.jpg";
        }
        case STAR:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\star.png";
        }
        case SNACK_HEAD:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\snack.jpg";
        }
        case SNACK_BODY:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\snack.jpg";
        }
        case SNACK_TAIL:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\snack.jpg";
        }
        case PROP:{
            return "C:\\Users\\0range\\Desktop\\Gluttonous Snake\\image\\blank.jpg";
        }
    }
    return "";
}

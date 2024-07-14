#include "maze.h"
#include "mainwindow.h"

QVector<QPixmap> MazeImages;

maze::maze(uint length, uint width) : maze_length(length), maze_width(width)
{
    //qDebug() << "maze called";
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
        _maze[i] = nullptr;
    }
    delete(_maze);
    _maze = nullptr;
    //qDebug() << "maze destruct";
}

bool maze::modifyMaze(uint x, uint y, uint i){
    if(_maze[x][y] != MAZE_TYPE::WALL){
        _maze[x][y] = static_cast<MAZE_TYPE>(i);
        drawMaze(XORIGIN+x*GRID, YORIGIN+y*GRID, GRID, GRID, i);
        if(i == MAZE_TYPE::WALL)
            ++wall_num;
        return true;
    }
    else
        return false;
}

void maze::flashMaze(uint x, uint y, int duration, int interval, uint final){
    auto tmp = new uint;
    *tmp = _maze[x][y];

    QTimer *timer = new QTimer;
    timer->start(interval);

    QTimer::singleShot(duration, [=](){
        if(_maze[x][y]==STAR || _maze[x][y]==PROP|| _maze[x][y]==BOMB|| _maze[x][y]==SUN){
            modifyMaze(x, y, final);
        }
        QObject::disconnect(timer, nullptr, nullptr, nullptr);
        delete timer;
        return ;
    });

    QObject::connect(timer, &QTimer::timeout, [=](){
        if(_maze[x][y]==STAR || _maze[x][y]==PROP|| _maze[x][y]==BOMB|| _maze[x][y]==SUN){
            *tmp = (*tmp==_maze[x][y]) ? BLANK : _maze[x][y];
            drawMaze(XORIGIN+x*GRID, YORIGIN+y*GRID, GRID, GRID, *tmp);
        }
    });
}

void maze::drawMaze(){
    drawMaze(XORIGIN, YORIGIN, mazeLength*GRID, mazeWidth*GRID, BACKGROUND);
}

void maze::drawMaze(uint position_x, uint position_y, uint length, uint width, uint image){
    window->paintImage(MazeImages[image], position_x, position_y, length, width);
}

QString maze::getImagePath(uint type){
    switch(type){
        case BACKGROUND:{
            return ":/image/background.png";
        }
        case WALL:{
            return ":/image/wall.png";
        }
        case BLANK:{
            return ":/image/blank.png";
        }
        case STAR:{
            return ":/image/star.jpg";
        }
        case SNACK_HEAD_UP:{
            return ":/image/head_up.jpg";
        }
        case SNACK_HEAD_DOWN:{
            return ":/image/head_down.jpg";
        }
        case SNACK_HEAD_LEFT:{
            return ":/image/head_left.jpg";
        }
        case SNACK_HEAD_RIGHT:{
            return ":/image/head_right.jpg";
        }
        case SNACK_BODY:{
            return ":/image/body.jpg";
        }
        case SNACK_TAIL:{
            return ":/image/body.jpg";
        }
        case PROP:{
            return ":/image/blank.jpg";
        }
        case BOMB:{
            return ":/image/bomb.png";
        }
        case SUN:{
            return ":/image/sun.png";
        }
    }
    return "";
}

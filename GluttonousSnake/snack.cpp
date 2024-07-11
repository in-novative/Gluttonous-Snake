#include "snack.h"
#include "game.h"
#include "interface.h"
#include "mainwindow.h"

snack::snack(mazePtr M, int misc) : M(M){
    uint x = M->getMazeLength() / 2;
    uint y = M->getMazeWidth() / 2;

    snack_body.push_front(std::make_pair(x, y+1));
    snack_body.push_front(std::make_pair(x, y));
    snack_body.push_front(std::make_pair(x, y-1));
    M->modifyMaze(x, y-1, MAZE_TYPE::SNACK_HEAD_UP);
    M->modifyMaze(x, y, MAZE_TYPE::SNACK_BODY);
    M->modifyMaze(x, y+1, MAZE_TYPE::SNACK_TAIL);

    timer.setInterval(misc);
    timer.start();
};

snack::~snack(){
    M = nullptr;
    snack_body.clear();
    //qDebug() << "snack destruct";
}

MAZE_TYPE snack::move(DIRECTION D){
    if(snack_towards + D == 3)                      //The direction of movement is opposite to the direction of the snake's head
        D = snack_towards;

    uint head_x = (D == DIRECTION::LEFT) ? snack_body.begin()->first - 1
                  : (D == DIRECTION::RIGHT) ? snack_body.begin()->first + 1
                                            : snack_body.begin()->first;
    uint head_y = (D == DIRECTION::UP) ? snack_body.begin()->second - 1
                  : (D == DIRECTION::DOWN) ? snack_body.begin()->second + 1
                                           : snack_body.begin()->second;

    MAZE_TYPE result = M->getMaze(head_x, head_y);

    switch (M->getMaze(head_x, head_y)){
        case MAZE_TYPE::WALL : {
            //crash("YOU HIT A WALL !");
            break;
        }
        case MAZE_TYPE::SNACK_TAIL :
        case MAZE_TYPE::BLANK : {
            snack_body.pop_back();
            snack_body.push_front(std::make_pair(head_x, head_y));
            modify_snack();
            break;
        }
        case MAZE_TYPE::STAR : {
            snack_body.push_front(std::make_pair(head_x, head_y));
            ++snack_length;
            modify_snack();
            break;
        }
        case MAZE_TYPE::SNACK_HEAD_UP :
        case MAZE_TYPE::SNACK_HEAD_DOWN :
        case MAZE_TYPE::SNACK_HEAD_LEFT :
        case MAZE_TYPE::SNACK_HEAD_RIGHT :
        case MAZE_TYPE::SNACK_BODY : {
            //crash("YOU HIT YOUR BODY!");
            break;
        }
        case MAZE_TYPE::PROP : {
            //todo
            break;
        }
        default :
            break;
        }
    snack_towards = D;
    return result;
}

void snack::modify_snack(){
    M->modifyMaze(snack_body.begin()->first, snack_body.begin()->second, SNACK_HEAD_LEFT+snack_towards);
    M->modifyMaze(std::next(snack_body.begin(), 1)->first, std::next(snack_body.begin(), 1)->second, MAZE_TYPE::SNACK_BODY);
    M->modifyMaze(std::prev(snack_body.end(), 1)->first, std::prev(snack_body.end(), 1)->second, MAZE_TYPE::SNACK_TAIL);
    M->modifyMaze(snack_body.end()->first, snack_body.end()->second, MAZE_TYPE::BLANK);
}

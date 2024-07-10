#ifndef QTHEADER_H
#define QTHEADER_H

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <QPair>
#include <QKeyEvent>
#include <QTimer>
#include <fstream>
#include <utility>
#include <deque>
#include <string>
#include <iterator>
#include "mainwindow.h"

#define interfaceLength 1400
#define interfaceWidth 1000
#define mazeLength 30
#define mazeWidth 18
#define GRID 40
#define XORIGIN 100
#define YORIGIN 250

using uint = unsigned int;
using position = std::pair<uint, uint>;

enum DIRECTION{
    LEFT = 1,
    UP,
    DOWN,
    RIGHT,
    D_COUNT
};

enum MAZE_TYPE{
    WALL = 0,
    BLANK,
    STAR,
    SNACK_HEAD,
    SNACK_BODY,
    SNACK_TAIL,
    PROP,
    M_COUNT
};

extern QVector<QPixmap> MazeImages;

void clearLabelsAndButtons(QLayout* layout);
QVBoxLayout* getMainWindowLayout();
QChar DIRECTION2QChar(uint d);

#endif // QTHEADER_H

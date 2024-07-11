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
#include <QMessageBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <fstream>
#include <utility>
#include <deque>
#include <string>
#include <iterator>

#define interfaceLength 700
#define interfaceWidth 500
#define mazeLength 30
#define mazeWidth 18
#define GRID 20
#define XORIGIN 50
#define YORIGIN 125
#define SECOND 1000

using uint = unsigned int;
using position = std::pair<uint, uint>;

enum DIRECTION{
    LEFT = 0,
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

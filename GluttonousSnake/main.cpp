#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "interface.h"
#include "mainwindow.h"

MainWindow *window;
QApplication *app;

int main(int argc, char *argv[]) {
    QApplication _app(argc, argv);
    MainWindow _window;
    window = &_window;
    app = &_app;

    window->setWindowTitle("贪吃蛇游戏");
    window->resize(interfaceLength, interfaceWidth);

    beginInterface();
    window->show();
    return app->exec();
}

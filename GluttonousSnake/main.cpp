#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include "interface.h"
#include "mainwindow.h"

MainWindow *window;
QApplication *app;
interface *userInterface;

int main(int argc, char *argv[]) {
    QApplication _app(argc, argv);

    // 获取并打印当前工作目录
    QString currentPath = QDir::currentPath();
    qDebug() << "Current working directory:" << currentPath;

    QDir::setCurrent(QCoreApplication::applicationDirPath());  // 设置当前工作目录为可执行文件所在目录

    // 再次获取并打印设置后的工作目录
    currentPath = QDir::currentPath();
    qDebug() << "New working directory:" << currentPath;

    MainWindow _window;
    window = &_window;
    app = &_app;

    window->setWindowTitle("贪吃蛇游戏");
    window->resize(interfaceLength, interfaceWidth);

    userInterface = new interface();
    userInterface->beginInterface();
    window->show();
    return app->exec();
}

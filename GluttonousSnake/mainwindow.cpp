#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintImage(QPixmap image, uint x, uint y, uint width, uint height){
    images.append(qMakePair(image, QRect(x, y, width, height)));
    update();
}

QChar MainWindow::readKeyboard(const QChar skip){
    QChar result;
    for(int i=0; i<keyText.size(); ++i){
        if(keyText.at(i)=='w' || keyText.at(i)=='a' || keyText.at(i)=='s' || keyText.at(i)=='d'){
            if(keyText.at(i) != skip){
                result = keyText.at(i);
                break;
            }
        }
    }
    keyText.clear();
    return result;
}

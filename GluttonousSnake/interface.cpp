#include "interface.h"
#include "mainwindow.h"

interface::interface(){}

interface::~interface(){
    delete _game;
    _game = nullptr;
    //qDebug() << "interface destruct";
}

void interface::beginInterface() {
    //qDebug() << "beginInterface called";

    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);
    QLabel *label = new QLabel("贪吃蛇大作战", window);
    label->setAlignment(Qt::AlignCenter);
    QFont font1("Arial", 40);
    label->setFont(font1);
    layout->addWidget(label);

    QPushButton *button1 = new QPushButton("开始游戏", window);
    QPushButton *button2 = new QPushButton("查看排行榜", window);
    QPushButton *button3 = new QPushButton("帮助", window);
    QPushButton *button4 = new QPushButton("退出游戏", window);

    QFont font2("Arial", 15);
    button1->setFont(font2);
    button2->setFont(font2);
    button3->setFont(font2);
    button4->setFont(font2);

    label->setGeometry(450, 250, 500, 100);
    button1->setGeometry(550, 450, 300, 70);
    button2->setGeometry(550, 550, 300, 70);
    button3->setGeometry(550, 650, 300, 70);
    button4->setGeometry(550, 750, 300, 70);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);

    QObject::connect(button1, &QPushButton::clicked, [&]() { gameInterface(); });
    QObject::connect(button2, &QPushButton::clicked, [&]() { rankInterface(); });
    QObject::connect(button3, &QPushButton::clicked, [&]() { helpInterface(); });
    QObject::connect(button4, &QPushButton::clicked, &QCoreApplication::quit);

    window->update();
}

void interface::gameInterface() {
    //qDebug() << "gameInterface called";
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    QLabel *label = new QLabel("贪吃蛇大作战", window);
    label->setAlignment(Qt::AlignCenter);
    QFont font1("Arial", 40);
    label->setFont(font1);
    layout->addWidget(label);

    QPushButton *button1 = new QPushButton("单人闯关", window);
    QPushButton *button2 = new QPushButton("双人合作", window);
    QPushButton *button3 = new QPushButton("双人对战", window);

    QFont font2("Arial", 15);
    button1->setFont(font2);
    button2->setFont(font2);
    button3->setFont(font2);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    QObject::connect(button1, &QPushButton::clicked, [this](){
        startGame(1);
    });

    window->update();
}

void interface::rankInterface(){
    //qDebug() << "rankInterface called";
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);
    return ;
}

void interface::helpInterface(){
    //qDebug() << "helpInterface called";
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);
    return ;
}

QVBoxLayout* getMainWindowLayout(){
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(window->centralWidget()->layout());
    if (!layout) {
        layout = new QVBoxLayout(window);
        window->centralWidget()->setLayout(layout);
    } else {
        clearLabelsAndButtons(layout);
    }
    return layout;
}

void clearLabelsAndButtons(QLayout* layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0))){
        QWidget *widget = item->widget();
        if (widget) {
            if (qobject_cast<QLabel*>(widget) || qobject_cast<QPushButton*>(widget)) {
                delete widget;
            } else {
                layout->addWidget(widget);
            }
        }
        delete item;
    }
}

QChar DIRECTION2QChar(uint d){
    QChar result = (d == LEFT) ? 'a'
                    : (d == UP) ? 'w'
                    : (d == RIGHT) ? 'd'
                    : (d == DOWN) ? 's'
                    : '0';
    return result;
};

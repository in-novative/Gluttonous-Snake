#include "interface.h"
#include "mainwindow.h"
#include "CustomWidget.h"
#include <fstream>
#include <string>
#include <qdir.h>
interface::interface(){}

interface::~interface(){
    delete _game;
    _game = nullptr;
    //qDebug() << "interface destruct";
}

void interface::beginInterface() {
    // 创建自定义的 CustomWidget 作为中央小部件
    CustomWidget *centralWidget = new CustomWidget(window);
    centralWidget->setBackgroundImage(":image/1.png");  // 替换为图片的实际路径
    centralWidget->setShowBackground(true);
    window->setCentralWidget(centralWidget);

    // 创建一个 QVBoxLayout 作为中央小部件的布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);
    centralWidget->setLayout(mainLayout);

    // 添加标题标签
    QLabel *titleLabel = new QLabel("           ", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 40);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // 创建按钮并设置字体
    QPushButton *button1 = new QPushButton("开始游戏", centralWidget);
    QPushButton *button2 = new QPushButton("查看排行榜", centralWidget);
    QPushButton *button3 = new QPushButton("帮助", centralWidget);
    QPushButton *button4 = new QPushButton("退出游戏", centralWidget);

    QFont buttonFont("Arial", 15);
    button1->setFont(buttonFont);
    button2->setFont(buttonFont);
    button3->setFont(buttonFont);
    button4->setFont(buttonFont);

    // 将按钮添加到布局
    mainLayout->addWidget(button1);
    mainLayout->addWidget(button2);
    mainLayout->addWidget(button3);
    mainLayout->addWidget(button4);

    // 连接按钮信号与槽
    QObject::connect(button1, &QPushButton::clicked, [&]() { gameInterface(); });
    QObject::connect(button2, &QPushButton::clicked, [&]() { rankInterface(); });
    QObject::connect(button3, &QPushButton::clicked, [&]() { helpInterface(); });
    QObject::connect(button4, &QPushButton::clicked, &QCoreApplication::quit);

    window->update();
}

void interface::gameInterface() {
    CustomWidget *centralWidget = dynamic_cast<CustomWidget*>(window->centralWidget());
    if (!centralWidget) {
        qWarning() << "Error: centralWidget is not a CustomWidget!";
        return;
    }

    centralWidget->setShowBackground(true);

    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    QLabel *label = new QLabel("            ", window);
    label->setAlignment(Qt::AlignCenter);
    QFont font1("Arial", 40);
    label->setFont(font1);
    layout->addWidget(label);

    QPushButton *button1 = new QPushButton("单人闯关", window);
    QPushButton *button2 = new QPushButton("限时模式", window);
    QPushButton *backButton = new QPushButton("返回主菜单", window);

    QFont font2("Arial", 15);
    button1->setFont(font2);
    button2->setFont(font2);
    backButton->setFont(font2);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(backButton);

    QObject::connect(button1, &QPushButton::clicked, [this, centralWidget]() {
        centralWidget->setShowBackground(false); // 隐藏背景图
        clearLabelsAndButtons(getMainWindowLayout()); // 移除所有控件
        startGame(1);
    });
    QObject::connect(button2, &QPushButton::clicked, [this, centralWidget]() {
        centralWidget->setShowBackground(false); // 隐藏背景图
        clearLabelsAndButtons(getMainWindowLayout()); // 移除所有控件
        startGame(2);
    });
    QObject::connect(backButton, &QPushButton::clicked, [&]() { beginInterface(); });

    window->update();
}

void interface::rankInterface(){
    //qDebug() << "rankInterface called";

    CustomWidget *centralWidget = dynamic_cast<CustomWidget*>(window->centralWidget());
    if (!centralWidget) {
        qWarning() << "Error: centralWidget is not a CustomWidget!";
        return;
    }

    // 设置背景图片路径
    centralWidget->setBackgroundImage(":/image/help.png");  // 替换为实际图片路径
    centralWidget->setShowBackground(true);

    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);
    qDebug() << "Current working directory:" << QDir::currentPath();

    QLabel *label = new QLabel("排行榜", window);
    label->setAlignment(Qt::AlignCenter);
    QFont font1("Arial", 30);
    label->setFont(font1);
    layout->addWidget(label);

    const char* filePath = ":/resource/ranks.txt";
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            QString qLine = QString::fromStdString(line);
            QLabel *rankLabel = new QLabel(qLine, window);
            QFont font2("Arial", 15);
            rankLabel->setFont(font2);
            layout->addWidget(rankLabel);
        }
        file.close();
    } else {
        QLabel *noDataLabel = new QLabel("无法打开排行榜文件或文件不存在", window);
        QFont font2("Arial", 15);
        noDataLabel->setFont(font2);
        layout->addWidget(noDataLabel);
    }
    QPushButton *backButton = new QPushButton("返回主菜单", window);
    QFont font2("Arial", 15);
    backButton->setFont(font2);
    layout->addWidget(backButton);

    QObject::connect(backButton, &QPushButton::clicked, [&]() { beginInterface(); });

    window->update();

    return ;
}

void interface::helpInterface(){
    //qDebug() << "helpInterface called";

    CustomWidget *centralWidget = dynamic_cast<CustomWidget*>(window->centralWidget());
    if (!centralWidget) {
        qWarning() << "Error: centralWidget is not a CustomWidget!";
        return;
    }

    // 设置背景图片路径
    centralWidget->setBackgroundImage(":image/help.png");  // 替换为实际图片路径
    centralWidget->setShowBackground(true);

    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);
    QLabel *label = new QLabel("帮助信息"
                               "\n\n欢迎来到贪吃蛇游戏的帮助界面", window);
    label->setAlignment(Qt::AlignCenter);
    QFont font1("Arial", 15);
    label->setFont(font1);
    layout->addWidget(label);//设置窗口信息

    QLabel *helpText = new QLabel(
                                  "\n\n贪吃蛇控制方式：\n- W: 上\n- S: 下\n- A: 左\n- D: 右"
                                  "\n\n游戏玩法：\n使用wasd控制贪吃蛇移动，空格暂停游戏\n吃到星星获取分数，撞墙、咬到蛇身、吃到炸弹会终止游戏\n吃到太阳会使当前游戏得分翻倍"
                                  "\n\n游戏团队：\nZJU-24summer-gluttonous_team"
                                  "\n团队成员:Jie and He and Zhang", window);
    helpText->setAlignment(Qt::AlignLeft);
    QFont font2("Arial", 10);
    helpText->setFont(font2);
    layout->addWidget(helpText);
    //设置返回按钮
    QPushButton *backButton = new QPushButton("返回主菜单", window);
    backButton->setFont(font2);
    layout->addWidget(backButton);

    QObject::connect(backButton, &QPushButton::clicked, [&]() { beginInterface(); });
    window->update();
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

#include "game.h"
#include "mainwindow.h"
#include "interface.h"
#include "CustomWidget.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

game::game(int i) {
    switch (i) {
    case 1: {
        soloChallenge();
        break;
    }
    case 2: {
        timeChallengeWithoutBomb();
        break;
    }
    }
}

game::~game() {
    delete _sun;
    _sun = nullptr;
    delete _bomb;
    _bomb = nullptr;
    delete _maze;
    _maze = nullptr;
    delete _snack;
    _snack = nullptr;
    delete _star;
    _star = nullptr;
    delete elapsedTimer;
    elapsedTimer = nullptr;
    delete updateTimer;
    updateTimer = nullptr;
    //qDebug() << "game destruct";
}

struct Ranking {
    int score;
    qint64 gameTime; // 使用 qint64 存储时间
};

void readRankings(std::vector<Ranking>& rankings);
void writeRankings(const std::vector<Ranking>& rankings);
void updateRankings(int score, qint64 gameTime);

/*void game::soloChallenge() {
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    auto scoreLabel = new QLabel("分数: 0");
    auto timeLabel = new QLabel("时间: 0s");
    layout->addWidget(scoreLabel);
    layout->addWidget(timeLabel);

    _maze = new maze(mazeLength, mazeWidth);
    _snack = new snack(_maze, 0.1 * SECOND);
    _star = new star(5 * SECOND, 10 * SECOND);
    _bomb = new bomb(10 * SECOND, 15 * SECOND);
    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

    int score = 0;
    paused = false;
    //定时器
    updateTimer = new QTimer();
    QObject::connect(updateTimer, &QTimer::timeout, [this, timeLabel]() {
        if (!elapsedTimer) {
            qDebug() << "elapsedTimer 是空指针!";
            return;
        }
        qint64 elapsed = elapsedTimer->elapsed(); // 使用 elapsedTimer 计算时间
        timeLabel->setText("时间: " + QString::number(elapsed / 1000) + "s");
    });
    updateTimer->start(1000); // 每秒更新一次

    QObject::connect(_snack->getTimer(), &QTimer::timeout, [=]() mutable {
        if (paused) return;
        QChar operation = window->readKeyboard(DIRECTION2QChar(3 - _snack->getSnackTowards()));
        if (operation == '0') {
            operation = DIRECTION2QChar(_snack->getSnackTowards());
        }

        DIRECTION _operation = (operation == 'a') ? LEFT
                               : (operation == 'w') ? UP
                               : (operation == 's') ? DOWN
                               : (operation == 'd') ? RIGHT
                                                    : _snack->getSnackTowards();

        MAZE_TYPE target = _snack->move(_operation);
        if (target == STAR) {
            int snakeLength = _snack->getSnackLength();
            int points = snakeLength * 3; // 根据实际需求调整得分计算逻辑
            score += points;
            scoreLabel->setText("分数: " + QString::number(score));
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _star->getTimer(1)->setInterval(misc);

            _star->timerStart(1);
            _star->timerStop(2);
        } else if (target == WALL) {
            qint64 elapsed = elapsedTimer->elapsed() / 100000;
            handleCollision("你撞墙了!", score, elapsed, BOMB);
        } else if (SNACK_HEAD_LEFT<=target && target<=SNACK_BODY) {
            qint64 elapsed = elapsedTimer->elapsed() / 100000;
            handleCollision("你撞到自己的身体了!", score, elapsed, BOMB);
        } else if (target == BOMB) {
            qint64 elapsed = elapsedTimer->elapsed();
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _bomb->getTimer(1)->setInterval(misc);

            _bomb->timerStart(1);
            _bomb->timerStop(2);
            handleCollision("你吃到了炸弹!", score, elapsed, BOMB);
        }
    });

    QObject::connect(_star->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while (true) {
            x = QRandomGenerator::global()->bounded(1, mazeLength - 1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth - 1);
            if (_maze->getMaze(x, y) == BLANK)
                break;
        }
        _star->setStarPosition(x, y);
        _maze->modifyMaze(x, y, STAR);

        int misc = QRandomGenerator::global()->bounded(5 * SECOND, 10 * SECOND);
        _star->getTimer(2)->setInterval(misc);

        _star->timerStop(1);
        _star->timerStart(2);
    });

    QObject::connect(_star->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _star->getStarPosition().first;
        uint y = _star->getStarPosition().second;
        _star->timerStop(2);
        _maze->flashMaze(x, y, 2 * SECOND, 0.4 * SECOND, WALL);

        QTimer::singleShot(3 * SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _star->getTimer(1)->setInterval(misc);
            _star->timerStart(1);
        });
    });

    QObject::connect(_bomb->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while (true) {
            x = QRandomGenerator::global()->bounded(1, mazeLength - 1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth - 1);
            if (_maze->getMaze(x, y) == BLANK)
                break;
        }
        _bomb->setBombPosition(x, y);
        _maze->modifyMaze(x, y, BOMB);

        int misc = QRandomGenerator::global()->bounded(10 * SECOND, 15 * SECOND);
        _bomb->getTimer(2)->setInterval(misc);

        _bomb->timerStop(1);
        _bomb->timerStart(2);
    });

    QObject::connect(_bomb->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _bomb->getBombPosition().first;
        uint y = _bomb->getBombPosition().second;
        _bomb->timerStop(2);
        _maze->flashMaze(x, y, 2 * SECOND, 0.4 * SECOND, WALL);

        QTimer::singleShot(3 * SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _bomb->getTimer(1)->setInterval(misc);
            _bomb->timerStart(1);
        });
    });

    QObject::connect(window, &MainWindow::spacePressed, [=]() mutable {
        if (paused) {
            resumeGame(BOMB);
        } else {
            pauseGame(BOMB);
        }
    });
}*/

void game::soloChallenge() {
    /*CustomWidget *gameWidget = dynamic_cast<CustomWidget*>(window->centralWidget());
    if (!gameWidget) {
        qWarning() << "Error: gameWidget is not a CustomWidget!";
        return;
    }

    // 清除现有的布局和控件
    clearLabelsAndButtons(gameWidget->layout());

    QWidget *overlayWidget = gameWidget;
    QVBoxLayout *layout = new QVBoxLayout(overlayWidget);
    overlayWidget->setLayout(layout);*/

    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    // 添加分数和时间标签
    //auto scoreLabel = new QLabel("分数: 0", overlayWidget);
    //auto timeLabel = new QLabel("时间: 0s", overlayWidget);
    auto scoreLabel = new QLabel("分数: 0");
    auto timeLabel = new QLabel("时间: 0s");
    layout->addWidget(scoreLabel);
    layout->addWidget(timeLabel);

    // 迷宫、蛇、星星和炸弹的初始化代码
    _maze = new maze(mazeLength, mazeWidth);
    _snack = new snack(_maze, 0.1 * SECOND);
    _star = new star(5 * SECOND, 10 * SECOND);
    _bomb = new bomb(10 * SECOND, 15 * SECOND);
    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

    int score = 0;
    paused = false;

    // 定时器和事件连接代码
    updateTimer = new QTimer();
    QObject::connect(updateTimer, &QTimer::timeout, [this, timeLabel]() {
        if (!elapsedTimer) {
            qDebug() << "elapsedTimer 是空指针!";
            return;
        }
        qint64 elapsed = elapsedTimer->elapsed();
        timeLabel->setText("时间: " + QString::number(elapsed / 1000) + "s");
    });
    updateTimer->start(1000);

    QObject::connect(_snack->getTimer(), &QTimer::timeout, [=]() mutable {
        if (paused) return;
        QChar operation = window->readKeyboard(DIRECTION2QChar(3 - _snack->getSnackTowards()));
        if (operation == '0') {
            operation = DIRECTION2QChar(_snack->getSnackTowards());
        }

        DIRECTION _operation = (operation == 'a') ? LEFT
                               : (operation == 'w') ? UP
                               : (operation == 's') ? DOWN
                               : (operation == 'd') ? RIGHT
                                                    : _snack->getSnackTowards();

        MAZE_TYPE target = _snack->move(_operation);
        if (target == STAR) {
            int snakeLength = _snack->getSnackLength();
            int points = snakeLength * 3;
            score += points;
            scoreLabel->setText("分数: " + QString::number(score));
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _star->getTimer(1)->setInterval(misc);

            _star->timerStart(1);
            _star->timerStop(2);
        } else if (target == WALL) {
            qint64 elapsed = elapsedTimer->elapsed() / 100000;
            handleCollision("你撞墙了!", score, elapsed, BOMB);
        } else if (SNACK_HEAD_LEFT <= target && target <= SNACK_BODY) {
            qint64 elapsed = elapsedTimer->elapsed() / 100000;
            handleCollision("你撞到自己的身体了!", score, elapsed, BOMB);
        } else if (target == BOMB) {
            qint64 elapsed = elapsedTimer->elapsed();
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _bomb->getTimer(1)->setInterval(misc);

            _bomb->timerStart(1);
            _bomb->timerStop(2);
            handleCollision("你吃到了炸弹!", score, elapsed, BOMB);
        }
    });

    // 其他事件连接和逻辑
    QObject::connect(_star->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while (true) {
            x = QRandomGenerator::global()->bounded(1, mazeLength - 1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth - 1);
            if (_maze->getMaze(x, y) == BLANK)
                break;
        }
        _star->setStarPosition(x, y);
        _maze->modifyMaze(x, y, STAR);

        int misc = QRandomGenerator::global()->bounded(5 * SECOND, 10 * SECOND);
        _star->getTimer(2)->setInterval(misc);

        _star->timerStop(1);
        _star->timerStart(2);
    });

    QObject::connect(_star->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _star->getStarPosition().first;
        uint y = _star->getStarPosition().second;
        _star->timerStop(2);
        _maze->flashMaze(x, y, 2 * SECOND, 0.4 * SECOND, WALL);

        QTimer::singleShot(3 * SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _star->getTimer(1)->setInterval(misc);
            _star->timerStart(1);
        });
    });

    QObject::connect(_bomb->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while (true) {
            x = QRandomGenerator::global()->bounded(1, mazeLength - 1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth - 1);
            if (_maze->getMaze(x, y) == BLANK)
                break;
        }
        _bomb->setBombPosition(x, y);
        _maze->modifyMaze(x, y, BOMB);

        int misc = QRandomGenerator::global()->bounded(10 * SECOND, 15 * SECOND);
        _bomb->getTimer(2)->setInterval(misc);

        _bomb->timerStop(1);
        _bomb->timerStart(2);
    });

    QObject::connect(_bomb->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _bomb->getBombPosition().first;
        uint y = _bomb->getBombPosition().second;
        _bomb->timerStop(2);
        _maze->flashMaze(x, y, 2 * SECOND, 0.4 * SECOND, WALL);

        QTimer::singleShot(3 * SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _bomb->getTimer(1)->setInterval(misc);
            _bomb->timerStart(1);
        });
    });

    QObject::connect(window, &MainWindow::spacePressed, [=]() mutable {
        if (paused) {
            resumeGame(BOMB);
        } else {
            pauseGame(BOMB);
        }
    });
}

void game::timeChallengeWithoutBomb() {
    QVBoxLayout *layout = getMainWindowLayout();
    clearLabelsAndButtons(layout);

    auto scoreLabel = new QLabel("分数: 0");
    auto timeLabel = new QLabel("时间: 0s");
    auto countdownLabel = new QLabel("剩余时间: 600s");
    layout->addWidget(scoreLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(countdownLabel);

    _maze = new maze(mazeLength, mazeWidth);
    _snack = new snack(_maze, 0.1 * SECOND);
    _sun = new sun(20 * SECOND, 30 * SECOND); // 初始化太阳道具，每 20 秒出现一次，持续 30 秒
    _star = new star(5 * SECOND, 10 * SECOND);
    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

    int score = 0;
    paused = false;

    // 定时器
    updateTimer = new QTimer();
    QObject::connect(updateTimer, &QTimer::timeout, [this, timeLabel, countdownLabel, &score]() {
        if (!elapsedTimer) {
            qDebug() << "elapsedTimer 是空指针!";
            return;
        }
        qint64 elapsed = elapsedTimer->elapsed(); // 使用 elapsedTimer 计算时间
        timeLabel->setText("时间: " + QString::number(elapsed / 1000) + "s");
        qint64 timeLeft = 600 - elapsed / 1000;
        countdownLabel->setText("剩余时间: " + QString::number(timeLeft) + "s");

        if (timeLeft <= 0) {
            handleCollision("时间到!", score, elapsed / 1000, SUN);
        }
    });
    updateTimer->start(1000); // 每秒更新一次

    QObject::connect(_snack->getTimer(), &QTimer::timeout, [=]() mutable {
        if (paused) return;
        QChar operation = window->readKeyboard(DIRECTION2QChar(3 - _snack->getSnackTowards()));
        if (operation == '0') {
            operation = DIRECTION2QChar(_snack->getSnackTowards());
        }

        DIRECTION _operation = (operation == 'a') ? LEFT
                               : (operation == 'w') ? UP
                               : (operation == 's') ? DOWN
                               : (operation == 'd') ? RIGHT
                                                    : _snack->getSnackTowards();

        MAZE_TYPE target = _snack->move(_operation);
        if (target == STAR) {
            int snakeLength = _snack->getSnackLength();
            int points = snakeLength * 3; // 根据实际需求调整得分计算逻辑
            score += points;
            scoreLabel->setText("分数: " + QString::number(score));
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _star->getTimer(1)->setInterval(misc);

            _star->timerStart(1);
            _star->timerStop(2);
        } else if (target == SUN) {
            score *= 2;
            scoreLabel->setText("分数: " + QString::number(score));
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _sun->getTimer(1)->setInterval(misc);

            _sun->timerStart(1);
            _sun->timerStop(2);
        } else if (target == WALL) {
            qint64 elapsed = elapsedTimer->elapsed() / 100000;
            handleCollision("你撞墙了!", score, elapsed, SUN);
        } else if (SNACK_HEAD_LEFT<=target && target<=SNACK_BODY) {
            qint64 elapsed = elapsedTimer->elapsed()/100000;
            handleCollision("你撞到自己的身体了!", score, elapsed, SUN);
        }
    });

    QObject::connect(_sun->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while (true) {
            x = QRandomGenerator::global()->bounded(1, mazeLength - 1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth - 1);
            if (_maze->getMaze(x, y) == BLANK)
                break;
        }
        _sun->setSunPosition(x, y);
        _maze->modifyMaze(x, y, SUN);

        int misc = QRandomGenerator::global()->bounded(10 * SECOND, 15 * SECOND);
        _sun->getTimer(2)->setInterval(misc);

        _sun->timerStop(1);
        _sun->timerStart(2);
    });

    QObject::connect(_star->getTimer(1), &QTimer::timeout, [=]() {
        uint x, y;
        while (true) {
            x = QRandomGenerator::global()->bounded(1, mazeLength - 1);
            y = QRandomGenerator::global()->bounded(1, mazeWidth - 1);
            if (_maze->getMaze(x, y) == BLANK)
                break;
        }
        _star->setStarPosition(x, y);
        _maze->modifyMaze(x, y, STAR);

        int misc = QRandomGenerator::global()->bounded(5 * SECOND, 10 * SECOND);
        _star->getTimer(2)->setInterval(misc);

        _star->timerStop(1);
        _star->timerStart(2);
    });

    QObject::connect(_star->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _star->getStarPosition().first;
        uint y = _star->getStarPosition().second;
        _star->timerStop(2);
        _maze->flashMaze(x, y, 2 * SECOND, 0.4 * SECOND, WALL);

        QTimer::singleShot(3 * SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(2 * SECOND, 5 * SECOND);
            _star->getTimer(1)->setInterval(misc);
            _star->timerStart(1);
        });
    });

    QObject::connect(_sun->getTimer(2), &QTimer::timeout, [=]() {
        uint x = _sun->getSunPosition().first;
        uint y = _sun->getSunPosition().second;
        _sun->timerStop(2);
        _maze->flashMaze(x, y, 2 * SECOND, 0.4 * SECOND, WALL);

        QTimer::singleShot(3 * SECOND, [=]() {
            int misc = QRandomGenerator::global()->bounded(5 * SECOND, 10 * SECOND);
            _sun->getTimer(1)->setInterval(misc);
            _sun->timerStart(1);
        });
    });

    QObject::connect(window, &MainWindow::spacePressed, [=]() mutable {
        qDebug() << "空格键按下. 当前状态: " << (paused ? "暂停" : "运行");
        if (paused) {
            resumeGame(SUN);
        } else {
            pauseGame(SUN);
        }
    });
}

void game::handleCollision(QString errorMessage, int score, qint64 gameTime,uint type) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(window, "碰撞", errorMessage + "\n是否继续游戏？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        userInterface->endGame();
        window->clearImages();
        if(type==BOMB) userInterface->startGame(1);
        else if(type==SUN) userInterface->startGame(2);
    } else {
        updateRankings(score, gameTime);
        userInterface->endGame();
        window->clearImages();
        userInterface->beginInterface();
    }
}

void readRankings(std::vector<Ranking>& rankings) {
    std::string filePath = ":/resource/ranks.txt";
    std::fstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        std::cout << "read Error opening file" << std::endl;
        return;
    }
    else std::cout << "read opening file well" << std::endl;
    rankings.clear();
    int score;
    qint64 gameTime;
    while (file >> score >> gameTime) {
        std::cout << "read score=" << score << " gameTime=" << gameTime << std::endl;
        rankings.push_back({ score, gameTime });
    }
    std::cout << "read well" << std::endl;
    file.close();
}

void writeRankings(const std::vector<Ranking>& rankings) {
    std::string filePath = ":/resource/ranks.txt";
    std::fstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        std::cout << "write Error opening file" << std::endl;
        return;
    }
    else std::cout << "write opening file well" << std::endl;
    for (const auto& rank : rankings) {
        std::cout << "score=" << rank.score << " gameTime=" << rank.gameTime << std::endl;
        file << rank.score << " " << rank.gameTime << "\n";
        if (file.fail()) {
            qDebug() << "Failed to write to rankings file.";
            return;
        }
    }
    std::cout << "write well" << std::endl;
    file.close();
}

void updateRankings(int score, qint64 gameTime) {
    std::vector<Ranking> rankings;
    readRankings(rankings);
    std::cout << "score=" << score << " gameTime=" << gameTime << std::endl;
    rankings.push_back({ score, gameTime });
    std::sort(rankings.begin(), rankings.end(), [](const auto& a, const auto& b) {
        return a.score > b.score || (a.score == b.score && a.gameTime < b.gameTime);
    });

    if (rankings.size() > 10) {
        rankings.resize(10); // 只保留前十位
    }
    std::cout << "update well" << std::endl;
    writeRankings(rankings);
}

void game::pauseGame(uint type) {
    paused = true;
    updateTimer->stop();
    _snack->getTimer()->stop();
    _star->getTimer(1)->stop();
    _star->getTimer(2)->stop();
    if(type == BOMB) {
        _bomb->getTimer(1)->stop();
        _bomb->getTimer(2)->stop();
    } else if(type == SUN) {
        _sun->getTimer(1)->stop();
        _sun->getTimer(2)->stop();
    }
    QMessageBox pauseBox;
    pauseBox.setWindowTitle("游戏暂停");
    pauseBox.setText("游戏已暂停");
    QPushButton* mainMenuButton = pauseBox.addButton("主菜单", QMessageBox::ActionRole);
    QPushButton* continueButton = pauseBox.addButton("继续游戏", QMessageBox::ActionRole);
    QPushButton* newGameButton = pauseBox.addButton("新的游戏", QMessageBox::ActionRole);

    pauseBox.exec();

    if (pauseBox.clickedButton() == mainMenuButton) {
        userInterface->endGame();
        window->clearImages();
        userInterface->beginInterface();
    } else if (pauseBox.clickedButton() == continueButton) {
        resumeGame(type);
    } else if (pauseBox.clickedButton() == newGameButton) {
        userInterface->endGame();
        window->clearImages();
        if(type == BOMB) userInterface->startGame(1);
        else if(type == SUN) userInterface->startGame(2);
    }
}

void game::resumeGame(uint type) {
    paused = false;
    updateTimer->start(1000);
    _snack->getTimer()->start();
    if (_star->timerActive(1)) _star->getTimer(1)->start();
    if (_star->timerActive(2)) _star->getTimer(2)->start();
    if(type == BOMB) {
        if (_bomb->timerActive(1)) _bomb->getTimer(1)->start();
        if (_bomb->timerActive(2)) _bomb->getTimer(2)->start();
    } else if(type == SUN) {
        if (_sun->timerActive(1)) _sun->getTimer(1)->start();
        if (_sun->timerActive(2)) _sun->getTimer(2)->start();
    }
}

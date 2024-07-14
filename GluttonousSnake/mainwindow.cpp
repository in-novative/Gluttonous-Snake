#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取按钮和标签指针
    button = ui->pushButton;
    imageLabel = ui->imageLabel;

    // 加载图片
    QPixmap pixmap(":image/background.png");

    // 将图片设置到标签中
    imageLabel->setPixmap(pixmap);

    // 调整标签大小以适应图片
    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    // 创建一个垂直布局管理器
    QVBoxLayout *layout = new QVBoxLayout;

    // 将按钮和标签添加到布局中
    layout->addWidget(button);
    layout->addWidget(imageLabel);

    // 将布局设置为中央窗口小部件的布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintImage(QPixmap image, uint x, uint y, uint width, uint height)
{
    images.append(qMakePair(image, QRect(x, y, width, height)));
    update();
}

QChar MainWindow::readKeyboard(const QChar skip)
{
    QChar result;
    for(int i = 0; i < keyText.size(); ++i) {
        if(keyText.at(i) == 'w' || keyText.at(i) == 'a' || keyText.at(i) == 's' || keyText.at(i) == 'd') {
            if(keyText.at(i) != skip) {
                result = keyText.at(i);
                break;
            }
        }
    }
    keyText.clear();
    return result;
}



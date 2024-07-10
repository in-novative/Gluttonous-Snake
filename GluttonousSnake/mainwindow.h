#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtHeader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintImage(QPixmap image, uint x, uint y, uint width, uint height);
    QChar readKeyboard(QChar skip);

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        for (const auto &image : images) {
            painter.drawPixmap(image.second, image.first);
        }
    }
    void keyPressEvent(QKeyEvent *event) override {
        int key = event->key();
        keyText.append(QKeySequence(key).toString().toLower());
    }

private:
    Ui::MainWindow *ui;
    QVector<QPair<QPixmap, QRect>> images;
    QString keyText;
};

extern MainWindow *window;
extern QApplication *app;

#endif // MAINWINDOW_H

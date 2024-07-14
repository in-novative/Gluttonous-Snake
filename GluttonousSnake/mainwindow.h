#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtHeader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintImage(QPixmap image, uint x, uint y, uint width, uint height);
    QChar readKeyboard(QChar skip);
    inline void clearImages() { images.clear(); }

signals:
    void spacePressed();
    void keyPressEventOccurred(QKeyEvent* event);

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        for (const auto &image : images) {
            painter.drawPixmap(image.second, image.first);
        }
    }
    void keyPressEvent(QKeyEvent *event) override {
        int key = event->key();
        if (key == Qt::Key_Space) {
            emit spacePressed();
        } else {
            keyText.append(QKeySequence(key).toString().toLower());
            emit keyPressEventOccurred(event);
        }
    }

private:
    Ui::MainWindow *ui;
    QVector<QPair<QPixmap, QRect>> images;
    QString keyText;
    QPushButton *button;
    QLabel *imageLabel;
};

extern MainWindow *window;
extern QApplication *app;

#endif // MAINWINDOW_H

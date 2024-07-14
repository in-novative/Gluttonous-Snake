// CustomWidget.cpp
#include "CustomWidget.h"
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent), showBackground(true) {}

void CustomWidget::setBackgroundImage(const QString &imagePath) {
    backgroundPixmap.load(imagePath);
    update();
}

void CustomWidget::setShowBackground(bool show) {
    showBackground = show;
    update();
}

void CustomWidget::paintEvent(QPaintEvent *event) {
    if (showBackground) {
        QPainter painter(this);
        painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);
    }
    QWidget::paintEvent(event);
}

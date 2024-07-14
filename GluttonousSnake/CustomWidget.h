// CustomWidget.h
#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QPixmap>

class CustomWidget : public QWidget {
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = nullptr);
    void setBackgroundImage(const QString &imagePath);
    void setShowBackground(bool show);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap backgroundPixmap;
    bool showBackground;  // 控制是否显示背景图片
};

#endif // CUSTOMWIDGET_H

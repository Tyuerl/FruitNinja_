#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

#include <QTimer>
#include "apple.h"
#include "watermelon.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void                on_pushButton_clicked();
    void                resizeEvent(QResizeEvent *event) override;

private slots:
    void    AnimationFruit();
    void    GeneratorFruit();

    void on_buttonstart_clicked();

    void on_load_clicked();

private:
    Ui::Widget          *ui;
    int                 sizeFruit_;
    QGraphicsScene      *scene;
    QTimer              *gameTime;
    QTimer              *animationTimer;
    QList<Apple>        redApple;
    QList<Watermelon>   arbuz;
    int                 hp = 20;
    int                 point = 0;
    int                 record;
};
#endif // WIDGET_H

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
    void                isOn_pushButton_clicked();
    void                resizeEvent(QResizeEvent *event) override;
    void                isGameStart();
    void                isGameEnd();

private slots:
    void                isAnimationFruit();
    void                isGeneratorFruit();
    void                on_buttonstart_clicked();
    void                on_load_clicked();

signals:
    void isToRecord();

private:
    Ui::Widget          *mlsUi;
    int                 mlsSizeFruit_;
    QGraphicsScene      *mlsScene;
    QTimer              *mlsGameTime;
    QTimer              *mlsAnimationTimer;
    QList<IsFruit*>     mlsFruit;
    int                 mlsHp = 20;
    int                 mlsPoint = 0;
    int                 mlsRecord;
};
#endif // WIDGET_H

#ifndef APPLE_H
#define APPLE_H
#include "fruit.h"



class Apple :public Fruit
{
public:
    Apple();
    Apple(int x, int y);
    ~Apple();
    void    Move() override;
    QRectF  boundingRect() const override;
    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget = nullptr) override;

    // QGraphicsItem interface
};

#endif // APPLE_H

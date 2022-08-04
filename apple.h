#ifndef APPLE_H
#define APPLE_H
#include "fruit.h"

class IsApple :public IsFruit
{
public:
            IsApple();
            IsApple(int x, int y);
            ~IsApple();
    QRectF  boundingRect() const override;
    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget = nullptr) override;

    // QGraphicsItem interface
};

#endif // APPLE_H

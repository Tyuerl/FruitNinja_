#ifndef WATERMELON_H
#define WATERMELON_H

#include "fruit.h"

class IsWatermelon : public IsFruit
{
public:
            IsWatermelon();
            IsWatermelon(int x, int y);
            ~IsWatermelon();
    QRectF  boundingRect() const override;
    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget = nullptr) override;
};

#endif // WATERMELON_H

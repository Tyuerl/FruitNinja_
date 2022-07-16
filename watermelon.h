#ifndef WATERMELON_H
#define WATERMELON_H

#include "fruit.h"

class Watermelon : public Fruit
{
public:
    Watermelon();
    Watermelon(int x, int y);
    ~Watermelon();
    void    Move() override;
    QRectF  boundingRect() const override;
    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget = nullptr) override;
};

#endif // WATERMELON_H

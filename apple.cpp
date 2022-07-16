#include "apple.h"
//Apple::Apple() :Apple()
//{
 //   name_ = "Red Apple";
//}

#include "fruit.h"


Apple::Apple()  :Fruit()
{
    name_ = "Red Apple";
    color = QColor(Qt::yellow);
    this->setPos(posX_, posY_);
    hp = 5;
}


Apple::Apple(int x, int y)  :Fruit()
{
    name_ = "Red Apple";
    color = QColor(Qt::yellow);
    this->setPos(x, y);
    hp = 5;
}

Apple::~Apple()
{
}

void Apple::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    (void) option;
    (void) widget;
    if ((alive == 1) && pos() != QPointF(0, 0))
    {

        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(0, 0, SIZE, SIZE);

        painter->setBrush(QColor(210, 105, 30));
        QPen trianglePen = QPen();
        trianglePen.setColor(QColor(210, 105, 30));

        QPolygon triangle = QPolygon();
        triangle << QPoint(SIZE / 2 - 5, 0) << QPoint(SIZE / 2 + 5, 0)
                 << QPoint (SIZE / 2, 5);
        painter->setPen(trianglePen);
        painter->drawPolygon(triangle);

        QPen treePen = QPen();
        treePen.setColor(Qt::darkYellow);
        treePen.setWidth(4);
        QLine tree = QLine();
        tree.setP1(QPoint(SIZE / 2, 5));
        tree.setP2(QPoint(SIZE / 2 + 8, -30));
        painter->setPen(treePen);
        painter->drawLine(tree);
    }
    else if(alive == 3)
    {
        painter->setBrush(QColor(255, 255, 173));
        painter->drawEllipse(0, 0, 4 * SIZE / 5, SIZE);
        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(0, 0, SIZE / 3, SIZE);
        painter->drawEllipse(SIZE / 3, 0, SIZE / 2, SIZE);
    }
}

QRectF Apple::boundingRect() const
{
    return (Fruit::boundingRect());
}

void    Apple::Move ()
{
    Fruit::Move();

}


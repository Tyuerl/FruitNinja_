#include "apple.h"
//Apple::Apple() :Apple()
//{
 //   name_ = "Red Apple";
//}

#include "fruit.h"


IsApple::IsApple()  :IsFruit()
{
    mlsName_ = "Red IsApple";
    mlsColor = QColor(Qt::yellow);
    this->setPos(mlsPosX_, mlsPosY_);
    mlsHp = 5;
}


IsApple::IsApple(int x, int y)  :IsFruit()
{
    mlsName_ = "Yellow Apple";
    mlsColor = QColor(Qt::yellow);
    this->setPos(x, y);
    mlsHp = 5;
}

IsApple::~IsApple()
{
}

void IsApple::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    (void) option;
    (void) widget;
    if ((mlsAlive == isMoving) && pos() != QPointF(0, 0))
    {

        painter->setBrush(RED);
        painter->drawEllipse(0, 0, SIZE, SIZE);

        painter->setBrush(BROWN);
        QPen trianglePen = QPen();
        trianglePen.setColor(BROWN);
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
    else if(mlsAlive == isCutting)
    {
        painter->setBrush(QColor(255, 255, 173));
        painter->drawEllipse(0, 0, 4 * SIZE / 5, SIZE);
        painter->setBrush(RED);
        painter->drawEllipse(0, 0, SIZE / 3, SIZE);
        painter->drawEllipse(SIZE / 3, 0, SIZE / 2, SIZE);
    }
}

QRectF IsApple::boundingRect() const
{
    return (IsFruit::boundingRect());
}

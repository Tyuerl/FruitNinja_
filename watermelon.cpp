#include "watermelon.h"


IsWatermelon::IsWatermelon()  :IsFruit()
{
    mlsName_ = "Watermelon";
    mlsColor = QColor(Qt::green);
    this->setPos(mlsPosX_, mlsPosY_);
    mlsHp = 10;
}


IsWatermelon::IsWatermelon(int x, int y)  :IsFruit()
{
    mlsName_ = "Red IsWatermelon";
    mlsColor = QColor(Qt::yellow);
    this->setPos(x, y);
}

IsWatermelon::~IsWatermelon()
{
}

void IsWatermelon::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    (void) option;
    (void) widget;
    if ((mlsAlive == isMoving) && pos() != QPointF(0, 0))
    {

        painter->setBrush(QColor(1, 50, 32)); // темнозеленый
        painter->drawEllipse(0, 0, SIZE, SIZE - 10);
        painter->setBrush(QColor(4, 199, 127)); // светлый
        painter->drawEllipse(10, 0, SIZE - 20, SIZE - 10);
        painter->setBrush(QColor(1, 50, 32)); // темнозеленый
        painter->drawEllipse(20, 0, SIZE - 40, SIZE - 10);
        painter->setBrush(QColor(4, 199, 127)); // светлый
        painter->drawEllipse(35, 0, SIZE - 70, SIZE - 10);



   //     QPen treePen = QPen();
    //    treePen.setColor(Qt::darkYellow);
     ///   treePen.setWidth(4);
     //   QLine tree = QLine();
     //   tree.setP1(QPoint(SIZE / 2, 5));
     //   tree.setP2(QPoint(SIZE / 2 + 8, -30));
     //   painter->setPen(treePen);
      //  painter->drawLine(tree);
    }
    else if(mlsAlive == isCutting)
    {
        painter->setBrush(QColor(1, 50, 32)); // темнозеленый
        painter->drawEllipse(0, 0, SIZE, SIZE - 10);


        painter->setBrush(Qt::red);
        painter->drawEllipse(10, 0, SIZE - 10, SIZE - 10);
        painter->setBrush(QColor(210, 105, 30));
        painter->setPen(QColor(210, 105, 30));
        painter->drawRect(SIZE / 2, 0, SIZE / 2  + 10, SIZE);
    }
}

QRectF IsWatermelon::boundingRect() const
{
    return (IsFruit::boundingRect());
}


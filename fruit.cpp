#include "fruit.h"
#include <QDebug>
IsFruit::IsFruit()
{
    std:: srand(std::time(0));
    rand();
    mlsRotation = -200 + rand()% 400;
    mlsPosX_ = WIDTH / 6 + rand() % (5 * WIDTH / 6);
    mlsPosY_ = HEIGHT;// test
    setPos(mlsPosX_, mlsPosY_);
    if (mlsPosX_ > WIDTH / 3)
        mlsDeltaX_ = -(2 + rand() % (WIDTH / 2 / 2 / 30)); // 2sec - flight, 2 - 2 side, 30 - fps
    else
        mlsDeltaX_ = (2 + rand() % (WIDTH / 2 / 2 / 30));
    mlsGravitation = 9; // 9,806 65 :_)
    mlsDeltaY_ = 23  + rand() % 10 ;// +  rand() % 14;
    mlsAlive = isMoving;
}

IsFruit::IsFruit(int x, int y, QString name,
             int dely, int delx, int g,
             int rot, QColor clr, int hp)
{
    mlsPosX_ = x;
    mlsPosY_ = y;
    setPos(x, y);
    mlsName_ = name;
    mlsDeltaY_ = dely;
    mlsDeltaX_ = delx;
    mlsGravitation = g;
    mlsRotation = rot;
    mlsColor = clr;
    this->mlsHp = hp;
    mlsAlive = isMoving;
}

IsFruit::IsFruit(const IsFruit &go)
{
    IsFruit *q;
    q = go.Copy();

    mlsPosX_        = q->isPosx();
    mlsPosY_        = q->isPosy();
    mlsDeltaY_      = q->isDeltaY();
    mlsDeltaX_      = q->isDeltaX();
    mlsGravitation  = q->isGravitation();
    mlsRotation     = q->isRotation();
    mlsColor        = q->isColor();
    mlsName_        = q->isName();
    mlsHp           = q->isHp();
    mlsAlive        = q->isAlive();
    delete q;
}

IsFruit::~IsFruit()
{

}

QRectF IsFruit::boundingRect() const
{
    return (QRectF(0, 0, SIZE, SIZE));
}

IsFruit *IsFruit::Copy() const
{
    return new IsFruit(mlsPosX_, mlsPosY_, mlsName_, mlsDeltaY_,
                                mlsDeltaX_, mlsGravitation, mlsRotation,
                       mlsColor, mlsHp);
}

void IsFruit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)painter;
    (void)option;
    (void)widget;

}

IsFruit &IsFruit::operator =(const IsFruit& go)
{
    mlsPosX_       = go.isPosx();
    mlsPosY_       = go.isPosy();
    mlsDeltaY_     = go.isDeltaY();
    mlsDeltaX_     = go.isDeltaX();
    mlsGravitation = go.isGravitation();
    mlsRotation    = go.isRotation();
    mlsColor       = go.isColor();
    mlsName_       = go.isName();
    mlsHp          = go.isHp();
    mlsAlive       = go.isAlive();
    return (*this);
}

void IsFruit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    (void)event;
    //qDebug() << "you did a click";
    if (mlsAlive != isCutting)
        mlsAlive = isPoint;
}

int IsFruit::isAlive(bool thisForMoving)
{
    (void)thisForMoving;
    if (mlsPosY_ > HEIGHT   && mlsAlive == isMoving)
        mlsAlive = isDamaging;
    if (mlsPosY_ > HEIGHT   && mlsAlive == isCutting)
        mlsAlive = isDeleting;
    return (mlsAlive);
}

void IsFruit::isMove ()
{
    //static int count = 0;
    mlsPosX_ += mlsDeltaX_;
    mlsPosY_ -=mlsDeltaY_;
    mlsRotation++;
    setPos(mlsPosX_, mlsPosY_);
        mlsDeltaY_ -= mlsGravitation / 9;
    setRotation(isRotation() + mlsRotation);
}

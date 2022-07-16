#include "fruit.h"
#include <QDebug>
Fruit::Fruit()
{
    std:: srand(std::time(0));
    rotation = -200  + rand()% 400;
    posX_ = WIDTH / 6 + rand() % (5 * WIDTH / 6);
    posY_ = HEIGHT;// test
    setPos(posX_, posY_);
    if (posX_ > WIDTH / 3)
        deltaX_ = -(2 + rand() % (WIDTH / 2 / 2 / 30)); // 2sec - flight, 2 - 2 side, 30 - fps
    else
        deltaX_ = (2 + rand() % (WIDTH / 2 / 2 / 30));
    gravitation = 9; // 9,806 65 :_)
    deltaY_ = 15 + rand() % 15 ;// +  rand() % 14;
    alive = 1;
}

Fruit::Fruit(int x, int y, QString name,
             int dely, int delx, int g,
             int rot, QColor clr, int hp)
{
    posX_ = x;
    posY_ = y;
    setPos(x, y);
    name_ = name;
    deltaY_ = dely;
    deltaX_ = delx;
    gravitation = g;
    rotation = rot;
    color = clr;
    this->hp = hp;
    alive = 1;
}

Fruit::Fruit(const Fruit &go)
{
    Fruit *q;
    q = go.Copy();

    posX_       = q->Posx();
    posY_       = q->Posy();
    deltaY_     = q->DeltaY();
    deltaX_     = q->DeltaX();
    gravitation = q->Gravitation();
    rotation    = q->Rotation();
    color       = q->Color();
    name_       = q->Name();
    hp          = q->Hp();
    alive       = q->Alive();
    delete q;
}

QRectF Fruit::boundingRect() const
{
    return (QRectF(0, 0, SIZE, SIZE));
}

void Fruit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ;
}

Fruit *Fruit::Copy() const
{
    return new Fruit(posX_, posY_, name_, deltaY_,
                                deltaX_, gravitation, rotation,
                     color, hp);
}

Fruit &Fruit::operator =(const Fruit& go)
{
    posX_       = go.Posx();
    posY_       = go.Posy();
    deltaY_     = go.DeltaY();
    deltaX_     = go.DeltaX();
    gravitation = go.Gravitation();
    rotation    = go.Rotation();
    color       = go.Color();
    name_       = go.Name();
    hp          = go.Hp();
    alive       = go.Alive();
    return (*this);
}

void Fruit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "you do a click";
    if (alive != 3)
        alive = 2;
}

int Fruit::IsAlive()
{
    if (posY_ > HEIGHT && alive == 1)
        alive = -1;
    if (posY_ > HEIGHT && alive == 3)
        return (0);
    return (alive);
}

void Fruit::Move ()
{
    static int count = 0;
    posX_ += deltaX_;
    posY_ -=deltaY_;
    rotation++;
    setPos(posX_, posY_);
    count++;
    if (count % 4)
        deltaY_ -= gravitation / 9;
    setRotation(Rotation() + rotation);
}

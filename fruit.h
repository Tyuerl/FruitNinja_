#ifndef FRUIT_H
#define FRUIT_H

#include <QPainter>

#include <QWidget>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include <ctime>

#define WIDTH 1024
#define HEIGHT 576
#define SIZE WIDTH/12
//Интерфейс для всех фруктов
class Fruit : public QGraphicsItem
{
public:
    Fruit();
    Fruit(int x, int y, QString name, int dely,
          int delx, int g, int rot, QColor clr, int hp);
    Fruit(const Fruit& go);
    virtual void        paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget = nullptr) override;
    virtual void        Move();
  //virtual void        Slayer();
    virtual QRectF      boundingRect() const override;
    int                 IsAlive();
    virtual Fruit*      Copy() const;
    virtual Fruit&      operator =(const Fruit& go);
    void    setAlive(int n)   {alive = n;};
    //virtual           void advance(int phase) override;



protected:
    int                 posX_;
    int                 posY_;
    QString             name_;
    int                 deltaY_;
    int                 deltaX_;
    int                 gravitation;
    int                 rotation;
    QColor              color;
    int                 hp;
    int                alive; // -1 - need delete, 1 - exist, 2 - player destroy this fruit
public:
    int     Posx()          const   {return posX_;};
    int     Posy()          const   {return posY_;};
    int     DeltaY()        const   {return deltaY_;};
    int     DeltaX()        const   {return deltaX_;};
    int     Gravitation()   const   {return gravitation;};
    int     Hp()            const   {return hp;};
    int     Rotation ()     const   {return rotation;};
    QString Name ()         const   {return name_;};
    QColor  Color ()        const   {return color;};
    int     Alive()         const   {return (alive);};


    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // FRUIT_H

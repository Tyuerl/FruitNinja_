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

const int               WIDTH   = 1024;
const int               HEIGHT  = 576;
const int               SIZE    = WIDTH / 12;
const QColor            BROWN   = QColor(210, 105, 30);
const QColor            RED     = QColor(255, 0, 0);
//Интерфейс для всех фруктов
class IsFruit : public QGraphicsItem
{
public:
                        IsFruit();
                        IsFruit(int x, int y, QString name, int dely,
                                int delx, int g, int rot, QColor clr, int hp);
                        IsFruit(const IsFruit& go);
                        ~IsFruit();
    enum                enState {isMoving, isCutting, isDeleting, isDamaging, isPoint};
    int                 isAlive(bool thisForMoving);
    void                isSetAlive(int n)   {mlsAlive = n;};
    void                isMove();
    virtual QRectF      boundingRect() const override;
    virtual IsFruit&    operator =(const IsFruit& go);
    virtual IsFruit*    Copy() const;
    virtual void        paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget = nullptr) override;
protected:
    int                 mlsPosX_;
    int                 mlsPosY_;
    QString             mlsName_;
    int                 mlsDeltaY_;
    int                 mlsDeltaX_;
    int                 mlsGravitation;
    int                 mlsRotation;
    QColor              mlsColor;
    int                 mlsHp;
    int                 mlsAlive; // -1 - need delete, 1 - exist, 2 - player destroy this IsFruit
public:
    int                 isPosx()          const   {return mlsPosX_;};
    int                 isPosy()          const   {return mlsPosY_;};
    int                 isDeltaY()        const   {return mlsDeltaY_;};
    int                 isDeltaX()        const   {return mlsDeltaX_;};
    int                 isGravitation()   const   {return mlsGravitation;};
    int                 isHp()            const   {return mlsHp;};
    int                 isRotation ()     const   {return mlsRotation;};
    QString             isName ()         const   {return mlsName_;};
    QColor              isColor ()        const   {return mlsColor;};
    int                 isAlive()         const   {return (mlsAlive);};
protected:
    void                mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // FRUIT_H

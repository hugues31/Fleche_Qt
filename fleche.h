#ifndef Fleche_H
#define Fleche_H

#include <QGraphicsLineItem>

class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;

class Fleche : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    Fleche(QGraphicsPolygonItem *startItem, QGraphicsPolygonItem *endItem,
      QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);

    int type() const
        { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color)
        { myColor = color; }
    QGraphicsPolygonItem *startItem() const
        { return myStartItem; }
    QGraphicsPolygonItem *endItem() const
        { return myEndItem; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr);

private:
    QGraphicsPolygonItem *myStartItem;
    QGraphicsPolygonItem *myEndItem;
    QColor myColor;
    QPolygonF FlecheHead;
};

#endif

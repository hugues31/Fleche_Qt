#include <QtGui>

#include "fleche.h"
#include <math.h>

const qreal Pi = 3.14;

Fleche::Fleche(QGraphicsPolygonItem *startItem, QGraphicsPolygonItem *endItem,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent)
{
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;

    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Fleche::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Fleche::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(FlecheHead);
    return path;
}

void Fleche::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void Fleche::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal FlecheSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
    QPolygonF endPolygon = myEndItem->polygon();
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
    p2 = endPolygon.at(i) + myEndItem->pos();
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType =
        polyLine.intersect(centerLine, &intersectPoint);
    if (intersectType == QLineF::BoundedIntersection)
        break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, myStartItem->pos()));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

        QPointF FlecheP1 = line().p1() + QPointF(sin(angle + Pi / 3) * FlecheSize,
                                        cos(angle + Pi / 3) * FlecheSize);
        QPointF FlecheP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * FlecheSize,
                                        cos(angle + Pi - Pi / 3) * FlecheSize);

        FlecheHead.clear();
        FlecheHead << line().p1() << FlecheP1 << FlecheP2;
        painter->drawLine(line());
        painter->drawPolygon(FlecheHead);
        if (isSelected()) {
            painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}

#include "mapviewtarget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>



MapViewTarget::MapViewTarget(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setZValue(-1);
}

QRectF MapViewTarget::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10-adjust, -10-adjust, 23+adjust, 23+adjust);
}

void MapViewTarget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(1, Qt::darkRed);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

#ifndef MAPVIEWTARGET_H
#define MAPVIEWTARGET_H

#include <QGraphicsItem>

class MapViewTarget : public QGraphicsItem
{
public:
    explicit MapViewTarget(QGraphicsItem *parent = 0);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // MAPVIEWTARGET_H

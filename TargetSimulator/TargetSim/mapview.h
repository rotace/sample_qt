#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "baseview.h"

#include <QGraphicsView>

#include <mapviewtarget.h>


class QGraphicsViewImpl : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsViewImpl(QWidget *parent = 0) : QGraphicsView(parent) {
        this->scale(1.0, 1.0);
    }

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
#endif
};


class MapView : public BaseView
{
    Q_OBJECT
    QGraphicsView *mView;
    QList<MapViewTarget*> mList;

public:
    explicit MapView(QWidget *parent = 0);
    ~MapView();



    // BaseView interface
public:
    void updateTarget(int i, QVariant &v) Q_DECL_OVERRIDE;
    void insertTarget(int i) Q_DECL_OVERRIDE;
    void removeTarget(int i) Q_DECL_OVERRIDE;
};

#endif // MAPVIEW_H

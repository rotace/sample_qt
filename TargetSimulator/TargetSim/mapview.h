#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "baseview.h"

#include <QGraphicsView>

#include <mapviewtarget.h>

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
    void updateTarget(int i, BaseTarget &t) Q_DECL_OVERRIDE;
    void insertTarget(int i) Q_DECL_OVERRIDE;
};

#endif // MAPVIEW_H

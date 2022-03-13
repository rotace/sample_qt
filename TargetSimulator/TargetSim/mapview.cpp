#include "mapview.h"

#include <QtCore>

#include "mapviewtarget.h"

MapView::MapView(QWidget *parent)
    : BaseView(parent)
{
    mView = new QGraphicsView();
    mView->setParent(this);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setParent(mView);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    mView->setScene(scene);
    mView->setCacheMode(QGraphicsView::CacheBackground);
    mView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    mView->setRenderHint(QPainter::Antialiasing);
    mView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    mView->scale(qreal(0.8), qreal(0.8));
    mView->setMinimumSize(400, 400);
}

MapView::~MapView()
{
    while(!mList.isEmpty()) {
        MapViewTarget *t = mList.takeLast();
        delete t;
    }
}

void MapView::updateTarget(int i, BaseTarget &t)
{
    mList[i]->setPos(t.posX(), t.posY());
}

void MapView::insertTarget(int i)
{
    mList.insert(i, new MapViewTarget());
    mView->scene()->addItem(mList.at(i));
}

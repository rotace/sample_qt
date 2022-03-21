#include "mapview.h"

#include <QtCore>
#include <QtWidgets>

#include "mapviewtarget.h"


void QGraphicsViewImpl::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if(e->angleDelta().y() > 0)
            this->scale(1.1, 1.1);
        else
            this->scale(0.9, 0.9);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}


MapView::MapView(QWidget *parent)
    : BaseView(parent)
{
    QHBoxLayout * topLayout = new QHBoxLayout;
    this->setLayout(topLayout);

    mView = new QGraphicsViewImpl(this);
    mView->setDragMode(QGraphicsView::ScrollHandDrag);
    mView->setCacheMode(QGraphicsView::CacheBackground);
    mView->setRenderHint(QPainter::Antialiasing, false);
    mView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    mView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    mView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    topLayout->addWidget(mView);

    QGraphicsScene *scene = new QGraphicsScene();
//    qint32 area = 10000;
//    scene->setSceneRect(-area, -area, 2*area, 2*area);
    mView->setScene(scene);
}

MapView::~MapView()
{
    while(!mList.isEmpty()) {
        MapViewTarget *t = mList.takeLast();
        delete t;
    }
}

void MapView::updateTarget(int i, QVariant &v)
{
    if( !v.isValid() || !v.canConvert<BaseTarget>() ) return;
    BaseTarget t = v.value<BaseTarget>();
    mList[i]->setPos(t.posX(), -t.posY());
}

void MapView::insertTarget(int i)
{
    mList.insert(i, new MapViewTarget());
    mView->scene()->addItem(mList.at(i));
}


void MapView::removeTarget(int i)
{
    mView->scene()->removeItem(mList.takeAt(i));
}


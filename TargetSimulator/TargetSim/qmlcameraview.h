#ifndef QMLCAMERAVIEW_H
#define QMLCAMERAVIEW_H

#include "baseview.h"

#include <QImage>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <Qt3DQuick/QQmlAspectEngine>
#include "qmlwindow.h"

class QmlCameraView : public BaseView
{
    Q_OBJECT
    qreal mAlt;
    QImage mImage;
    QmlWindow *mWindow;
    Qt3D::Quick::QQmlAspectEngine *mEngine;

public:
    explicit QmlCameraView(QWidget *parent = 0);
    explicit QmlCameraView(qreal altitude, qreal elevAngleOfView, QSize pixelSize, bool isInputEnabled = false, QWidget *parent = 0);
    ~QmlCameraView();
    void updateView();
    qreal azim() const;
    qreal elev() const;
    QImage image() const { return mImage; }
    void close() { mWindow->close(); }
    void hide() { mWindow->setVisible(false); }
    void show() { mWindow->setVisible(true); }
    bool isVisible() { return mWindow->isVisible(); }
    void setCameraDirection(qreal azim, qreal elev);

    // BaseView interface
public:
    void updateTarget(int i, QVariant &v) Q_DECL_OVERRIDE;
    void insertTarget(int i) Q_DECL_OVERRIDE;
    void removeTarget(int i) Q_DECL_OVERRIDE;
};

#endif // QMLCAMERAVIEW_H

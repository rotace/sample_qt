#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "baseview.h"

#include <QtWidgets>
#include <Qt3DRenderer/QWindow>
#include <Qt3DRenderer/QMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QScaleTransform>
#include <Qt3DCore/QRotateTransform>
#include <Qt3DCore/QTranslateTransform>

class CameraView : public BaseView
{
    Q_OBJECT
    qreal mAlt;
    QImage mImage;
    QGraphicsView *mView;
    QGraphicsPixmapItem *mItem;
    Qt3D::QWindow *mWindow;
    Qt3D::QCamera *mCamera;
    Qt3D::QEntity *mRootEntity;
    Qt3D::QMaterial *mMaterial;
    QList<Qt3D::QEntity*> mEntityList;
    QList<Qt3D::QRotateTransform*> mRotateList;
    QList<Qt3D::QTranslateTransform*> mTranslateList;

public:
    explicit CameraView(QWidget *parent = 0);
    explicit CameraView(qreal altitude, qreal elevAngleOfView, QSize pixelSize, bool isInputEnabled = false, QWidget *parent = 0);
    ~CameraView();
    qreal azim() const;
    qreal elev() const;
    QImage image() const { return mImage; }
    void close() { mWindow->close(); }
    void hide() { mWindow->setVisible(false); }
    void show() { mWindow->setVisible(true); }
    bool isVisible() { return mWindow->isVisible(); }
    void setCameraDirection(qreal azim, qreal elev);

private:
    void updateView();

signals:

public slots:

    // BaseView interface
public:
    void updateTarget(int i, QVariant &v) Q_DECL_OVERRIDE;
    void insertTarget(int i) Q_DECL_OVERRIDE;
    void removeTarget(int i) Q_DECL_OVERRIDE;
};

#endif // CAMERAVIEW_H

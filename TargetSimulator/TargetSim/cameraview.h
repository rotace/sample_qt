#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "baseview.h"

#include <Qt3DRenderer/QWindow>
#include <Qt3DRenderer/QMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QScaleTransform>
#include <Qt3DCore/QRotateTransform>
#include <Qt3DCore/QTranslateTransform>

class CameraView : public BaseView
{
    Q_OBJECT
    Qt3D::QWindow *mWindow;
    Qt3D::QEntity *mRootEntity;
    Qt3D::QMaterial *mMaterial;
    QList<Qt3D::QEntity*> mEntityList;
    QList<Qt3D::QRotateTransform*> mRotateList;
    QList<Qt3D::QTranslateTransform*> mTranslateList;

public:
    explicit CameraView(QWidget *parent = 0);
    void close() { mWindow->close(); };

signals:

public slots:

    // BaseView interface
public:
    void updateTarget(int i, QVariant &v) Q_DECL_OVERRIDE;
    void insertTarget(int i) Q_DECL_OVERRIDE;
    void removeTarget(int i) Q_DECL_OVERRIDE;
};

#endif // CAMERAVIEW_H

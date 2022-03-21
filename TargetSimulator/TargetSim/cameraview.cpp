#include "cameraview.h"


#include <Qt3DCore/QCamera>
#include <Qt3DCore/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QLookAtTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRenderer/QRenderAspect>
#include <Qt3DRenderer/QFrameGraph>
#include <Qt3DRenderer/QForwardRenderer>
#include <Qt3DRenderer/QPhongMaterial>

#include <Qt3DRenderer/QCylinderMesh>
#include <Qt3DRenderer/QSphereMesh>
#include <Qt3DRenderer/QTorusMesh>

#include <QPropertyAnimation>

CameraView::CameraView(QWidget *parent)
    : BaseView(parent)
    , mWindow(new Qt3D::QWindow)
    , mRootEntity(new Qt3D::QEntity)
    , mMaterial(new Qt3D::QPhongMaterial(mRootEntity))
{
    Qt3D::QInputAspect *input = new Qt3D::QInputAspect;
    mWindow->registerAspect(input);

    Qt3D::QCamera *cameraEntity = mWindow->defaultCamera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 1.0f, 1.0f, 5000.0f);
    cameraEntity->setPosition(QVector3D(0, -400.0, 0));
    cameraEntity->setUpVector(QVector3D(0, 0, 1));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    input->setCamera(cameraEntity);

    mWindow->setRootEntity(mRootEntity);
    mWindow->resize(300, 200);
    mWindow->show();
}


void CameraView::updateTarget(int i, QVariant &v)
{
    if( !v.isValid() || !v.canConvert<BaseTarget>() ) return;
    BaseTarget t = v.value<BaseTarget>();
    mTranslateList[i]->setTranslation(QVector3D(t.posX(), t.posY(), 0.0));
}

void CameraView::insertTarget(int i)
{
    Qt3D::QEntity *entity = new Qt3D::QEntity(mRootEntity);

    Qt3D::QSphereMesh *mesh = new Qt3D::QSphereMesh;
    mesh->setRadius(3);

    Qt3D::QTransform *trans = new Qt3D::QTransform;
    Qt3D::QRotateTransform *rotate = new Qt3D::QRotateTransform;
    Qt3D::QTranslateTransform *move = new Qt3D::QTranslateTransform;
    rotate->setAxis(QVector3D(0, 1, 0));
    rotate->setAngleDeg(0.0);
    move->setTranslation(QVector3D(0, 0, 0));

    trans->addTransform(rotate);
    trans->addTransform(move);

    entity->addComponent(mesh);
    entity->addComponent(trans);
    entity->addComponent(mMaterial);

    mEntityList.insert(i, entity);
    mRotateList.insert(i, rotate);
    mTranslateList.insert(i, move);
}

void CameraView::removeTarget(int i)
{
    mEntityList.takeLast()->~QEntity();
    mRotateList.removeLast();
    mTranslateList.removeLast();
}

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

#include <QtCore>
#include <QtMath>

CameraView::CameraView(QWidget *parent)
    : CameraView(3.0, 45.0, QSize(480, 320), false, parent)
{
}

CameraView::CameraView(qreal altitude, qreal elevAngleOfView, QSize pixelSize, bool isInputEnabled, QWidget *parent)
    : BaseView(parent)
    , mAlt(altitude)
    , mView(new QGraphicsView(this))
    , mItem(new QGraphicsPixmapItem)
    , mWindow(new Qt3D::QWindow)
    , mCamera(mWindow->defaultCamera())
    , mRootEntity(new Qt3D::QEntity)
    , mMaterial(new Qt3D::QPhongMaterial(mRootEntity))
{
    QHBoxLayout * topLayout = new QHBoxLayout;
    this->setLayout(topLayout);

    mView->setScene(new QGraphicsScene);
    mView->setDragMode(QGraphicsView::ScrollHandDrag);
    mView->scene()->addItem(mItem);
    topLayout->addWidget(mView);

    if(isInputEnabled) {
        Qt3D::QInputAspect *input = new Qt3D::QInputAspect;
        mWindow->registerAspect(input);
        input->setCamera(mCamera);
    }

    mCamera->lens()->setPerspectiveProjection(elevAngleOfView, 1.0f, 1.0f, 5000.0f);
    mCamera->setPosition(QVector3D(0, 0, mAlt));
    mCamera->setUpVector(QVector3D(0, 0, 1));
    mCamera->setViewCenter(QVector3D(0, 1, mAlt));

    mWindow->setRootEntity(mRootEntity);
    mWindow->setFlags(Qt::WindowStaysOnTopHint);
    mWindow->resize(pixelSize);
    mWindow->setMinimumSize(pixelSize);
    mWindow->setMaximumSize(pixelSize);
    mWindow->show();
}

qreal CameraView::azim() const
{
    QVector3D delta = mCamera->viewCenter() - mCamera->position();
    return qRadiansToDegrees(qAtan2(delta.x(), delta.y()));
}

qreal CameraView::elev() const
{
    QVector3D delta = mCamera->viewCenter() - mCamera->position();
    return qRadiansToDegrees(qAsin(delta.z()));
}

void CameraView::setCameraDirection(qreal azim, qreal elev)
{
    mCamera->setViewCenter(QVector3D(
        qSin(qDegreesToRadians(azim)) * qCos(qDegreesToRadians(elev)),
        qCos(qDegreesToRadians(azim)) * qCos(qDegreesToRadians(elev)),
        qSin(qDegreesToRadians(elev)) + mAlt
    ));

    this->updateView();
}

void CameraView::updateView()
{
    qint32 sleep_msec = 10;
    QEventLoop loop;
    QTimer::singleShot( sleep_msec, &loop, SLOT( quit() ) );
    loop.exec();
    mImage = mWindow->screen()->grabWindow(mWindow->winId()).toImage().convertToFormat(QImage::Format_Grayscale8);
    mItem->setPixmap(QPixmap::fromImage(mImage));
}

void CameraView::updateTarget(int i, QVariant &v)
{
    if( !v.isValid() || !v.canConvert<BaseTarget>() ) return;
    BaseTarget t = v.value<BaseTarget>();
    mTranslateList[i]->setTranslation(QVector3D(t.posX(), t.posY(), 0.0));

    this->updateView();
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
    mEntityList.takeAt(i)->~QEntity();
    mRotateList.removeAt(i);
    mTranslateList.removeAt(i);
}

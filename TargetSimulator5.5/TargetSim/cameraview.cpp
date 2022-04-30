#include "cameraview.h"

#include <QtWidgets>
#include <Qt3DCore>
#include <Qt3DRenderer>
#include <Qt3DInput/QInputAspect>

CameraView::CameraView(QWidget *parent)
    : CameraView(3.0, 45.0, QSize(480, 320), false, false, parent)
{

}

CameraView::CameraView(qreal altitude, qreal elevAngleOfView, QSize pixelSize, bool isInputEnabled, bool isWindowEnabled, QWidget *parent)
    : BaseView(parent)
    , mAlt(altitude)
    , mWindow(new CameraWindow)
    , mEngine(new Qt3D::Quick::QQmlAspectEngine)
{
    // Widget
    QHBoxLayout *topLayout = new QHBoxLayout;
    this->setLayout(topLayout);

    // Quick
    if (     true     ) mEngine->aspectEngine()->registerAspect(new Qt3D::QRenderAspect);
    if (isInputEnabled) mEngine->aspectEngine()->registerAspect(new Qt3D::QInputAspect);
    mEngine->aspectEngine()->initialize();

    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(mWindow)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(mWindow));
    mEngine->aspectEngine()->setData(data);

    mEngine->setSource(QUrl("qrc:/qmlcameraview.qml"));
    mWindow->setEntity(mEngine->aspectEngine()->rootEntity());

    if (isWindowEnabled) {
        mWindow->setFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint );
        mWindow->resize(pixelSize);
        mWindow->setMinimumSize(pixelSize);
        mWindow->setMaximumSize(pixelSize);
        mWindow->show();
    } else {
        topLayout->addWidget(QWidget::createWindowContainer(mWindow, this));
    }

    // setFieldOfView
    qDebug() << "setFieldOfView:" << mEngine->aspectEngine()->rootEntity()->setProperty("fieldOfView", elevAngleOfView);
}

CameraView::~CameraView()
{
    qDebug() << "QmlCameraView Destructor Called!";
    delete mWindow;
    delete mEngine;
}

qreal CameraView::azim() const
{
    QSharedPointer<Qt3D::QEntity> entity = mEngine->aspectEngine()->rootEntity();
    QVector3D origin = entity->property("origin").value<QVector3D>();
    QVector3D center = entity->property("viewCenter").value<QVector3D>();
    QVector3D delta = center - origin;
    return qRadiansToDegrees(qAtan2(delta.x(), delta.y()));
}

qreal CameraView::elev() const
{
    QSharedPointer<Qt3D::QEntity> entity = mEngine->aspectEngine()->rootEntity();
    QVector3D origin = entity->property("origin").value<QVector3D>();
    QVector3D center = entity->property("viewCenter").value<QVector3D>();
    QVector3D delta = center - origin;
    return qRadiansToDegrees(qAsin(delta.z()));
}

QImage CameraView::image() const
{
    return mWindow->screen()->grabWindow(mWindow->winId()).toImage();
}

void CameraView::setCameraDirection(qreal azim, qreal elev)
{
    QSharedPointer<Qt3D::QEntity> entity = mEngine->aspectEngine()->rootEntity();
    QVector3D center(qSin(qDegreesToRadians(azim)) * qCos(qDegreesToRadians(elev)),
                     qCos(qDegreesToRadians(azim)) * qCos(qDegreesToRadians(elev)),
                     qSin(qDegreesToRadians(elev)) + entity->property("altitude").toReal()
                     );
    entity->setProperty("viewCenter", QVariant::fromValue<QVector3D>(center));
}


void CameraView::updateTarget(int i, QVariant &v)
{
    if( !v.isValid() || !v.canConvert<BaseTarget>() ) return;
    BaseTarget t = v.value<BaseTarget>();
    QVariant ret;
    bool isSuccess = QMetaObject::invokeMethod(mEngine->aspectEngine()->rootEntity().data(),
                                               "updateTarget",
                                               Qt::DirectConnection,
                                               Q_RETURN_ARG(QVariant, ret),
                                               Q_ARG(QVariant, i),
                                               Q_ARG(QVariant, QPointF(t.posX(), t.posY())));
    qDebug() << "echo return:" << ret;
}

void CameraView::insertTarget(int i)
{
    QVariant ret;
    bool isSuccess = QMetaObject::invokeMethod(mEngine->aspectEngine()->rootEntity().data(),
                                               "insertTarget",
                                               Qt::DirectConnection,
                                               Q_RETURN_ARG(QVariant, ret),
                                               Q_ARG(QVariant, i));
    qDebug() << "echo return:" << ret;
}

void CameraView::removeTarget(int i)
{
    QVariant ret;
    bool isSuccess = QMetaObject::invokeMethod(mEngine->aspectEngine()->rootEntity().data(),
                                               "removeTarget",
                                               Qt::DirectConnection,
                                               Q_RETURN_ARG(QVariant, ret),
                                               Q_ARG(QVariant, i));
    qDebug() << "echo return:" << ret;
}

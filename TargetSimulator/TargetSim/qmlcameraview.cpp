#include "qmlcameraview.h"

#include <QtWidgets>
#include <Qt3DCore>
#include <Qt3DRenderer>
#include <Qt3DInput/QInputAspect>

#define USE_EMBED

QmlCameraView::QmlCameraView(QWidget *parent)
    : QmlCameraView(3.0, 45.0, QSize(480, 320), false, parent)
{

}

QmlCameraView::QmlCameraView(qreal altitude, qreal elevAngleOfView, QSize pixelSize, bool isInputEnabled, QWidget *parent)
    : BaseView(parent)
    , mAlt(altitude)
    , mWindow(new QmlWindow)
    , mEngine(new Qt3D::Quick::QQmlAspectEngine)
{
    // Widget
    QHBoxLayout *topLayout = new QHBoxLayout;
    this->setLayout(topLayout);

    // Quick
    mEngine->aspectEngine()->registerAspect(new Qt3D::QRenderAspect);
    mEngine->aspectEngine()->registerAspect(new Qt3D::QInputAspect);
    mEngine->aspectEngine()->initialize();

    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(mWindow)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(mWindow));
    mEngine->aspectEngine()->setData(data);

    mEngine->setSource(QUrl("qrc:/qmlcameraview.qml"));
    mWindow->setEntity(mEngine->aspectEngine()->rootEntity());

#ifdef USE_EMBED
    topLayout->addWidget(QWidget::createWindowContainer(mWindow, this));
#else
    mWindow->setFlags(Qt::Window | Qt::CustomizeWindowHint );
    mWindow->resize(QSize(480,320));
    mWindow->show();
#endif
}

QmlCameraView::~QmlCameraView()
{
    qDebug() << "QmlCameraView Destructor Called!";
#ifndef USE_EMBED
    delete mWindow;
    delete mEngine;
#endif
}

void QmlCameraView::updateView()
{

}

qreal QmlCameraView::azim() const
{

}

qreal QmlCameraView::elev() const
{

}

void QmlCameraView::setCameraDirection(qreal azim, qreal elev)
{
//    QVariant ret;
//    bool isSuccess = QMetaObject::invokeMethod(mEngine->aspectEngine()->rootEntity().data(),
//                                               "echo",
//                                               Qt::DirectConnection,
//                                               Q_RETURN_ARG(QVariant, ret),
//                                               Q_ARG(QVariant, QString("Hello, World!")));
//    qDebug() << "echo return:" << ret;
}


void QmlCameraView::updateTarget(int i, QVariant &v)
{
}

void QmlCameraView::insertTarget(int i)
{
}

void QmlCameraView::removeTarget(int i)
{
}

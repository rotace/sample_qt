#include "camerawindow.h"

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

CameraWindow::CameraWindow(QScreen *screen)
    : QWindow(screen)
{
    setSurfaceType(QSurface::OpenGLSurface);

    resize(1024, 768);

    QSurfaceFormat format;
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        format.setVersion(4, 3);
        format.setProfile(QSurfaceFormat::CoreProfile);
    }
    format.setDepthBufferSize( 24 );
    format.setSamples( 4 );
    format.setStencilBufferSize(8);
    setFormat(format);
    create();
}

void CameraWindow::setEntity(QSharedPointer<Qt3D::QEntity> entity)
{
    mEntity = entity;
}


void CameraWindow::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
     {
         case Qt::Key_Escape:
             QApplication::quit();
             break;

         default:
             QWindow::keyPressEvent( e );
     }
}


void CameraWindow::resizeEvent(QResizeEvent *)
{
    if( mEntity.isNull() ) return;
    qDebug() << "setAspectRatio:" << mEntity->setProperty("aspectRatio", float(this->width()) / float(this->height()));
}

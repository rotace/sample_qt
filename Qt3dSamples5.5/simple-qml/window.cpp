#include "window.h"


#include <QKeyEvent>
#include <QGuiApplication>
#include <QOpenGLContext>


Window::Window(QScreen *screen)
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

void Window::setEntity(QSharedPointer<Qt3D::QEntity> entity)
{
    mEntity = entity;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QGuiApplication::quit();
            break;

        default:
            QWindow::keyPressEvent( e );
    }
}


void Window::resizeEvent(QResizeEvent *e)
{
    if ( mEntity.isNull() ) return;
    qDebug() << "setAspectRatio:" << mEntity->setProperty("aspectRatio", float(this->width()) / float(this->height()));
}

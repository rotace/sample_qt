#include "window.h"


#include <QKeyEvent>
#include <QApplication>
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


void Window::keyPressEvent(QKeyEvent *e)
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

void Window::hideEvent(QHideEvent *)
{
    QApplication::quit();
}

#include "window.h"
#include <QtGui>
#include <Qt3DCore>
#include <Qt3DRenderer>
#include <Qt3DInput/QInputAspect>
#include <Qt3DQuick/QQmlAspectEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Window window;
    Qt3D::Quick::QQmlAspectEngine engine;

    // Aspect
    engine.aspectEngine()->registerAspect(new Qt3D::QRenderAspect);
    engine.aspectEngine()->registerAspect(new Qt3D::QInputAspect);
    engine.aspectEngine()->initialize();

    // register Window
    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(&window)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(&window));
    engine.aspectEngine()->setData(data);

    // Load QML
    engine.setSource(QUrl("qrc:/main.qml"));

    // Camera
    window.setEntity(engine.aspectEngine()->rootEntity());

    // Window
    window.resize(QSize(480, 320));
    window.show();

    return app.exec();
}


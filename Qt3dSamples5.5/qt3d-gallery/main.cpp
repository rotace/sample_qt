#include <QDebug>
#include <QMessageBox>
#include <QSurfaceFormat>
#include <QApplication>
#include <QQmlApplicationEngine>

void showOpenGLInfo(){
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();

    QString profileString;
    switch (format.profile()) {
    case QSurfaceFormat::NoProfile:
        profileString = "NoProfile";
        break;
    case QSurfaceFormat::CoreProfile:
        profileString = "CoreProfile";
        break;
    case QSurfaceFormat::CompatibilityProfile:
        profileString = "CompatibilityProfile";
        break;
    }

    QString renderableTypeString;
    switch (format.renderableType()) {
    case QSurfaceFormat::DefaultRenderableType:
        renderableTypeString = "DefaultRenderableType";
        break;
    case QSurfaceFormat::OpenGL:
        renderableTypeString = "OpenGL";
        break;
    case QSurfaceFormat::OpenGLES:
        renderableTypeString = "OpenGLES";
        break;
    case QSurfaceFormat::OpenVG:
        renderableTypeString = "OpenVG";
        break;
    }

    QMessageBox::information(0,
                             "OpenGLInfo",
                             QString("OpenGL Version:    %1.%2\n"
                                     "OpenGL Profile:    %3\n"
                                     "OpenGL Options:    %4\n"
                                     "OpenGL RenderType:    %5")
                             .arg(format.majorVersion())
                             .arg(format.minorVersion())
                             .arg(profileString)
                             .arg(format.options())
                             .arg(renderableTypeString));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    showOpenGLInfo();

    return app.exec();
}


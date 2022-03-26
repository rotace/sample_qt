#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qt3DCore>
#include <Qt3DRenderer>
#include <Qt3DInput/QInputAspect>

void MainWindow::buttonPushed(QString message)
{
    // c++ IF (signal)   qml->c++ (not used)
    qDebug() << "slot:" << message;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mWindow(new Window)
    , mEngine(new Qt3D::Quick::QQmlAspectEngine(this))
{
    ui->setupUi(this);

    // Aspect
    mEngine->aspectEngine()->registerAspect(new Qt3D::QRenderAspect);
    mEngine->aspectEngine()->registerAspect(new Qt3D::QInputAspect);
    mEngine->aspectEngine()->initialize();

    // register Window
    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(mWindow)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(mWindow));
    mEngine->aspectEngine()->setData(data);

    // Load QML
    mEngine->setSource(QUrl("qrc:/main.qml"));

    // Window
    mWindow->resize(QSize(480, 320));
    mWindow->show();

    QSharedPointer<Qt3D::QEntity> entity = mEngine->aspectEngine()->rootEntity();
    connect(entity.data(), SIGNAL(button(QString)), this, SLOT(buttonPushed(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mWindow;
}

void MainWindow::on_radiusSpinBox_valueChanged(int arg1)
{
    // ref)
    // https://theolizer.com/cpp-school4/cpp-school4-4/

    // c++ IF (property) c++->qml
    QSharedPointer<Qt3D::QEntity> entity = mEngine->aspectEngine()->rootEntity();
    qDebug() << "Set Radius:" << arg1 << ":" << entity->setProperty("radius", arg1);

    // c++ IF (function) c++->qml
    QVariant ret;
    bool isSuccess = QMetaObject::invokeMethod(entity.data(),
                                               "echo",
                                               Qt::DirectConnection,
                                               Q_RETURN_ARG(QVariant, ret),
                                               Q_ARG(QVariant, QString("Hello, World!")));
    qDebug() << "echo return:" << ret;
}

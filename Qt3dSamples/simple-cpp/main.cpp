#include "window.h"
#include <QtGui>
#include <QtCore>
#include <Qt3DCore>
#include <Qt3DRenderer>
#include <Qt3DInput/QInputAspect>

#define IS_SIMPLE


void addSphereEntity(Qt3D::QEntity *rootEntity) {
    Qt3D::QEntity *entity = new Qt3D::QEntity(rootEntity);

    // Mesh
    Qt3D::QSphereMesh *mesh = new Qt3D::QSphereMesh;
    mesh->setRadius(3);

    // Transform
    Qt3D::QTransform *trans = new Qt3D::QTransform;
    Qt3D::QRotateTransform *rotate = new Qt3D::QRotateTransform;
    Qt3D::QTranslateTransform *move = new Qt3D::QTranslateTransform;
    rotate->setAxis(QVector3D(0, 1, 0));
    rotate->setAngleDeg(0.0);
    move->setTranslation(QVector3D(10, 0, 0));
    trans->addTransform(rotate);
    trans->addTransform(move);

    // Material
    Qt3D::QMaterial *mate = new Qt3D::QPhongMaterial(rootEntity);

    entity->addComponent(mesh);
    entity->addComponent(trans);
    entity->addComponent(mate);
}

void addTorusEntity(Qt3D::QEntity *rootEntity) {
    // Torus
    Qt3D::QEntity *torusEntity = new Qt3D::QEntity(rootEntity);

    // Torus shape data
    Qt3D::QTorusMesh *torus = new Qt3D::QTorusMesh();
    torus->setRadius(40);
    torus->setMinorRadius(15);

    torusEntity->addComponent(torus);

    // TorusMesh Transform
    Qt3D::QTransform *trans = new Qt3D::QTransform;
    Qt3D::QRotateTransform *rotate = new Qt3D::QRotateTransform;
    Qt3D::QTranslateTransform *move = new Qt3D::QTranslateTransform;

    move->setTranslation(QVector3D(-5.0f, 3.5f, 2.0f));
    rotate->setAxis(QVector3D(1, 0, 0));
    rotate->setAngleDeg(35.0f);
    trans->addTransform(move);
    trans->addTransform(rotate);
    torusEntity->addComponent(trans);
}


int main(int argc, char *argv[])
{
    // Common Instance
    QGuiApplication a(argc, argv);
    Qt3D::QEntity *rootEntity = new Qt3D::QEntity;
    Qt3D::QInputAspect *input = new Qt3D::QInputAspect;

#ifdef IS_SIMPLE
    // Instance
    Qt3D::QWindow window;

    // Aspect
    window.registerAspect(input);

    // Camera
    Qt3D::QCamera *camera = window.defaultCamera();
#else
    // Instance
    Window window;
    Qt3D::QAspectEngine engine;
    Qt3D::QRenderAspect *render = new Qt3D::QRenderAspect;
    Qt3D::QFrameGraph *framegraph = new Qt3D::QFrameGraph;
    Qt3D::QTechniqueFilter *filter = new Qt3D::QTechniqueFilter;
    Qt3D::QViewport *viewport = new Qt3D::QViewport(filter);
    Qt3D::QClearBuffer *buffer = new Qt3D::QClearBuffer(viewport);
    Qt3D::QCameraSelector *selector = new Qt3D::QCameraSelector(buffer);

    // Aspect
    engine.registerAspect(input);
    engine.registerAspect(render);
    engine.initialize();

    // Camera
    Qt3D::QCamera *camera= new Qt3D::QCamera(rootEntity);

    // FrameGraph
    viewport->setRect(QRectF(0, 0, 1, 1));
    buffer->setBuffers(Qt3D::QClearBuffer::ColorDepthBuffer);
    selector->setCamera(camera);
    framegraph->setActiveFrameGraph(filter);
    rootEntity->addComponent(framegraph);

    // Register Window
    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(&window)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(&window));
    engine.setData(data);
#endif

    addTorusEntity(rootEntity);
    addSphereEntity(rootEntity);

    // Camera Settings
    camera->lens()->setPerspectiveProjection(60.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(-5, 0, -20.0f));
    camera->setViewCenter(QVector3D(11, 0, 5));
    camera->setUpVector(QVector3D(0, 1, 0));
    input->setCamera(camera);

#ifdef IS_SIMPLE
    // Root
    window.setRootEntity(rootEntity);
#else
    // Root
    engine.setRootEntity(rootEntity);
#endif

    // Window
    window.resize(QSize(480, 320));
    window.show();

    return a.exec();


}


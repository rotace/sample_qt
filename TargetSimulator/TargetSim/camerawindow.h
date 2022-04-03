#ifndef QMLWINDOW_H
#define QMLWINDOW_H

#include <QWindow>
#include <QSharedPointer>
#include <Qt3DCore/QEntity>

class CameraWindow : public QWindow
{
    Q_OBJECT
    QSharedPointer<Qt3D::QEntity> mEntity;

public:
    explicit CameraWindow(QScreen *screen = 0);
    void setEntity(QSharedPointer<Qt3D::QEntity> entity);


    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
};

#endif // QMLWINDOW_H

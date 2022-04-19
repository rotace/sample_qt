#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QSharedPointer>
#include <Qt3DCore/QEntity>


class Window : public QWindow
{
    Q_OBJECT
    QSharedPointer<Qt3D::QEntity> mEntity;

public:
    explicit Window(QScreen *screen = 0);
    void setEntity(QSharedPointer<Qt3D::QEntity> entity);


    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
};

#endif // WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <Qt3DCore/QCamera>

class Window : public QWindow
{
    Q_OBJECT
    Qt3D::QCamera *mCamera = 0;

public:
    explicit Window(QScreen *screen = 0);
    void setCamera(Qt3D::QCamera *camera);


    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
};

#endif // WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>

class Window : public QWindow
{
    Q_OBJECT
public:
    explicit Window(QScreen *screen = 0);


    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent *) Q_DECL_OVERRIDE;
};

#endif // WINDOW_H

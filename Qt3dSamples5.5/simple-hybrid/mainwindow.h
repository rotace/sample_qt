#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window.h"
#include <QMainWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DQuick/QQmlAspectEngine>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void buttonPushed(QString message);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radiusSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Window *mWindow;
    Qt3D::Quick::QQmlAspectEngine *mEngine;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H

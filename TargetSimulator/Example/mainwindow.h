#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "simulatormodel.h"
#include "mapview.h"
#include "cameraview.h"
#include "qmlcameraview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addTargetPushButton_clicked();

    void on_delPushButton_clicked();

    void on_timerPushButton_clicked();

    void on_leftPushButton_clicked();

    void on_rightPushButton_clicked();

    void on_upPushButton_clicked();

    void on_downPushButton_clicked();

    void on_togglePushButton_clicked();

    void on_debug1PushButton_clicked();

    void on_debug2PushButton_clicked();



private:
    Ui::MainWindow *ui;
    SimulatorModel *mModel;
    QListView *mListView;
    QmlCameraView * mQmlCamView;
    CameraView *mCamView;
    MapView *mMapView;
    qreal mAzim;
    qreal mElev;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H

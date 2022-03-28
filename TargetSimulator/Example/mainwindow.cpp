#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "basetarget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mModel(new SimulatorModel)
    , mQmlCamView(0)
    , mCamView(0)
    , mMapView(0)
    , mAzim(0.0)
    , mElev(0.0)
{
    ui->setupUi(this);
    mModel->setParent(this);

    QWidget *topWidget = new QWidget;
    QGridLayout *topLayout = new QGridLayout;
    ui->centralWidget->layout()->addWidget(topWidget);
    topWidget->setLayout(topLayout);

    mListView = new QListView();
    topLayout->addWidget(mListView, 0, 0);
    mListView->setModel(mModel);

    mMapView = new MapView();
    topLayout->addWidget(mMapView, 0, 1);
    mMapView->setModel(mModel);

    qreal altitude = 3.0;
    qreal elevAngleOfView = 45.0;
    QSize pixelSize = QSize(480, 320);

    mCamView = new CameraView(altitude, elevAngleOfView, pixelSize);
    topLayout->addWidget(mCamView, 1, 0);
    mCamView->setModel(mModel);

    mQmlCamView = new QmlCameraView(altitude, elevAngleOfView, pixelSize);
    topLayout->addWidget(mQmlCamView, 1, 1);
    mQmlCamView->setModel(mModel);

    mModel->setTarget(BaseTarget(-100,-0.0,0,+10));
    mModel->setTarget(BaseTarget(-0.0,-100,0,-10));
    mModel->setTarget(BaseTarget(-0.0,+100,0,+10));
    mModel->setTarget(BaseTarget(+100,+0.0,0,-10));
    mModel->setTarget(BaseTarget());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTargetPushButton_clicked()
{
    mModel->setTarget(BaseTarget(
        ui->posXDoubleSpinBox->value(),
        ui->posYDoubleSpinBox->value(),
        ui->velXDoubleSpinBox->value(),
        ui->velYDoubleSpinBox->value(),
        ui->rcsDoubleSpinBox->value()
    ));
}

void MainWindow::on_delPushButton_clicked()
{
    mModel->delTarget();
}


void MainWindow::on_timerPushButton_clicked()
{
    if( mModel->isRunning() ) {
        mModel->stop();
    } else {
        mModel->setDeltaTime(ui->timeDoubleSpinBox->value());
        mModel->start();
    }
    if( mModel->isRunning() ) {
        ui->timerPushButton->setText("Timer Running");
    } else {
        ui->timerPushButton->setText("Timer Start");
    }
}


void MainWindow::closeEvent(QCloseEvent *)
{
    QApplication::quit();
}

void MainWindow::on_leftPushButton_clicked()
{
    mAzim -= ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    mQmlCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mQmlCamView->azim()).arg(mQmlCamView->elev()));
}

void MainWindow::on_rightPushButton_clicked()
{
    mAzim += ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    mQmlCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mQmlCamView->azim()).arg(mQmlCamView->elev()));
}

void MainWindow::on_upPushButton_clicked()
{
    mElev += ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    mQmlCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mQmlCamView->azim()).arg(mQmlCamView->elev()));
}

void MainWindow::on_downPushButton_clicked()
{
    mElev -= ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    mQmlCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mQmlCamView->azim()).arg(mQmlCamView->elev()));
}

void MainWindow::on_togglePushButton_clicked()
{
    bool isVisible = false;
    if( mCamView != 0 ) isVisible |= mCamView->isVisible();
    if( mQmlCamView != 0 ) isVisible |= mQmlCamView->isVisible();

    if( isVisible ) {
        if( mCamView != 0 ) mCamView->hide();
        if( mQmlCamView != 0 ) mQmlCamView->hide();
        ui->togglePushButton->setText("show");
    } else {
        if( mCamView != 0 ) mCamView->show();
        if( mQmlCamView != 0 ) mQmlCamView->show();
        ui->togglePushButton->setText("hide");
    }
}

void MainWindow::on_debug1PushButton_clicked()
{

}

void MainWindow::on_debug2PushButton_clicked()
{

}


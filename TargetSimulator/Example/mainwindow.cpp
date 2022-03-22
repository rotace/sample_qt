#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "basetarget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mModel(new SimulatorModel)
    , mAzim(0.0)
    , mElev(0.0)
{
    ui->setupUi(this);
    mModel->setParent(this);

    mListView = new QListView();
    ui->centralWidget->layout()->addWidget(mListView);
    mListView->setModel(mModel);

    mMapView = new MapView();
    ui->centralWidget->layout()->addWidget(mMapView);
    mMapView->setModel(mModel);

    qreal altitude = 3.0;
    qreal elevAngleOfView = 45.0;
    QSize pixelSize = QSize(480, 320);
    mCamView = new CameraView(altitude, elevAngleOfView, pixelSize);
    ui->centralWidget->layout()->addWidget(mCamView);
    mCamView->setModel(mModel);

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
    mCamView->close();
}

void MainWindow::on_leftPushButton_clicked()
{
    mAzim -= ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mCamView->azim()).arg(mCamView->elev()));
}

void MainWindow::on_rightPushButton_clicked()
{
    mAzim += ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mCamView->azim()).arg(mCamView->elev()));
}

void MainWindow::on_upPushButton_clicked()
{
    mElev += ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mCamView->azim()).arg(mCamView->elev()));
}

void MainWindow::on_downPushButton_clicked()
{
    mElev -= ui->tiltAngleStepDoubleSpinBox->value();
    mCamView->setCameraDirection(mAzim, mElev);
    ui->statusBar->showMessage(QString("AZIM: %1 deg, ELEV: %2 deg").arg(mCamView->azim()).arg(mCamView->elev()));
}

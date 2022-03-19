#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>

#include "mapview.h"
#include "basetarget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mModel(new SimulatorModel)
{
    ui->setupUi(this);
    mModel->setParent(this);

    QListView *listView = new QListView();
    ui->centralWidget->layout()->addWidget(listView);
    listView->setModel(mModel);

    MapView *mapView = new MapView();
    ui->centralWidget->layout()->addWidget(mapView);
    mapView->setModel(mModel);

    mModel->setTarget(BaseTarget(-200,0,0,+10,0));
    mModel->setTarget(BaseTarget(+200,0,0,-10,0));
    mModel->setTarget(BaseTarget(-100,0,0,+10,0));
    mModel->setTarget(BaseTarget(+100,0,0,-10,0));
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

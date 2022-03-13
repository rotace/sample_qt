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
        ui->velYDoubleSpinBox->value()
    ));
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tcpsocketwidget.h"
#include "udpsocketwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTcpPushButton_clicked()
{
    ui->tabWidget->addTab(new TcpSocketWidget(), QString("TCP%1").arg(ui->tabWidget->count()));
}

void MainWindow::on_addUdpPushButton_clicked()
{
    ui->tabWidget->addTab(new UdpSocketWidget(), QString("UDP%1").arg(ui->tabWidget->count()));
}

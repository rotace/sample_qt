#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "simulatormodel.h"


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

private:
    Ui::MainWindow *ui;
    SimulatorModel *mModel;

};

#endif // MAINWINDOW_H

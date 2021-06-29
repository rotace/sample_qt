#include <QCoreApplication>

#include "MainThreadApplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication coreApp(argc, argv);
    MainThreadApplication mainApp(&coreApp);

    mainApp.start();
    return coreApp.exec();
}

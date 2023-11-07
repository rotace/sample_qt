#include "mainwindow.h"

#include <QtCore>
#include <QApplication>

constexpr char APP_NAME[] = "TreeViewer";

bool createResourceFiles(const QString resDirName)
{
    QDir resDir(":"+resDirName);
    const auto &fileNameList = resDir.entryList(QDir::Files);
    for(const auto &fileName:fileNameList)
    {
        QDir appDir(qApp->applicationName() + "/" + resDirName);
        QDir().mkpath(appDir.absolutePath());
        QFile appFile(appDir.filePath(fileName));
        QFile resFile(QString(":" + resDirName + "/")+fileName);

        if(!resFile.exists()) {
            qCritical() << QString("file is not included in resource system! (%1)").arg(QFileInfo(appFile).absoluteFilePath());
        }

        if(appFile.exists()) {
            continue;
        } else {
            if(resFile.copy(appFile.fileName())) {
                appFile.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser);
            } else {
                qCritical() << QString("copy failed! (%1)").arg(QFileInfo(appFile).absoluteFilePath());
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationVersion("0.0");

    // Files
    if( !createResourceFiles("csv") ) return 0;

    // Widget
    MainWindow w;
    w.show();

    return a.exec();
}

#ifndef MAINTHREADAPPLICATION_H
#define MAINTHREADAPPLICATION_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "TcpTask.h"
#include "UdpTask.h"

class MainThreadApplication : public QObject
{
    Q_OBJECT
public:
    explicit MainThreadApplication(QObject *parent = nullptr);
    void start();

private:
    QThread* subThread1_;
    QThread* subThread2_;
    QThread* subThread3_;
    QThread* subThread4_;
    QThread* subThread5_;
    QThread* subThread6_;
    UdpTask* udpTask1_;
    UdpTask* udpTask2_;
    UdpTask* udpTask3_;
    UdpTask* udpTask4_;
    UdpTask* udpTask5_;
    UdpTask* udpTask6_;
    TcpTask* tcpTask1_;
    TcpTask* tcpTask2_;
    TcpTask* tcpTask3_;

signals:

};

#endif // MAINTHREADAPPLICATION_H

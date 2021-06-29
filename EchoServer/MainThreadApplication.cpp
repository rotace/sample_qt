#include "MainThreadApplication.h"

#include <QDebug>

MainThreadApplication::MainThreadApplication(QObject *parent)
    : QObject(parent),
      subThread1_(new QThread(this)),
      subThread2_(new QThread(this)),
      subThread3_(new QThread(this)),
      subThread4_(new QThread(this)),
      subThread5_(new QThread(this)),
      subThread6_(new QThread(this)),
      udpTask1_(new UdpTask(50001, subThread1_)),
      udpTask2_(new UdpTask(50002, subThread2_)),
      udpTask3_(new UdpTask(50003, subThread3_)),
      udpTask4_(new UdpTask(50004)),
      udpTask5_(new UdpTask(50005)),
      udpTask6_(new UdpTask(50006)),
      tcpTask1_(new TcpTask(50031, subThread4_)),
      tcpTask2_(new TcpTask(50032, subThread5_)),
      tcpTask3_(new TcpTask(50033, subThread6_))
{
}

void MainThreadApplication::start()
{
    qDebug() << "Sub Thread Start";
    subThread1_->start();
    subThread2_->start();
    subThread3_->start();
    subThread4_->start();
    subThread5_->start();
    subThread6_->start();
    qDebug() << "Main Thread:" << QThread::currentThread();
    qDebug() << "Sub Thread1:" << subThread1_;
    qDebug() << "Sub Thread2:" << subThread2_;
    qDebug() << "Sub Thread3:" << subThread3_;
    qDebug() << "Sub Thread4:" << subThread4_;
    qDebug() << "Sub Thread5:" << subThread5_;
    qDebug() << "Sub Thread6:" << subThread6_;
}

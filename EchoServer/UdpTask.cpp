#include <QtGlobal>
#include <QtNetwork>

#include "UdpTask.h"

UdpTask::UdpTask(qint32 port, QThread *thread)
    : QObject(nullptr),
      udpSock_(nullptr),
      port_(port)
{
//  execute by Main Thread
    this->moveToThread(thread);
    connect(thread, &QThread::finished, this, &QObject::deleteLater);

//  kick init() by Sub Thread
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

void UdpTask::init()
{
    Q_ASSERT(!udpSock_);

//  execute by Sub Thread
    qDebug() << "[" << QThread::currentThread() << "] " << "Init UDP (Port =" << port_ << ")";
    udpSock_ = new QUdpSocket(this);
    udpSock_->bind(port_);

    // Receive
    connect(udpSock_, &QUdpSocket::readyRead, [=](){
        while (udpSock_->hasPendingDatagrams()) {
            QNetworkDatagram datagram = udpSock_->receiveDatagram();
            QByteArray bytes = datagram.data();
            qDebug() << "[" << QThread::currentThread() << "] " << bytes;
        }
    });

    // State Change
    connect(udpSock_, &QUdpSocket::stateChanged, [=](QUdpSocket::SocketState state){
       qDebug() << "[" << QThread::currentThread() << "] " << state;
    });

    // Error
    connect(udpSock_,
            QOverload<QUdpSocket::SocketError>::of(&QUdpSocket::error)
            ,[=](QUdpSocket::SocketError error){
        qDebug() << "[" << QThread::currentThread() << "] " << error;
    });

    Q_ASSERT(udpSock_);
}


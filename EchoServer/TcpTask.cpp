#include <QtGlobal>
#include <QtNetwork>

#include "TcpTask.h"

TcpTask::TcpTask(qint32 port, QThread *thread)
    : QObject(nullptr),
      tcpServer_(nullptr),
      port_(port)
{
    //  execute by Main Thread
        this->moveToThread(thread);
        connect(thread, &QThread::finished, this, &QObject::deleteLater);

    //  kick init() by Sub Thread
        QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

void TcpTask::init()
{
    Q_ASSERT(!tcpServer_);

//  execute by Sub Thread
    qDebug() << "[" << QThread::currentThread() << "] " << "Init TCP (Port =" << port_ << ")";
    tcpServer_ = new QTcpServer(this);
    tcpServer_->listen(QHostAddress::Any, port_);

//  New Connection
    connect(tcpServer_, &QTcpServer::newConnection, [=]{
        QTcpSocket *tcpSock = tcpServer_->nextPendingConnection();

        // Disconnected
        connect(tcpSock, &QAbstractSocket::disconnected, tcpSock, &QObject::deleteLater);

        // Connected
        connect(tcpSock, &QTcpSocket::connected, [=](){
            qDebug() << "[" << QThread::currentThread() << "] " << "Connected (Port =" << port_ << ")";
        });

        // Receive
        connect(tcpSock, &QTcpSocket::readyRead, [=](){
            while(tcpSock->bytesAvailable()){
                QByteArray bytes = tcpSock->readAll();
                qDebug() << "[" << QThread::currentThread() << "] " << bytes;
            }
        });

        // State Change
        connect(tcpSock, &QTcpSocket::stateChanged, [=](QTcpSocket::SocketState state){
           qDebug() << "[" << QThread::currentThread() << "] " << state;
        });

        // Error
        connect(tcpSock,
                QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error)
                ,[=](QTcpSocket::SocketError error){
            qDebug() << "[" << QThread::currentThread() << "] " << error;
        });
    });

    Q_ASSERT(tcpServer_);
}

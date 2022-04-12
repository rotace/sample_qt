#include "udpsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

UdpSocketWidget::UdpSocketWidget(QWidget *parent)
    : AbstractSocketWidget(parent)
    , mUdpSock(new QUdpSocket(this))
{
    QPushButton *connection = new QPushButton("Connect");
    connection->setEnabled(false);

    QPushButton *transmission = new QPushButton("Send");
    transmission->setEnabled(true);

    mLayout->addRow("Connection", connection);
    mLayout->addRow("Transmission", transmission);

    connect(connection, &QPushButton::clicked, [=](){

        switch(mUdpSock->state()) {
        case QAbstractSocket::UnconnectedState:
            qDebug().noquote() << this->peerInfo(mUdpSock) << "Connecting... ";
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            qDebug().noquote() << this->peerInfo(mUdpSock) << "Disconnecting... ";
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        }
    });

    connect(transmission, &QPushButton::clicked, [=](){

        QByteArray datagram;
        datagram.append("Hello World");
        mUdpSock->writeDatagram(datagram, mPeerAddress, mPeerPort);

        switch (mUdpSock->state()) {
        case QAbstractSocket::UnconnectedState:
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        }
    });

    connect(mUdpSock, static_cast<void (QUdpSocket::*)()>(&QUdpSocket::readyRead), [=](){
        while (mUdpSock->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(mUdpSock->pendingDatagramSize());
            mUdpSock->readDatagram(datagram.data(), datagram.size(), &mPeerAddress, &mPeerPort);
            qDebug().noquote() << this->peerInfo(mUdpSock) << datagram;
        }
    });

    connect(mUdpSock, &QUdpSocket::stateChanged, [=](QUdpSocket::SocketState state){
        qDebug().noquote() << this->peerInfo(mUdpSock) << state;

        switch(state){
        case QAbstractSocket::UnconnectedState:
            connection->setText("Connect");
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            connection->setText("Disconnect");
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        }
    });

}


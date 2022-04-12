#include "tcpsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

TcpSocketWidget::TcpSocketWidget(QWidget *parent)
    : AbstractSocketWidget(parent)
    , mTcpSock(new QTcpSocket(this))
{
    QPushButton *connection = new QPushButton("Connect");
    connection->setEnabled(true);

    QPushButton *transmission = new QPushButton("Send");
    transmission->setEnabled(false);

    mLayout->addRow("Connection", connection);
    mLayout->addRow("Transmission", transmission);

    connect(connection, &QPushButton::clicked, [=](){

        switch(mTcpSock->state()) {
        case QAbstractSocket::UnconnectedState:
            qDebug().noquote() << this->peerInfo(mTcpSock) << "Connecting... ";
            mTcpSock->bind(mLocalAddress, mLocalPort);
            mTcpSock->connectToHost(mPeerAddress, mPeerPort);
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            qDebug().noquote() << this->peerInfo(mTcpSock) << "Disconnecting... ";
            mTcpSock->disconnectFromHost();
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

        switch (mTcpSock->state()) {
        case QAbstractSocket::UnconnectedState:
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            mTcpSock->write( QString("Hello World").toLocal8Bit() );
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        }
    });


    connect(mTcpSock, static_cast<void (QTcpSocket::*)()>(&QTcpSocket::readyRead), [=](){
        while(mTcpSock->bytesAvailable()){
            QByteArray bytes = mTcpSock->readAll();
            qDebug().noquote() << this->peerInfo(mTcpSock) << bytes;
        }
    });

    connect(mTcpSock, &QTcpSocket::stateChanged, [=](QTcpSocket::SocketState state){
        qDebug().noquote() << this->peerInfo(mTcpSock) << state;

        switch(state){
        case QAbstractSocket::UnconnectedState:
            connection->setText("Connect");
            transmission->setEnabled(false);
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            connection->setText("Disconnect");
            transmission->setEnabled(true);
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


#include "tcpsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

TcpSocketWidget::TcpSocketWidget(QWidget *parent)
    : AbstractSocketWidget(parent)
    , mTcpSock(new QTcpSocket(this))
{
    QPushButton *connectButton = new QPushButton("Connect");
    connectButton->setEnabled(true);

    QPushButton *sendButton = new QPushButton("Send");
    sendButton->setEnabled(false);

    mLayout->addRow("Connection", connectButton);
    mLayout->addRow("Transmission", sendButton);

    connect(connectButton, &QPushButton::clicked, [=](){

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

    connect(sendButton, &QPushButton::clicked, [=](){

        QString message("Hello World TCP\n");

        switch (mTcpSock->state()) {
        case QAbstractSocket::UnconnectedState:
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            mTcpSock->write( message.toLocal8Bit() );
            qDebug().noquote() << this->localInfo(mTcpSock) << "->" << this->peerInfo(mTcpSock) << message.trimmed();
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
            qDebug().noquote() << this->localInfo(mTcpSock) << "<-" << this->peerInfo(mTcpSock) << bytes;
        }
    });

    connect(mTcpSock, &QTcpSocket::stateChanged, [=](QTcpSocket::SocketState state){
        qDebug().noquote() << this->peerInfo(mTcpSock) << state;

        switch(state){
        case QAbstractSocket::UnconnectedState:
            connectButton->setText("Connect");
            sendButton->setEnabled(false);
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            connectButton->setText("Disconnect");
            sendButton->setEnabled(true);
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


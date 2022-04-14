#include "udpsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

UdpSocketWidget::UdpSocketWidget(QWidget *parent)
    : AbstractSocketWidget(parent)
    , mUdpSock(new QUdpSocket(this))
{
    QLineEdit* multicast = new QLineEdit;
    multicast->setText("224.0.0.1");

    QPushButton *bindButton = new QPushButton("Bind");
    bindButton->setEnabled(true);

    QPushButton *joinButton = new QPushButton("Join");
    joinButton->setEnabled(false);

    QPushButton *sendButton = new QPushButton("Send");
    sendButton->setEnabled(true);

    mLayout->addRow("Multicast Address", multicast);
    mLayout->addRow("Bound", bindButton);
    mLayout->addRow("Multicast", joinButton);
    mLayout->addRow("Transmission", sendButton);

    connect(bindButton, &QPushButton::clicked, [=](){

        switch(mUdpSock->state()){
        case QAbstractSocket::UnconnectedState:
            qDebug().noquote() << this->peerInfo(mUdpSock) << "Binding... ";
            mUdpSock->bind(mLocalAddress, mLocalPort);
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            break;
        case QAbstractSocket::BoundState:
            qDebug().noquote() << this->peerInfo(mUdpSock) << "Unbinding... ";
            mUdpSock->disconnectFromHost();
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        }
    });

    connect(joinButton, &QPushButton::clicked, [=](){
        if( joinButton->text() == QString("Join") ) {
            bool success = mUdpSock->joinMulticastGroup( QHostAddress(multicast->text()) );
            joinButton->setText("Leave");
            joinButton->setToolTip(success ? "Last Action Sucessed" : "Last Action Faild");
        } else {
            bool success = mUdpSock->leaveMulticastGroup( QHostAddress(multicast->text()) );
            joinButton->setText("Join");
            joinButton->setToolTip(success ? "Last Action Sucessed" : "Last Action Faild");
        }
    });

    connect(sendButton, &QPushButton::clicked, [=](){
        QByteArray datagram;
        datagram.append("Hello World UDP\n");
        mUdpSock->writeDatagram(datagram, mPeerAddress, mPeerPort);
        qDebug().noquote() << this->localInfo(mUdpSock) << "->" << this->sockInfo(mPeerAddress, mPeerPort) << QString::fromLocal8Bit(datagram).trimmed();
    });

    connect(mUdpSock, static_cast<void (QUdpSocket::*)()>(&QUdpSocket::readyRead), [=](){
        while (mUdpSock->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(mUdpSock->pendingDatagramSize());
            mUdpSock->readDatagram(datagram.data(), datagram.size(), &mPeerAddress, &mPeerPort);
            qDebug().noquote() << this->localInfo(mUdpSock) << "<-" << this->peerInfo(mUdpSock) << datagram;
        }
    });

    connect(mUdpSock, &QUdpSocket::stateChanged, [=](QUdpSocket::SocketState state){
        qDebug().noquote() << this->peerInfo(mUdpSock) << state;

        switch(state){
        case QAbstractSocket::UnconnectedState:
            bindButton->setText("Bind");
            joinButton->setEnabled(false);
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            break;
        case QAbstractSocket::BoundState:
            bindButton->setText("Unbind");
            joinButton->setEnabled(true);
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        }
    });

}


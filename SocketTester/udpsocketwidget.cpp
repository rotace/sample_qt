#include "udpsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

UdpSocketWidget::UdpSocketWidget(QWidget *parent)
    : AbstractSocketWidget(parent)
    , mUdpSock(new QUdpSocket(this))
{
    QWidget* multiWidget = new QWidget;
    QLineEdit* multiAddr= new QLineEdit;
    QComboBox* multiIf = new QComboBox;
    QPushButton *bindButton = new QPushButton("Bind");
    QPushButton *joinButton = new QPushButton("Join");
    QPushButton *sendButton = new QPushButton("Send");
    QListWidget *multicastListWidget = new QListWidget;
    QStringListModel *networkListModel = new QStringListModel(this);

    multiAddr->setText("224.0.0.100");
    networkListModel->setStringList(this->networkList());
    multiIf->setModel(networkListModel);
    multiIf->setCurrentIndex(0);
    multiIf->setMinimumWidth(80);
    multiIf->setMaximumWidth(80);
    bindButton->setEnabled(true);
    joinButton->setEnabled(false);
    sendButton->setEnabled(true);

    multiWidget->setLayout(new QHBoxLayout);
    multiWidget->layout()->addWidget(multiAddr);
    multiWidget->layout()->addWidget(multiIf);
    multiWidget->layout()->setMargin(0);

    mLayout->addRow("Bound", bindButton);
    mLayout->addRow("Transmission", sendButton);
    mLayout->addRow(new QLabel("----Multicast----"));
    mLayout->addRow("Addr/NIC", multiWidget);
    mLayout->addRow("Join", joinButton);
    mLayout->addRow("Group", multicastListWidget);

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
        QString addr = multiAddr->text();
        QString ifce = multiIf->currentText();
        bool success = mUdpSock->joinMulticastGroup( QHostAddress(addr), QNetworkInterface::interfaceFromName(ifce) );
        qDebug() << QString(success ? "joinMulticastGroup Sucessed" : "joinMulticastGroup Faild");
        if (success) multicastListWidget->addItem(QString("%1/%2").arg(addr).arg(ifce));
    });

    connect(multicastListWidget, &QListWidget::clicked, [=](const QModelIndex& index){
        QString infos = index.model()->data(index).toString();
        QStringList info = infos.split("/");

        QMessageBox::StandardButton btnFlag = QMessageBox::question(this, "Leave Multicast Group", QString("Leave Multicast Group (%1) ?").arg(infos));

        bool success;
        switch (btnFlag) {
        case QMessageBox::Yes:
            success = mUdpSock->leaveMulticastGroup( QHostAddress(info[0]), QNetworkInterface::interfaceFromName(info[1]) );
            qDebug() << QString(success ? "leaveMulticastGroup Sucessed" : "leaveMulticastGroup Faild");
            if (success) {
                multicastListWidget->takeItem(index.row());
            }
            break;
        case QMessageBox::No:
        default:
            break;
        }
    });

    connect(sendButton, &QPushButton::clicked, [=](){
        QByteArray datagram;
        datagram.append(this->sendMessage()+"\n");
        mUdpSock->writeDatagram(datagram, mPeerAddress, mPeerPort);
        qDebug().noquote() << this->localInfo(mUdpSock) << "->" << this->sockInfo(mPeerAddress, mPeerPort) << this->sendMessage();
    });

    connect(mUdpSock, static_cast<void (QUdpSocket::*)()>(&QUdpSocket::readyRead), [=](){
        while (mUdpSock->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(mUdpSock->pendingDatagramSize());
            mUdpSock->readDatagram(datagram.data(), datagram.size(), &mPeerAddress, &mPeerPort);
            this->setRecvMessage(datagram);
            qDebug().noquote() << this->localInfo(mUdpSock) << "<-" << this->peerInfo(mUdpSock) << QString(datagram).trimmed();
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


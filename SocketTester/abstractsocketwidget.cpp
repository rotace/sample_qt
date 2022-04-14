#include "abstractsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

AbstractSocketWidget::AbstractSocketWidget(QWidget *parent)
    : QWidget(parent)
    , mLayout(new QFormLayout)
{
    this->setLayout(mLayout);

    QLineEdit* peerAddress = new QLineEdit;
    QComboBox* localAddress = new QComboBox;
    QSpinBox* peerPort = new QSpinBox;
    QSpinBox* localPort = new QSpinBox;

    QStringList addrInfoList;
    addrInfoList.append("any / 0.0.0.0 / 0.0.0.0");
    for( const QNetworkInterface ifce : QNetworkInterface::allInterfaces() ) {
        for( const QNetworkAddressEntry entry : ifce.addressEntries() ) {
            QStringList entryInfo;
            entryInfo << ifce.name() << entry.ip().toString() << entry.netmask().toString();
            addrInfoList.append(entryInfo.join(" / "));
        }
    }
    localAddress->setToolTip(addrInfoList.join("\n"));
    localAddress->setModel(&mModel);
    peerPort->setMinimum(0);
    peerPort->setMaximum(65535);
    localPort->setMinimum(0);
    localPort->setMaximum(65535);

    mLayout->addRow("Peer Address", peerAddress);
    mLayout->addRow("Peer Port", peerPort);
    mLayout->addRow("Local Address", localAddress);
    mLayout->addRow("Local Port", localPort);

    connect(peerAddress, &QLineEdit::editingFinished, [=](){
        if( this->isValidAddress(peerAddress->text()) )
            mPeerAddress = QHostAddress(peerAddress->text());
    });

    connect(localAddress, &QComboBox::currentTextChanged, [=](const QString str){
        if( this->isValidAddress(str) )
            mLocalAddress = QHostAddress(str);
    });

    connect(peerPort, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](){
        mPeerPort = peerPort->value();
    });

    connect(localPort, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](){
        mLocalPort = localPort->value();
    });

    this->updateLocalAddress();
    peerAddress->setText("127.0.0.1");
    localAddress->setCurrentIndex(0);
    peerPort->setValue(50000);
    localPort->setValue(0);
    mPeerAddress.setAddress(peerAddress->text());
    qDebug() << mPeerAddress << mLocalAddress << mPeerPort << mLocalPort;
}

QString AbstractSocketWidget::sockInfo(QHostAddress address, qint32 port) const
{
    return QString("[ADDR:%1, PORT:%2]").arg(address.toString()).arg(port);
}


QString AbstractSocketWidget::peerInfo(QAbstractSocket *socket) const
{
    return QString("[ADDR:%1, PORT:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
}

QString AbstractSocketWidget::localInfo(QAbstractSocket *socket) const
{
    return QString("[ADDR:%1, PORT:%2]").arg(socket->localAddress().toString()).arg(socket->localPort());
}

bool AbstractSocketWidget::isValidAddress(QString addrText) const
{
    QHostAddress addr(addrText);
    if( addr.isNull() ) qDebug() << addrText << "is invalid!";
    return !addr.isNull();
}

void AbstractSocketWidget::updateLocalAddress()
{
    QStringList list;
    list.append("0.0.0.0");
    for( const QHostAddress addr : QNetworkInterface::allAddresses() ) list.append(addr.toString());
    mModel.setStringList(list);
}

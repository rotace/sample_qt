#include "abstractsocketwidget.h"

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

AbstractSocketWidget::AbstractSocketWidget(QWidget *parent)
    : QWidget(parent)
    , mLayout(new QFormLayout)
{
    this->setLayout(mLayout);

    mSendMessage = new QLineEdit;
    QWidget* peerWidget = new QWidget;
    QWidget* localWidget = new QWidget;
    QListView* recvMessage = new QListView;
    QLineEdit* peerAddress = new QLineEdit;
    QComboBox* localAddress = new QComboBox;
    QSpinBox* peerPort = new QSpinBox;
    QSpinBox* localPort = new QSpinBox;

    recvMessage->setModel(&mRecvMessageListModel);
    localAddress->setToolTip(this->networkSummaryList().join("\n"));
    localAddress->setModel(&mLocalAddrListModel);
    peerPort->setMinimum(0);
    peerPort->setMaximum(65535);
    peerPort->setMinimumWidth(80);
    peerPort->setMaximumWidth(80);
    localPort->setMinimum(0);
    localPort->setMaximum(65535);
    localPort->setMinimumWidth(80);
    localPort->setMaximumWidth(80);

    peerWidget->setLayout(new QHBoxLayout);
    peerWidget->layout()->addWidget(peerAddress);
    peerWidget->layout()->addWidget(peerPort);
    peerWidget->layout()->setMargin(0);

    localWidget->setLayout(new QHBoxLayout);
    localWidget->layout()->addWidget(localAddress);
    localWidget->layout()->addWidget(localPort);
    localWidget->layout()->setMargin(0);

    mLayout->addRow("Send Message", mSendMessage);
    mLayout->addRow("Recv Message", recvMessage);
    mLayout->addRow("Peer Addr/Port", peerWidget);
    mLayout->addRow("Local Addr/Port", localWidget);

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

    mLocalAddrListModel.setStringList(this->addressList());
    mSendMessage->setText("Hello World!!");
    peerAddress->setText("127.0.0.1");
    localAddress->setCurrentIndex(0);
    peerPort->setValue(50000);
    localPort->setValue(0);
    mPeerAddress.setAddress(peerAddress->text());
    qDebug() << mPeerAddress << mLocalAddress << mPeerPort << mLocalPort;
}

void AbstractSocketWidget::setRecvMessage(QString message)
{
    qint32 count = mRecvMessageListModel.rowCount()+1;
    mRecvMessageListModel.insertRow(0);
    mRecvMessageListModel.setData(mRecvMessageListModel.index(0), QVariant(QString("%1:").arg(count) + message.trimmed()));
}

QString AbstractSocketWidget::sendMessage() const
{
    return mSendMessage->text();
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

QStringList AbstractSocketWidget::addressList() const
{
    QStringList list;
    list.append("0.0.0.0");
    for( const QHostAddress addr : QNetworkInterface::allAddresses() ) list.append(addr.toString());
    return list;
}

QStringList AbstractSocketWidget::networkList() const
{
    QStringList list;
    for( const QNetworkInterface ifce : QNetworkInterface::allInterfaces() ) list.append(ifce.name());
    return list;
}

QStringList AbstractSocketWidget::networkSummaryList() const
{
    QStringList netInfoList;
    netInfoList.append("any / 0.0.0.0 / 0.0.0.0");
    for( const QNetworkInterface ifce : QNetworkInterface::allInterfaces() ) {
        for( const QNetworkAddressEntry entry : ifce.addressEntries() ) {
            QStringList entryInfo;
            entryInfo << ifce.name() << entry.ip().toString() << entry.netmask().toString();
            netInfoList.append(entryInfo.join(" / "));
        }
    }
    return netInfoList;
}

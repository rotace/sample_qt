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
    peerAddress->setText("127.0.0.1");
    mPeerAddress = QHostAddress(peerAddress->text());

    QLineEdit* localAddress = new QLineEdit;
    localAddress->setText("0.0.0.0");
    mLocalAddress = QHostAddress(localAddress->text());

    QSpinBox* peerPort = new QSpinBox;
    peerPort->setMinimum(0);
    peerPort->setMaximum(65535);
    peerPort->setValue(50000);
    mPeerPort = peerPort->value();

    QSpinBox* localPort = new QSpinBox;
    localPort->setMinimum(0);
    localPort->setMaximum(65535);
    localPort->setValue(0);
    mLocalPort = localPort->value();

    mLayout->addRow("Peer Address", peerAddress);
    mLayout->addRow("Peer Port", peerPort);
    mLayout->addRow("Local Address", localAddress);
    mLayout->addRow("Local Port", localPort);

    connect(peerAddress, &QLineEdit::editingFinished, [=](){
        if( this->isValidAddress(peerAddress->text()) ) mPeerAddress = QHostAddress(peerAddress->text());
    });

    connect(localAddress, &QLineEdit::editingFinished, [=](){
        if( this->isValidAddress(localAddress->text()) ) mPeerAddress = QHostAddress(localAddress->text());
    });

    connect(peerPort, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](){
        mPeerPort = peerPort->value();
    });

    connect(localPort, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](){
        mLocalPort = localPort->value();
    });
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

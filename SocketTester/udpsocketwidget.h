#ifndef UDPSOCKETWIDGET_H
#define UDPSOCKETWIDGET_H

#include "abstractsocketwidget.h"
#include <QUdpSocket>

class UdpSocketWidget : public AbstractSocketWidget
{
    Q_OBJECT
    QUdpSocket *mUdpSock;

public:
    explicit UdpSocketWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // UDPSOCKETWIDGET_H

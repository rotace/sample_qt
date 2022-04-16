#ifndef TCPSOCKETWIDGET_H
#define TCPSOCKETWIDGET_H

#include "abstractsocketwidget.h"
#include <QTcpSocket>

class TcpSocketWidget : public AbstractSocketWidget
{
    Q_OBJECT
    QTcpSocket *mTcpSock;

public:
    explicit TcpSocketWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // TCPSOCKETWIDGET_H

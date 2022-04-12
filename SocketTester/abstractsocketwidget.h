#ifndef ABSTRACTSOCKETWIDGET_H
#define ABSTRACTSOCKETWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QAbstractSocket>
#include <QHostAddress>

class AbstractSocketWidget : public QWidget
{
    Q_OBJECT

protected:
    QFormLayout *mLayout;
    QHostAddress mPeerAddress;
    QHostAddress mLocalAddress;
    quint16 mPeerPort;
    quint16 mLocalPort;

public:
    explicit AbstractSocketWidget(QWidget *parent = 0);
    QString peerInfo(QAbstractSocket *socket) const;
    QString localInfo(QAbstractSocket *socket) const;
    bool isValidAddress(QString addr) const;

signals:

public slots:
};

#endif // ABSTRACTSOCKETWIDGET_H

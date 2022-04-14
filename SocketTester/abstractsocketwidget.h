#ifndef ABSTRACTSOCKETWIDGET_H
#define ABSTRACTSOCKETWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QStringListModel>

class AbstractSocketWidget : public QWidget
{
    Q_OBJECT

protected:
    QStringListModel mModel;
    QFormLayout *mLayout;
    QHostAddress mPeerAddress;
    QHostAddress mLocalAddress;
    quint16 mPeerPort;
    quint16 mLocalPort;

public:
    explicit AbstractSocketWidget(QWidget *parent = 0);
    QString sockInfo(QHostAddress address, qint32 port) const;
    QString peerInfo(QAbstractSocket *socket) const;
    QString localInfo(QAbstractSocket *socket) const;
    bool isValidAddress(QString addr) const;
    void updateLocalAddress();

signals:

public slots:
};

#endif // ABSTRACTSOCKETWIDGET_H

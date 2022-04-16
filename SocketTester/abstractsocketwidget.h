#ifndef ABSTRACTSOCKETWIDGET_H
#define ABSTRACTSOCKETWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QStringListModel>

class AbstractSocketWidget : public QWidget
{
    Q_OBJECT
    QStringListModel mRecvMessageListModel;
    QStringListModel mLocalAddrListModel;
    QLineEdit *mSendMessage;

protected:
    QFormLayout *mLayout;
    QHostAddress mPeerAddress;
    QHostAddress mLocalAddress;
    quint16 mPeerPort;
    quint16 mLocalPort;

public:
    explicit AbstractSocketWidget(QWidget *parent = 0);
    void setRecvMessage(QString message);
    QString sendMessage() const;
    QString sockInfo(QHostAddress address, qint32 port) const;
    QString peerInfo(QAbstractSocket *socket) const;
    QString localInfo(QAbstractSocket *socket) const;
    bool isValidAddress(QString addr) const;
    QStringList addressList() const;
    QStringList networkList() const;
    QStringList networkSummaryList() const;

signals:

public slots:
};

#endif // ABSTRACTSOCKETWIDGET_H

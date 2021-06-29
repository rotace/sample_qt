#ifndef UDPTASK_H
#define UDPTASK_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>

class UdpTask : public QObject
{
    Q_OBJECT
public:
    explicit UdpTask(qint32 port, QThread *thread = QThread::currentThread());

private:
    QUdpSocket *udpSock_;
    qint32 port_;

private slots:
    void init();

signals:

};

#endif // UDPTASK_H

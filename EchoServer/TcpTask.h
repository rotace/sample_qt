#ifndef TCPTASK_H
#define TCPTASK_H

#include <QObject>
#include <QThread>
#include <QTcpServer>

class TcpTask : public QObject
{
    Q_OBJECT
public:
    explicit TcpTask(qint32 port, QThread *thread = QThread::currentThread());

private:
    QTcpServer *tcpServer_;
    qint32 port_;

private slots:
    void init();

signals:

};

#endif // TCPTASK_H

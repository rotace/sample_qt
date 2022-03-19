#ifndef SIMULATORMODEL_H
#define SIMULATORMODEL_H

#include "basemodel.h"

#include <QTimer>

class SimulatorModel : public BaseModel
{
    Q_OBJECT
    QTimer mTimer;
    qreal mDeltaTime;

public:
    explicit SimulatorModel(QObject *parent = 0);
    bool isRunning() const;
    void start();
    void stop();
    qreal deltaTime() const;
    void setDeltaTime(const qreal &deltaTime);

signals:

public slots:
    void update();

};

#endif // SIMULATORMODEL_H

#include "simulatormodel.h"

#include <QtCore>

qreal SimulatorModel::deltaTime() const
{
    return mDeltaTime;
}

void SimulatorModel::setDeltaTime(const qreal &deltaTime)
{
    mDeltaTime = deltaTime;
}

SimulatorModel::SimulatorModel(QObject *parent)
    : BaseModel(parent)
    , mDeltaTime(1.0)
{
    connect(&mTimer, &QTimer::timeout, this, &SimulatorModel::update);
}

bool SimulatorModel::isRunning() const
{
    return mTimer.isActive();
}

void SimulatorModel::start()
{
    mTimer.start(1000*mDeltaTime);
}

void SimulatorModel::stop()
{
    mTimer.stop();
}

void SimulatorModel::update()
{
    for(qint32 i=0; i<this->rowCount(); i++) {
        BaseTarget t = this->data(this->index(i), Qt::DisplayRole).value<BaseTarget>();
        t.update(mDeltaTime);
        this->setData(this->index(i) ,QVariant::fromValue(t), Qt::DisplayRole);
    }
}

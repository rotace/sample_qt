#include "basetarget.h"

#include <QtCore>

struct TargetVariantConversions
{
    TargetVariantConversions()
    {
        QMetaType::registerConverter<BaseTarget, int>();
        QMetaType::registerConverter<BaseTarget, double>();
        QMetaType::registerConverter<BaseTarget, QString>();
    }
};

Q_GLOBAL_STATIC(TargetVariantConversions, initTargetConversions)

qreal BaseTarget::posX() const
{
    return mPosX;
}

void BaseTarget::setPosX(const qreal &posX)
{
    mPosX = posX;
}

qreal BaseTarget::posY() const
{
    return mPosY;
}

void BaseTarget::setPosY(const qreal &posY)
{
    mPosY = posY;
}

qreal BaseTarget::velX() const
{
    return mVelX;
}

void BaseTarget::setVelX(const qreal &velX)
{
    mVelX = velX;
}

qreal BaseTarget::velY() const
{
    return mVelY;
}

void BaseTarget::setVelY(const qreal &velY)
{
    mVelY = velY;
}

BaseTarget::BaseTarget()
    : mPosX(0.0)
    , mPosY(0.0)
    , mVelX(0.0)
    , mVelY(0.0)
{
    initTargetConversions();
}

BaseTarget::BaseTarget(const BaseTarget &obj)
{
    initTargetConversions();
    mPosX = obj.mPosX;
    mPosY = obj.mPosY;
    mVelX = obj.mVelX;
    mVelY = obj.mVelY;
}

BaseTarget::BaseTarget(qreal posX, qreal posY, qreal velX, qreal velY)
    : mPosX(posX)
    , mPosY(posY)
    , mVelX(velX)
    , mVelY(velY)
{
    initTargetConversions();
}

BaseTarget::operator int() const
{
    return 9;
}

BaseTarget::operator double() const
{
    return 9.999;
}

BaseTarget::operator QString() const
{
    return QString("BaseTarget(%1, %2, %3, %4)").arg(mPosX).arg(mPosY).arg(mVelX).arg(mVelY);
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const BaseTarget &t)
{
    return d << (QString)t;
}
#endif

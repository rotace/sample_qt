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

qreal BaseTarget::rcs() const
{
    return mRcs;
}

void BaseTarget::setRcs(const qreal &rcs)
{
    mRcs = rcs;
}

void BaseTarget::update(qreal deltaTime)
{
    mPosX += mVelX * deltaTime;
    mPosY += mVelY * deltaTime;
}

BaseTarget::BaseTarget()
    : mPosX(0.0)
    , mPosY(0.0)
    , mVelX(0.0)
    , mVelY(0.0)
    , mRcs(0.0)
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
    mRcs  = obj.mRcs;
}

BaseTarget::BaseTarget(qreal posX, qreal posY, qreal velX, qreal velY, qreal rcs)
    : mPosX(posX)
    , mPosY(posY)
    , mVelX(velX)
    , mVelY(velY)
    , mRcs(rcs)
{
    initTargetConversions();
}

BaseTarget::operator int() const
{
    return mRcs;
}

BaseTarget::operator double() const
{
    return mRcs;
}

BaseTarget::operator QString() const
{
    return QString("BaseTarget(%1, %2, %3, %4, %5)").arg(mPosX).arg(mPosY).arg(mVelX).arg(mVelY).arg(mRcs);
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const BaseTarget &t)
{
    return d << (QString)t;
}
#endif

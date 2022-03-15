#ifndef BASETARGET_H
#define BASETARGET_H

#include <QMetaType>
#include <QDataStream>
#include <QDebug>

class BaseTarget
{
    qreal mPosX;
    qreal mPosY;
    qreal mVelX;
    qreal mVelY;
    qreal mRcs;

public:
    BaseTarget();
    BaseTarget(const BaseTarget &obj);
    BaseTarget(qreal posX, qreal posY, qreal velX, qreal velY, qreal rcs);
    operator int() const;
    operator double() const;
    operator QString() const;
    qreal posX() const;
    void setPosX(const qreal &posX);
    qreal posY() const;
    void setPosY(const qreal &posY);
    qreal velX() const;
    void setVelX(const qreal &velX);
    qreal velY() const;
    void setVelY(const qreal &velY);
    qreal rcs() const;
    void setRcs(const qreal &rcs);
};
Q_DECLARE_METATYPE(BaseTarget)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const BaseTarget &t);
#endif

#endif // BASETARGET_H

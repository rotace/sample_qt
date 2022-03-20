#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "baseview.h"

class CameraView : public BaseView
{
    Q_OBJECT
public:
    explicit CameraView(QWidget *parent = 0);

signals:

public slots:

    // BaseView interface
public:
    void updateTarget(int i, QVariant &v) Q_DECL_OVERRIDE;
    void insertTarget(int i) Q_DECL_OVERRIDE;
    void removeTarget(int i) Q_DECL_OVERRIDE;
};

#endif // CAMERAVIEW_H

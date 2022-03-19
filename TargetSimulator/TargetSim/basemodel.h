#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QAbstractListModel>
#include "basetarget.h"

class BaseModel : public QAbstractListModel
{
    Q_OBJECT
    QList<QVariant> mList;

public:
    explicit BaseModel(QObject *parent = 0);
    void setTarget(const BaseTarget &target);
    void delTarget();

signals:

public slots:


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    bool insertRows(int row, int count, const QModelIndex &parent) Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent) Q_DECL_OVERRIDE;

};

#endif // BASEMODEL_H

#include "basemodel.h"

#include <QtCore>

#include "basetarget.h"

BaseModel::BaseModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void BaseModel::setTarget(const BaseTarget &target)
{
    this->insertRow(this->rowCount());
    this->setData(this->index(this->rowCount()-1) ,QVariant::fromValue(target), Qt::DisplayRole);
}

void BaseModel::delTarget()
{
    this->removeRow(this->rowCount()-1);
}




int BaseModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mList.count();
}

QVariant BaseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= mList.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return mList.at(index.row());

    return QVariant();
}

bool BaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() < 0 || index.row() >= mList.size())
        return false;

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        mList.replace(index.row(), value);
        emit dataChanged(index, index);
    }
    return false;
}

bool BaseModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        mList.insert(row, QVariant::fromValue(BaseTarget()));

    endInsertRows();

    return true;
}

bool BaseModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        mList.removeAt(row);

    endRemoveRows();

    return true;
}



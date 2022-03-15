#include "baseview.h"

#include <QtCore>

BaseView::BaseView(QWidget *parent)
{
    Q_UNUSED(parent);
}

QRect BaseView::visualRect(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QRect();
}

void BaseView::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    Q_UNUSED(index);
    Q_UNUSED(hint);
}

QModelIndex BaseView::indexAt(const QPoint &point) const
{
    Q_UNUSED(point);
    return QModelIndex();
}

QModelIndex BaseView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction);
    Q_UNUSED(modifiers);
    return QModelIndex();
}

int BaseView::horizontalOffset() const
{
    return 0;
}

int BaseView::verticalOffset() const
{
    return 0;
}

bool BaseView::isIndexHidden(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return false;
}

void BaseView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    Q_UNUSED(rect);
    Q_UNUSED(command);
}

QRegion BaseView::visualRegionForSelection(const QItemSelection &selection) const
{
    Q_UNUSED(selection);
    return QRegion();
}


void BaseView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    for(int i=topLeft.row(); i<=bottomRight.row(); ++i) {
        QModelIndex index = this->model()->index(i, 0);
        BaseTarget target = this->model()->data(index).value<BaseTarget>();
        this->updateTarget(i, target);
    }
    QAbstractItemView::dataChanged(topLeft, bottomRight, roles);
}

void BaseView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    for(int i=start; i<=end; ++i)
        this->insertTarget(i);

    QAbstractItemView::rowsInserted(parent, start, end);
}


void BaseView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent);
    for(int i=start; i<=end; ++i)
        this->removeTarget(start);
}

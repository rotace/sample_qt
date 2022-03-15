#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QAbstractItemView>

#include "basetarget.h"

class BaseView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit BaseView(QWidget *parent = 0);
    virtual void updateTarget(int i, BaseTarget &t) = 0;
    virtual void insertTarget(int i) = 0;
    virtual void removeTarget(int i) = 0;

signals:

public slots:

    // QAbstractItemView interface
public:
    QRect visualRect(const QModelIndex &index) const Q_DECL_OVERRIDE;
    void scrollTo(const QModelIndex &index, ScrollHint hint) Q_DECL_OVERRIDE;
    QModelIndex indexAt(const QPoint &point) const Q_DECL_OVERRIDE;

protected:
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;
    int horizontalOffset() const Q_DECL_OVERRIDE;
    int verticalOffset() const Q_DECL_OVERRIDE;
    bool isIndexHidden(const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) Q_DECL_OVERRIDE;
    QRegion visualRegionForSelection(const QItemSelection &selection) const Q_DECL_OVERRIDE;

    // QAbstractItemView interface OVERRIDE
protected slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) Q_DECL_OVERRIDE;
    void rowsInserted(const QModelIndex &parent, int start, int end) Q_DECL_OVERRIDE;
    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) Q_DECL_OVERRIDE;
};

#endif // BASEVIEW_H

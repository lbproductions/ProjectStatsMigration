#ifndef DOKOLIVEGAMEWINDOWNS_POINTSTABLEDELEGATE_H
#define DOKOLIVEGAMEWINDOWNS_POINTSTABLEDELEGATE_H

#include <QItemDelegate>

namespace DokoLiveGameWindowNS {

class PointsTable;

class PointsTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PointsTableDelegate(PointsTable *parent = 0);

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    PointsTable* m_table;
};

}

#endif // DOKOLIVEGAMEWINDOWNS_POINTSTABLEDELEGATE_H

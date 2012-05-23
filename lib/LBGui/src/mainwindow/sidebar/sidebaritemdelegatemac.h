#ifndef SIDEBARITEMDELEGATEMAC_H
#define SIDEBARITEMDELEGATEMAC_H

#include <QStyledItemDelegate>

namespace LBGui {

class SidebarTreeView;

class SidebarItemDelegateMac : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SidebarItemDelegateMac(SidebarTreeView *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    SidebarTreeView* m_view;
};

} // namespace LBGui


#endif // SIDEBARITEMDELEGATEMAC_H

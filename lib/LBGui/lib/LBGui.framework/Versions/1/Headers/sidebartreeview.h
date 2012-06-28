#ifndef SIDEBARTREEVIEW_H
#define SIDEBARTREEVIEW_H

#include <QTreeView>

namespace LBGui {

class Sidebar;
class SidebarChildCategorie;

class SidebarTreeView : public QTreeView
{
    Q_OBJECT
public:
    SidebarTreeView(Sidebar *parent = 0);

//    Database::ChildCategorie *selectedCategorie() const;

//    void dragMoveEvent(QDragMoveEvent *event);
//    void dropEvent(QDropEvent *event);

    void setSelectedIndex(int parent, int child);

signals:
    void categorieChanged(::LBGui::SidebarChildCategorie*);

protected:
    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;

private slots:
    void on_clicked(const QModelIndex&);

//    void on_folderItemAdded(::Database::FolderCategorie* folder,QStandardItem* item);

private:
    QModelIndex m_currentIndex;

//    Models::CategoriesModel *m_model;
};

} // namespace LBGui

#endif // CATEGORIESTREEVIEW_H

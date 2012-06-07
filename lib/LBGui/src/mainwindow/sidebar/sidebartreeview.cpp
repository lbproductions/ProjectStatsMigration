#include "sidebartreeview.h"

#include "../mainwindow.h"
#include "sidebar.h"
#include "sidebarchildcategorie.h"

#ifdef Q_WS_MAC
#   include "sidebaritemdelegatemac.h"
#endif

#include <QHeaderView>
#include <QFont>
#include <QDragMoveEvent>
#include <QPainter>

#include <QDebug>

namespace LBGui {

SidebarTreeView::SidebarTreeView(Sidebar *parent) :
    QTreeView(parent),
//    m_model(0),
    m_currentIndex(QModelIndex())
{
    setUniformRowHeights(false);
    header()->hide();

    setMinimumWidth(100);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setExpandsOnDoubleClick(false);

    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(on_clicked(QModelIndex)));

//    //m_model = Handler::getInstance()->database()->categories()->categoriesModel();
//    m_model = new Models::CategoriesModel(Database::Categories::instance());
//    setModel(m_model);

//    connect(m_model,SIGNAL(folderItemAdded(::Database::FolderCategorie*,QStandardItem*)),
//	    this, SLOT(on_folderItemAdded(::Database::FolderCategorie*,QStandardItem*)));

//    expandAll();

//    selectionModel()->setCurrentIndex(
//	    m_model->index(0,0,m_model->index(0,0,QModelIndex()))
//	    ,QItemSelectionModel::Select);

    //    //connect(Handler::getInstance()->database()->categories(),SIGNAL(rowCreated(::Database::Row*)),this,SLOT(resetModel()));
}

void SidebarTreeView::setSelectedIndex(int parent, int child)
{
    this->selectionModel()->clear();
    QModelIndex index = model()->index(parent,0,model()->index(child,0,QModelIndex()));
    selectionModel()->setCurrentIndex(index,QItemSelectionModel::Select);
    on_clicked(index);
}

//void SidebarTreeView::on_folderItemAdded(::Database::FolderCategorie* folder,QStandardItem* item)
//{

//    if(folder->contentType->value() != Database::ChildCategorie::LeagueCategorieContentType) {
//        selectionModel()->reset();
//        this->edit(item->index());
//        selectionModel()->setCurrentIndex(item->index(),QItemSelectionModel::Select);
//        on_clicked(item->index());
//    }
//}

void SidebarTreeView::on_clicked(const QModelIndex &index)
{
    if(index == m_currentIndex || !index.parent().isValid()) {
        return;
    }

    m_currentIndex = index;
    SidebarChildCategorie *categorie = index.data(SidebarChildCategorie::SelfRole).value<SidebarChildCategorie*>();

    if(categorie == 0) {
        return;
    }

    categorie->emitActivated();
    emit categorieChanged(categorie);
}

void SidebarTreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    if(selectionModel()->isRowSelected(index.row(),index.parent())) {
        static QColor bordertop("#b9c0d3");
        static QColor borderbottom("#959fb9");

        painter->setPen(bordertop);
        painter->drawLine(rect.x(),rect.y(),rect.width(),rect.y());
        painter->setPen(borderbottom);
        painter->drawLine(rect.x(),rect.y() + rect.height() - 1,rect.width(),rect.y() + rect.height() - 1);
    }

    if(index.parent().isValid() && /*!index.parent().parent().isValid() && */model()->hasChildren(index)) {
        static QImage branch_open(":/sidebar/macos_lionmail/branch_open");
        static QImage branch_open_selected(":/sidebar/macos_lionmail/branch_open_selected");
        static QImage branch_closed(":/sidebar/macos_lionmail/branch_closed");
        static QImage branch_closed_selected(":/sidebar/macos_lionmail/branch_closed_selected");
        int xOffset = 5;
        if(index.parent().parent().isValid())
            xOffset += 6;
        if(selectionModel()->isRowSelected(index.row(),index.parent())) {
            if(isExpanded(index)) {
                painter->drawImage(rect.x() + xOffset, rect.y() + 10, branch_open_selected);
            }
            else {
                painter->drawImage(rect.x() + xOffset, rect.y() + 8, branch_closed_selected);
            }


        }
        else {
            if(isExpanded(index)) {
                painter->drawImage(rect.x() + xOffset, rect.y() + 10, branch_open);
            }
            else {
                painter->drawImage(rect.x() + xOffset + 1, rect.y() + 8, branch_closed);
            }
        }
    }
}

//Database::ChildCategorie *SidebarTreeView::selectedCategorie() const
//{
//    if(selectedIndexes().isEmpty())
//    {
//	return 0;
//    }
//    return static_cast<Database::ChildCategorie *>(selectedIndexes().at(0).data(Qt::UserRole + 1).value<void*>());
//}

//void SidebarTreeView::dragMoveEvent(QDragMoveEvent *event)
//{
//    Database::FolderCategorie* c = static_cast<Database::FolderCategorie *>(indexAt(event->pos()).data(Qt::UserRole + 1).value<void*>());

//    if(c == 0 || c->type->value() != Database::Categorie::FolderCategorieType)
//    {
//	event->ignore();
//	return;
//    }

//    if(c->acceptMimeTypes(event->mimeData()->formats()))
//    {
//	event->acceptProposedAction();
//	return;
//    }

//    event->ignore();
//}

//void SidebarTreeView::dropEvent(QDropEvent *event)
//{
//    Database::FolderCategorie* c = static_cast<Database::FolderCategorie *>(indexAt(event->pos()).data(Qt::UserRole + 1).value<void*>());

//    if(c == 0 || c->type->value() != Database::Categorie::FolderCategorieType)
//    {
//	event->ignore();
//	return;
//    }

//    if(c->acceptMimeTypes(event->mimeData()->formats()))
//    {
//	c->dropMimeData(event->mimeData());
//	event->acceptProposedAction();
//	return;
//    }

//    event->ignore();
//}

} // namespace LBGui

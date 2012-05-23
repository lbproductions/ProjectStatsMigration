#include "sidebar.h"

#include "sidebartreeview.h"
#include "sidebarparentcategorie.h"
#include "sidebarchildcategorie.h"
#include "sidebaritemdelegatemac.h"

#include <mainwindow/mainwindow.h>

#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include <QStandardItemModel>

namespace LBGui {

Sidebar::Sidebar(MainWindow *parent) :
    QWidget(parent),
    m_mainWindow(parent),
    m_categoriesModel(new QStandardItemModel(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    m_treeView = new SidebarTreeView(this);
    layout->addWidget(m_treeView);

    m_treeView->setModel(m_categoriesModel);

//#ifdef Q_WS_MAC
//    m_options = new SidebarStatusBar(parent, this);
//    connect(m_options->m_dragButton,SIGNAL(dragged(int)),this,SIGNAL(dragged(int)));
//    layout->addWidget(m_options);
//#endif
    setLayout(layout);
    setStyle(MacOSLionMailStyle);

    setMinimumSize(200,200);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    connect(m_treeView, SIGNAL(categorieChanged(::LBGui::SidebarChildCategorie*)),
            this,       SIGNAL(categorieChanged(::LBGui::SidebarChildCategorie*)));
}

Sidebar::Style Sidebar::style() const
{
    return m_style;
}

void Sidebar::setStyle(Style style)
{
    QFile stylesheet;
    m_style = style;

    switch(m_style) {
    case MacOSLionMailStyle:
        stylesheet.setFileName(QLatin1String(":/sidebar/macos_lionmail/stylesheet"));
        stylesheet.open(QFile::ReadOnly);
        m_treeView->setStyleSheet(stylesheet.readAll());
        stylesheet.close();

        m_treeView->setDropIndicatorShown(true);
        m_treeView->setDragDropMode(QAbstractItemView::DropOnly);
        m_treeView->setAcceptDrops(true);
        m_treeView->setIconSize(QSize(17,17));
        m_treeView->setFrameStyle(QFrame::NoFrame);
        m_treeView->setAttribute(Qt::WA_MacShowFocusRect, false);
        m_treeView->setAutoFillBackground(true);
        m_treeView->setItemDelegate(new SidebarItemDelegateMac(m_treeView));
        m_treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_treeView->setTextElideMode(Qt::ElideMiddle);
        m_treeView->setIndentation(7);
        break;
    default:
        break;
    }

    if(!stylesheet.exists()) {
        qWarning() << "Sidebar::setStyle: The stylesheet file for the style does not exist.";
    }
}

SidebarParentCategorie* Sidebar::addParentCategorie(const QString &title)
{
    SidebarParentCategorie* item = new SidebarParentCategorie(title);
    m_categoriesModel->invisibleRootItem()->appendRow(item);
    return item;
}

SidebarChildCategorie *Sidebar::addChildCategorie(int parentIndex, const QString &title)
{
    return addChildCategorie(parentIndex, -1, title);
}

SidebarChildCategorie *Sidebar::addChildCategorie(int parentIndex, int childIndex, const QString &title)
{
    SidebarChildCategorie* item = new SidebarChildCategorie(title);
    if(childIndex > -1) {
        m_categoriesModel->invisibleRootItem()->child(parentIndex)->child(childIndex)->appendRow(item);
        item->setLevel(2);
    }
    else {
        m_categoriesModel->invisibleRootItem()->child(parentIndex)->appendRow(item);
        item->setLevel(1);
    }
    return item;
}

void Sidebar::removeCategorie(SidebarChildCategorie *categorie)
{
    QStandardItem *parentItem = categorie->QStandardItem::parent();
    parentItem->removeRow(categorie->row());
}

void Sidebar::clearCategorie(int parentIndex)
{
    SidebarParentCategorie* item = static_cast<SidebarParentCategorie*>(m_categoriesModel->invisibleRootItem()->child(parentIndex));
    item->removeRows(0,item->rowCount());
}

void Sidebar::setSelectedCategorie(int parent, int child)
{
    m_treeView->setSelectedIndex(parent,child);
}

void Sidebar::expandAll()
{
    m_treeView->expandAll(); //TODO nur toplevel expanden...
}

} // namespace LBGui

#include "treeview.h"

#include "treeviewheader.h"

#include <QSortFilterProxyModel>
#include <QSettings>
#include <QList>
#include <QItemSelectionRange>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QFile>

namespace LBGui {

TreeView::TreeView(QWidget *parent) :
    QTreeView(parent),
    m_doubleClickActions(0)
{
#ifdef Q_WS_MAC
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setFont(QFont("Lucida Grande",12));
    setFrameStyle(QFrame::NoFrame);
    setAttribute(Qt::WA_MacShowFocusRect, false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
#endif
    setUniformRowHeights(true);
    setHeader(new TreeViewHeader(Qt::Horizontal));
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(this,SIGNAL(activated(QModelIndex)), this, SIGNAL(selectionChanged()));
    connect(this,SIGNAL(pressed(QModelIndex)), this, SIGNAL(selectionChanged()));
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_doubleClicked(QModelIndex)));
}

int TreeView::doubleClickActions() const
{
    return m_doubleClickActions;
}

void TreeView::setDoubleClickActions(int actions)
{
    m_doubleClickActions = actions;
    if(m_doubleClickActions & EditAttributeAction) {
        connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_doubleClicked(QModelIndex)));
    }
}

void TreeView::on_doubleClicked(QModelIndex index)
{
    QModelIndex i = index;
    QSortFilterProxyModel *proyxModel = qobject_cast<QSortFilterProxyModel*>(model());
    if(proyxModel) {
        i = proyxModel->mapToSource(index);
    }

    if(m_doubleClickActions & EditAttributeAction) {
        edit(index);
    }
    if(m_doubleClickActions & EmitSignalAction) {
        emit doubleClicked();
    }
}

TreeView::Style TreeView::style() const
{
    return m_style;
}

void TreeView::setStyle(Style style)
{
    QFile stylesheet;
    m_style = style;

    switch(m_style) {
    case ItunesWhite:
        stylesheet.setFileName(QLatin1String(":/tableview/itunes_white/stylesheet"));
        break;
    }

    if(!stylesheet.exists()) {
        qWarning() << "TableView::setStyle: The stylesheet file for the style does not exist.";
    }

    stylesheet.open(QFile::ReadOnly);
    setStyleSheet(stylesheet.readAll());
    stylesheet.close();
}

} //namespace Gui

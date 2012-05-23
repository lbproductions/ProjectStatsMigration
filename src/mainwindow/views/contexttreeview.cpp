#include "contexttreeview.h"

#include <LBDatabase/LBDatabase.h>

#include <QSortFilterProxyModel>
#include <QHeaderView>

class ContextTreeViewPrivate {
    ContextTreeViewPrivate() : context(0) {}

    void init();
    void resizeAllColumnsToContents();

    LBDatabase::Context *context;
    QSortFilterProxyModel *contextSortProxyModel;

    ContextTreeView * q_ptr;
    Q_DECLARE_PUBLIC(ContextTreeView)
};

void ContextTreeViewPrivate::init()
{
    Q_Q(ContextTreeView);
    q->setSortingEnabled(true);
    q->setUniformRowHeights(true);
    q->setSelectionMode(QAbstractItemView::ExtendedSelection);
    q->setDoubleClickActions(LBGui::TreeView::EmitSignalAction);

    contextSortProxyModel = new QSortFilterProxyModel(q);
    q->setModel(contextSortProxyModel);
}

void ContextTreeViewPrivate::resizeAllColumnsToContents()
{
    Q_Q(ContextTreeView);
    for(int i = 0; i < contextSortProxyModel->columnCount(); ++i) {
        q->resizeColumnToContents(i);
    }
}

ContextTreeView::ContextTreeView(QWidget *parent) :
    TreeView(parent),
    d_ptr(new ContextTreeViewPrivate)
{
    Q_D(ContextTreeView);
    d->q_ptr = this;
    d->init();
}

ContextTreeView::~ContextTreeView()
{
}

void ContextTreeView::setContext(LBDatabase::Context *context)
{
    Q_D(ContextTreeView);
    if(d->context == context)
        return;

    d->contextSortProxyModel->setSourceModel(context);
    d->context = context;
}

LBDatabase::Context *ContextTreeView::context() const
{
    Q_D(const ContextTreeView);
    return d->context;
}

LBDatabase::Entity *ContextTreeView::firstSelectedEntity() const
{
    Q_D(const ContextTreeView);
    if(!d->context)
        return 0;

    QModelIndexList list = selectionModel()->selectedRows();
    if(list.isEmpty())
        return 0;

    QModelIndex index = d->contextSortProxyModel->mapToSource(list.first());
    QList<LBDatabase::Entity*> entities = d->context->entities();
    return entities.at(index.row());
}

QList<LBDatabase::Entity *> ContextTreeView::selectedEntities() const
{
    Q_D(const ContextTreeView);

    QList<LBDatabase::Entity *> entities;

    if(!d->context)
        return entities;

    foreach(QModelIndex i, selectionModel()->selectedRows()) {
        QModelIndex index = d->contextSortProxyModel->mapToSource(i);
        entities.append(d->context->entities().at(index.row()));
    }

    return entities;
}

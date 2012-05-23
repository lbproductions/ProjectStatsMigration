#ifndef CONTEXTTREEVIEW_H
#define CONTEXTTREEVIEW_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Entity;
class Context;
}

class ContextTreeViewPrivate;
class ContextTreeView : public LBGui::TreeView
{
public:
    ContextTreeView(QWidget *parent = 0);
    ~ContextTreeView();

    void setContext(LBDatabase::Context *Context);
    LBDatabase::Context *context() const;

    LBDatabase::Entity *firstSelectedEntity() const;
    QList<LBDatabase::Entity *> selectedEntities() const;

private:
    QScopedPointer<ContextTreeViewPrivate> d_ptr;
    Q_DECLARE_PRIVATE(ContextTreeView)
    Q_DISABLE_COPY(ContextTreeView)
};

#endif // CONTEXTTREEVIEW_H

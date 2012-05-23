#include "treeviewheader.h"

#include <QMenu>
#include <QAction>
#include <QMouseEvent>

namespace LBGui {

TreeViewHeader::TreeViewHeader(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation,parent),
    m_menu(0)
{
    setStretchLastSection(true);
}

void TreeViewHeader::mousePressEvent(QMouseEvent* e)
{
    QHeaderView::mousePressEvent(e);

    if(e->button() == Qt::RightButton) {
        if(!m_menu) {
            m_menu = new QMenu(this);

            for(int i = 0; i < model()->columnCount(); ++i) {
                QString name = model()->headerData(i,Qt::Horizontal).toString();
                QAction *action = new QAction(name,m_menu);
                action->setData(i);
                action->setCheckable(true);
                action->setChecked(!isSectionHidden(i));
                connect(action,SIGNAL(toggled(bool)),this,SLOT(hideHeader(bool)));
                m_menu->addAction(action);
            }
        }
        m_menu->popup(e->globalPos());
    }
}

void TreeViewHeader::hideHeader(bool hide)
{
    QAction *action = static_cast<QAction*>(sender());

    int i = action->data().toInt();

    action->setChecked(hide);
    setSectionHidden(i, !hide);
}

} //namespace Gui

#include "toolbar.h"

#include "mainwindow.h"

#include <QDebug>

namespace LBGui {

ToolBar::ToolBar(MainWindow *parent) :
    QToolBar(parent)
{
    setIconSize(QSize(50,44));
    setMovable(false);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenu(QPoint)));
}

void ToolBar::contextMenu(QPoint /*point*/)
{
    // http://bugreports.qt.nokia.com/browse/QTBUG-11271
    // http://bugreports.qt.nokia.com/browse/QTBUG-14433
    // Geht nicht mit unifiedtoolbar on mac.

    qDebug() << "test";
}

} // namespace LBGui

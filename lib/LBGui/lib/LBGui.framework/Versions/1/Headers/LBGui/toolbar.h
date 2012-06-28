#ifndef LBGUI_TOOLBAR_H
#define LBGUI_TOOLBAR_H

#include <QToolBar>

namespace LBGui {

class MainWindow;

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(MainWindow *parent = 0);
    
private slots:
    void contextMenu(QPoint);
};

} // namespace LBGui

#endif // LBGUI_TOOLBAR_H

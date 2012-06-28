#ifndef LBGUI_VIEW_H
#define LBGUI_VIEW_H

#include <QWidget>

namespace LBGui {

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);
    
public slots:
    virtual void activated();
    
};

} // namespace LBGui

#endif // LBGUI_VIEW_H

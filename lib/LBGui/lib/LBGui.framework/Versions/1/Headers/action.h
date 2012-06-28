#ifndef LBGUI_ACTION_H
#define LBGUI_ACTION_H

#include <QAction>

namespace LBGui {

class Action : public QAction
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = 0);
};

} // namespace LBGui

#endif // LBGUI_ACTION_H

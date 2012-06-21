#ifndef LIVEGAMEWINDOWNS_SIDEBARPAGE_H
#define LIVEGAMEWINDOWNS_SIDEBARPAGE_H

#include <QWidget>

namespace LiveGameWindowNS {

class LiveGameSidebar;

class SidebarPage : public QWidget
{
    Q_OBJECT
public:
    explicit SidebarPage(LiveGameSidebar *parent = 0);
};

} // namespace LiveGameWindowNS

#endif // LIVEGAMEWINDOWNS_SIDEBARPAGE_H

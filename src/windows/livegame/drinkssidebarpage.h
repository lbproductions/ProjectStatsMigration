#ifndef LIVEGAMEWINDOWNS_DRINKSSIDEBARPAGE_H
#define LIVEGAMEWINDOWNS_DRINKSSIDEBARPAGE_H

#include "sidebarpage.h"

class Player;

namespace LiveGameWindowNS {

class DrinksSidebarPage : public SidebarPage
{
public:
    DrinksSidebarPage(LiveGameSidebar *parent = 0);

    void addPlayer(Player *player);
};

} // namespace LiveGameWindowNS

#endif // LIVEGAMEWINDOWNS_DRINKSSIDEBARPAGE_H

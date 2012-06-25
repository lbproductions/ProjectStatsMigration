#ifndef LIVEGAMEWINDOWNS_DRINKSSIDEBARPAGE_H
#define LIVEGAMEWINDOWNS_DRINKSSIDEBARPAGE_H

#include "sidebarpage.h"

class Player;
class LiveGame;

namespace LiveGameWindowNS {

class DrinksSidebarPage : public SidebarPage
{
public:
    DrinksSidebarPage(LiveGameSidebar *parent = 0);


    void setLiveGame(LiveGame *liveGame);
    void addPlayer(Player *player);

private:
    LiveGame *m_liveGame;

    QLayout *m_layout;
    QWidget *m_spacer;
};

} // namespace LiveGameWindowNS

#endif // LIVEGAMEWINDOWNS_DRINKSSIDEBARPAGE_H

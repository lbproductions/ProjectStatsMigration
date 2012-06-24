#include "drinkssidebarpage.h"

#include "playerdrinksgroupbox.h"

#include <model/player.h>

#include <QVBoxLayout>

namespace LiveGameWindowNS {

DrinksSidebarPage::DrinksSidebarPage(LiveGameSidebar *parent) :
    SidebarPage(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    setLayout(l);
}

void DrinksSidebarPage::setLiveGame(LiveGame *liveGame)
{
    m_liveGame = liveGame;
}

void DrinksSidebarPage::addPlayer(Player *player)
{
    PlayerDrinksGroupBox *gb = new PlayerDrinksGroupBox(this);
    gb->setPlayer(player);
    gb->setLiveGame(m_liveGame);
    layout()->addWidget(gb);
}

} // namespace LiveGameWindowNS

#include "drinkssidebarpage.h"

#include "playerdrinksgroupbox.h"

#include <model/player.h>

#include <QVBoxLayout>

namespace LiveGameWindowNS {

DrinksSidebarPage::DrinksSidebarPage(LiveGameSidebar *parent) :
    SidebarPage(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);

    QWidget *w = new QWidget(this);
    w->setObjectName("background");

    QFile stylesheet2(":/stylesheets/livegamesidebar");
    stylesheet2.open(QFile::ReadOnly);
    w->setStyleSheet(stylesheet2.readAll());
    stylesheet2.close();

    m_layout = new QVBoxLayout(w);
    w->setLayout(m_layout);
    l->addWidget(w);

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
    m_layout->addWidget(gb);
}

} // namespace LiveGameWindowNS

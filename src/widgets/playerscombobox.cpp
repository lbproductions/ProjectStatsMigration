#include "playerscombobox.h"

#include <model/player.h>

PlayersComboBox::PlayersComboBox(QWidget *parent) :
    QComboBox(parent)
{
    addItem(tr("---"), 0);
}

void PlayersComboBox::addPlayers(QList<Player *> players)
{
    foreach(Player *player, players) {
        addPlayer(player);
    }
}

void PlayersComboBox::addPlayer(Player * const player)
{
    if(m_players.contains(player))
        return;

    m_players.append(player);
    addItem(QIcon(player->avatar()), player->name(), QVariant::fromValue<Player *>(player));
}

QList<Player *> PlayersComboBox::players() const
{
    return m_players;
}

Player *PlayersComboBox::currentPlayer() const
{
    return itemData(currentIndex()).value<Player *>();
}

void PlayersComboBox::setCurrentPlayer(Player *player)
{
    for(int i = 0; i < count(); ++i) {
        if(itemData(i).value<Player *>() == player) {
            setCurrentIndex(i);
            return;
        }
    }

    setCurrentIndex(0);
}

void PlayersComboBox::removePlayer(Player *player)
{
    for(int i = 0; i < count(); ++i) {
        if(itemData(i).value<Player *>() == player) {
            m_players.removeAll(player);
            removeItem(i);
            return;
        }
    }
}

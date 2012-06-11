#include "playerslistwidget.h"

#include "../model/player.h"
#include "../model/playerscontext.h"

#include <QDebug>

PlayersListWidget::PlayersListWidget(PlayersContext *context, QWidget *parent) :
    QListWidget(parent),
    m_context(context)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void PlayersListWidget::addPlayer(Player *player)
{
    addItem(player->name());
    m_playerPositions.append(player->id());
}

void PlayersListWidget::addPlayers(QList<Player *> players)
{
    foreach(Player *player, players) {
        addPlayer(player);
    }
}

QList<Player *> PlayersListWidget::selectedPlayers() const
{
    QList<Player*> list;
    foreach(QModelIndex index, selectionModel()->selectedRows()) {
        list.append(m_context->player(m_playerPositions.at(index.row())));
    }
    return list;
}

QList<Player *> PlayersListWidget::players() const
{
    QList<Player*> list;
    int c = count();
    for(int i = 0; i < c; ++i) {
        list.append(m_context->player(m_playerPositions.at(i)));
    }
    return list;
}

void PlayersListWidget::removeSelectedPlayers()
{
    int count = 0;
    foreach(QModelIndex index, selectionModel()->selectedRows()) {
        takeItem(index.row() - count);
        m_playerPositions.removeAt(index.row() - count);
        count++;
    }
}

void PlayersListWidget::transferSelectedPlayersFrom(PlayersListWidget *other)
{
    QList<Player*> players = other->selectedPlayers();

    if(players.isEmpty())
        return;

    int row = other->selectionModel()->selectedRows().first().row();
    addPlayers(players);
    other->removeSelectedPlayers();

    other->selectionModel()->setCurrentIndex(
            other->model()->index(row,0)
            ,QItemSelectionModel::Select);
}

void PlayersListWidget::clear()
{
    QListWidget::clear();
    m_playerPositions.clear();
}

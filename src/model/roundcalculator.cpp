#include "roundcalculator.h"

#include "livegame.h"
#include "round.h"
#include "player.h"

RoundCalculator::RoundCalculator(QObject *parent) :
    LBDatabase::Calculator(parent)
{
}

RelatedEntities RoundCalculator::currentPlayingPlayers(const LBDatabase::Entity *entity) const
{
    const Round *round = static_cast<const Round *>(entity);
    RelatedEntities result;
    LiveGame *g = round->game();

    if(!g)
        return result;

    QList<Player *> players = g->players();
    foreach(Player *p, players) {
        result.append(p);
    }
    return result;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

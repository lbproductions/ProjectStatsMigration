#include "livegamecalculator.h"

#include "livegame.h"
#include "player.h"
#include "round.h"
#include "storage.h"
#include "livedrink.h"

#include <LBDatabase/LBDatabase.h>

LiveGameCalculator::LiveGameCalculator(QObject *parent) :
    GameCalculator(parent)
{
}

EntityVariantHash LiveGameCalculator::points(const LBDatabase::Entity *entity) const
{
    const LiveGame *liveGame = static_cast<const LiveGame *>(entity);

    EntityVariantHash result;
    foreach(Player *player, liveGame->players()) {
        foreach(Round *round, liveGame->rounds()) {
            result.insert(player, result.value(player, QVariant(0)).toInt() + round->points(player));
        }
    }

    return result;
}

EntityVariantHash LiveGameCalculator::placement(const LBDatabase::Entity *entity) const
{
	const LiveGame *liveGame = static_cast<const LiveGame *>(entity);
    EntityVariantHash result;
    QList<Player *> list = liveGame->relation<Player>(GameProperties::PlayersRelation)->sort<int>(liveGame->function(LiveGameProperties::PointsFunction), LBDatabase::SortDescending);

    if(list.isEmpty())
        return result;

    int placement = 1;
    foreach(Player *p, list) {
        result.insert(p, placement++);
    }

    return result;
}

QVariant LiveGameCalculator::totalPoints(const LBDatabase::Entity *entity) const
{
	const LiveGame *liveGame = static_cast<const LiveGame *>(entity);

    int result = 0;
    foreach(Round *round, liveGame->rounds()) {
        if(!round->currentPlayingPlayers().isEmpty()) {
            result += qAbs(round->points(round->currentPlayingPlayers().first()));
        }
    }

    return result;
}

EntityVariantHash LiveGameCalculator::drinksPerPlayer(const LBDatabase::Entity *entity) const
{
	const LiveGame *liveGame = static_cast<const LiveGame *>(entity);
    EntityVariantHash result;

    foreach(Player *p, liveGame->players()) {
        QList<LiveDrink *> drinks;

        foreach(LiveDrink *drink, p->liveDrinks()) {
            if(drink->round() && drink->round()->game() == liveGame) {
                drinks.append(drink);
            }
        }

        result.insert(p, QVariant::fromValue<QList<LiveDrink *> >(drinks));
    }

    return result;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

#include "gamecalculator.h"

#include "game.h"
#include "player.h"

GameCalculator::GameCalculator(QObject *parent) :
	Calculator(parent)
{
}

EntityVariantHash GameCalculator::placement(const LBDatabase::Entity *entity) const
{
    const Game *game = static_cast<const Game *>(entity);
    EntityVariantHash result;
    foreach(Player *p, game->players()) {
        result.insert(p, game->position(p));
    }
    return result;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

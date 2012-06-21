#include "doppelkopfroundcalculator.h"

#include "livegame.h"
#include "round.h"
#include "doppelkopfround.h"
#include "player.h"
#include "playerscontext.h"
#include "storage.h"

DoppelkopfRoundCalculator::DoppelkopfRoundCalculator(QObject *parent) :
    RoundCalculator(parent)
{
}

RelatedEntities DoppelkopfRoundCalculator::currentPlayingPlayers(const LBDatabase::Entity *entity) const
{
    const Round *round = static_cast<const Round *>(entity);
    RelatedEntities result;
    LiveGame *g = round->game();

    if(!g)
        return result;

    int anzPlayers = g->players().size();
    int cardmixerPosition = round->number() % anzPlayers;
    for(int i = cardmixerPosition+1, anzahl = 0; anzahl < 4; i++, anzahl++) {

        i = i % anzPlayers;

        if(anzPlayers > 5 && anzahl+1 == anzPlayers / 2)
            ++i;

        i = i % anzPlayers;

        Player *player = g->players().at(i);
        result.append(player);
    }

    return result;
}

EntityVariantHash DoppelkopfRoundCalculator::isRe(const LBDatabase::Entity *entity) const
{
	const DoppelkopfRound *doppelkopfRound = static_cast<const DoppelkopfRound *>(entity);
    Storage *storage = static_cast<Storage *>(doppelkopfRound->context()->storage());

    EntityVariantHash result;
    foreach(Player *player, storage->playersContext()->players()) {
        result.insert(player, player == doppelkopfRound->rePlayer1() || player == doppelkopfRound->rePlayer2());
    }

    return result;
}

EntityVariantHash DoppelkopfRoundCalculator::isContra(const LBDatabase::Entity *entity) const
{
    const DoppelkopfRound *doppelkopfRound = static_cast<const DoppelkopfRound *>(entity);
    Storage *storage = static_cast<Storage *>(doppelkopfRound->context()->storage());

    EntityVariantHash result;
    foreach(Player *player, storage->playersContext()->players()) {
        result.insert(player,
                      doppelkopfRound->currentPlayingPlayers().contains(player) &&
                      player != doppelkopfRound->rePlayer1() && player != doppelkopfRound->rePlayer2());
    }

    return result;
}

QVariant DoppelkopfRoundCalculator::roundPoints(const LBDatabase::Entity *entity) const
{
	const DoppelkopfRound *doppelkopfRound = static_cast<const DoppelkopfRound *>(entity);
    int points = doppelkopfRound->points(doppelkopfRound->rePlayer1());
    if(doppelkopfRound->dokoSoloPlayer())
        points /= 3;
    return points;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

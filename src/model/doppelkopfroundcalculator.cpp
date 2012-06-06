#include "doppelkopfroundcalculator.h"

#include "livegame.h"
#include "round.h"
#include "player.h"

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

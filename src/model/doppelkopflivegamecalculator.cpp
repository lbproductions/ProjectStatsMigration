#include "doppelkopflivegamecalculator.h"

#include "doppelkopflivegame.h"
#include "doppelkopfround.h"
#include "player.h"

DoppelkopfLiveGameCalculator::DoppelkopfLiveGameCalculator(QObject *parent) :
    LiveGameCalculator(parent)
{
}

QVariant DoppelkopfLiveGameCalculator::allowedSoli(const LBDatabase::Entity *entity) const
{
    const DoppelkopfLiveGame *game = static_cast<const DoppelkopfLiveGame *>(entity);
    QStringList soli;
    if(game->doko_mitBubensolo()) {
        soli << "Buben";
    }
    if(game->doko_mitDamensolo()) {
        soli << "Damen";
    }
    if(game->doko_mitFleischlos()) {
        soli << "Fleischlos";
    }
    if(game->doko_mitTrumpfsolo()) {
        soli << "Trumpf";
    }
    if(game->doko_mitFarbsolo()) {
        soli << "Farben";
    }
    if(game->doko_mitSchwarzsolo()) {
        soli << "Schwarz";
    }
    return soli;
}

EntityVariantHash DoppelkopfLiveGameCalculator::hasPflichtsolo(const LBDatabase::Entity *entity) const
{
	const DoppelkopfLiveGame *doppelkopfLiveGame = static_cast<const DoppelkopfLiveGame *>(entity);

    EntityVariantHash result;
    foreach(Round *round, doppelkopfLiveGame->rounds()) {
        DoppelkopfRound *r = static_cast<DoppelkopfRound *>(round);
        if(r->dokoSoloPlayer() && r->doko_soloPflicht()) {
            result.insert(r->dokoSoloPlayer(), true);
        }
    }

    foreach(Player *const p, doppelkopfLiveGame->players()) {
        if(!result.contains(p)) {
            result.insert(p, false);
        }
    }

    return result;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

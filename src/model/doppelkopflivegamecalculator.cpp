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

QVariant DoppelkopfLiveGameCalculator::allowedSchmeissereien(const LBDatabase::Entity *entity) const
{
	const DoppelkopfLiveGame *doppelkopfLiveGame = static_cast<const DoppelkopfLiveGame *>(entity);

    QStringList schmeissereien;
    if(doppelkopfLiveGame->doko_mitFuenfKoenige()) {
        schmeissereien << trUtf8("5 Könige");
    }
    if(doppelkopfLiveGame->doko_mitZuWenigTrumpf()) {
        schmeissereien << tr("< 3 Trumpf");
    }
    if(doppelkopfLiveGame->doko_mitTrumpfabgabeSchmeisserei()) {
        schmeissereien << tr("Trumpfabgabe nicht genommen");
    }
    if(doppelkopfLiveGame->doko_mitNeunzigPunkte()) {
        schmeissereien << tr("> 90 Punkte");
    }

    return schmeissereien;
}

QVariant DoppelkopfLiveGameCalculator::reWins(const LBDatabase::Entity *entity) const
{
	const DoppelkopfLiveGame *doppelkopfLiveGame = static_cast<const DoppelkopfLiveGame *>(entity);

    int wins = 0;
    foreach(Round *r, doppelkopfLiveGame->rounds()) {
        DoppelkopfRound *round = static_cast<DoppelkopfRound *>(r);
        if(round->winner() == DoppelkopfRound::Re)
            ++wins;
    }

    return wins;
}

QVariant DoppelkopfLiveGameCalculator::contraWins(const LBDatabase::Entity *entity) const
{
    const DoppelkopfLiveGame *doppelkopfLiveGame = static_cast<const DoppelkopfLiveGame *>(entity);

    int wins = 0;
    foreach(Round *r, doppelkopfLiveGame->rounds()) {
        DoppelkopfRound *round = static_cast<DoppelkopfRound *>(r);
        if(round->winner() == DoppelkopfRound::Contra)
            ++wins;
    }

    return wins;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

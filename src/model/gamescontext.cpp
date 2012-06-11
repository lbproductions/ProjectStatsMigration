#include "gamescontext.h"

#include "game.h"
#include "gamecalculator.h"
#include "livegame.h"
#include "livegamecalculator.h"
#include "doppelkopflivegame.h"
#include "skatlivegame.h"

const QString GamesContext::Name("Games");
GamesContext::GamesContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Game>();
	registerCalculatorClass<Game,GameCalculator>();

	registerEntityClass<LiveGame>();
	registerCalculatorClass<LiveGame,LiveGameCalculator>();

	registerEntityClass<DoppelkopfLiveGame>();
	registerEntityClass<SkatLiveGame>();
}

Game *GamesContext::game(int id) const
{
	return static_cast<Game *>(entity(id));
}

QList<Game*> GamesContext::games() const
{
	QList<Game *> games;
	foreach(LBDatabase::Entity *entity, entities())
		games.append(static_cast<Game *>(entity));
	return games;
}


	// Write anything you want to remain unchanged between these comments: 
	//START

#include "storage.h"
#include "doppelkopfround.h"
#include "roundscontext.h"

DoppelkopfLiveGame *GamesContext::createDoppelkopfGame()
{
    Storage *psstorage = static_cast<Storage *>(storage());
    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(insertEntity(psstorage->entityType(DoppelkopfLiveGame::EntityTypeId)));
    DoppelkopfRound *round1 = psstorage->roundsContext()->createDoppelkopfRound();
    game->addRound(round1);
    game->setDate(QDateTime::currentDateTime());
    return game;
}

	// END

#include "playerscontext.h"

#include "player.h"
#include "playercalculator.h"

const QString PlayersContext::Name("Players");
PlayersContext::PlayersContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Player>();
	registerCalculatorClass<Player,PlayerCalculator>();

}

Player *PlayersContext::player(int id) const
{
	return static_cast<Player *>(entity(id));
}

QList<Player*> PlayersContext::players() const
{
	QList<Player *> players;
	foreach(LBDatabase::Entity *entity, entities())
		players.append(static_cast<Player *>(entity));
	return players;
}


	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

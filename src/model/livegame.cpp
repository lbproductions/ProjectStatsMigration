#include "livegame.h"

#include "round.h"
#include "player.h"


const QString LiveGame::Name("liveGame");

LiveGame::LiveGame(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Game(metaData, context)
{
}

LiveGame::State LiveGame::state() const
{
	return static_cast<State>(value(LiveGameProperties::StateAttribute).value<int>());
}

QList<Round *> LiveGame::rounds() const
{
	return relation<Round>(LiveGameProperties::RoundsRelation)->entities();
}

int LiveGame::points(const Player *player) const
{
	return function(LiveGameProperties::PointsFunction)->value(player).value<int>();
}

int LiveGame::placement(const Player *player) const
{
    return function(LiveGameProperties::PlacementFunction)->value(player).value<int>();
}

void LiveGame::addRound(Round *round)
{
    relation<Round>(LiveGameProperties::RoundsRelation)->addEntity(round);
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString LiveGame::displayName() const
{
    return Entity::displayName();
}
	// END


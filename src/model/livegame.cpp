#include "livegame.h"

#include "round.h"
#include "player.h"


const QString LiveGame::Name("liveGame");
const int LiveGame::EntityTypeId(22);

LiveGame::LiveGame(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Game(metaData, context)
{
}

LiveGame::State LiveGame::state() const
{
	return static_cast<State>(value(LiveGameProperties::StateAttribute).value<int>());
}

int LiveGame::totalPoints() const
{
	return value(LiveGameProperties::TotalPointsAttribute).value<int>();
}

void LiveGame::setState(State state)
{
	if(state == this->state())
		return;
	setValue(LiveGameProperties::StateAttribute,QVariant::fromValue<int>(state));
	emit stateChanged(state);
}

QList<Round *> LiveGame::rounds() const
{
	return relation<Round>(LiveGameProperties::RoundsRelation)->entities();
}

void LiveGame::addRound(Round *round)
{
	relation<Round>(LiveGameProperties::RoundsRelation)->addEntity(round);
	emit roundsRoundAdded(round);
}

QList<Player *> LiveGame::currentDealer() const
{
	return relation<Player>(LiveGameProperties::CurrentDealerRelation)->entities();
}

int LiveGame::points(const Player *player) const
{
	return function(LiveGameProperties::PointsFunction)->value(player).value<int>();
}

int LiveGame::placement(const Player *player) const
{
	return function(LiveGameProperties::PlacementFunction)->value(player).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString LiveGame::displayName() const
{
	return Entity::displayName();
}

	// END


#include "skatlivegame.h"



const QString SkatLiveGame::Name("skatLiveGame");
const int SkatLiveGame::EntityTypeId(27);

SkatLiveGame::SkatLiveGame(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	LiveGame(metaData, context)
{
}

QString SkatLiveGame::skat_gameEnd() const
{
	return value(SkatLiveGameProperties::Skat_gameEndAttribute).value<QString>();
}

int SkatLiveGame::skat_maxPoints() const
{
	return value(SkatLiveGameProperties::Skat_maxPointsAttribute).value<int>();
}

int SkatLiveGame::skat_maxRounds() const
{
	return value(SkatLiveGameProperties::Skat_maxRoundsAttribute).value<int>();
}

bool SkatLiveGame::skat_mitRamschen() const
{
	return value(SkatLiveGameProperties::Skat_mitRamschenAttribute).value<bool>();
}

void SkatLiveGame::setSkat_gameEnd(const QString &skat_gameEnd)
{
	if(skat_gameEnd == this->skat_gameEnd())
		return;
	setValue(SkatLiveGameProperties::Skat_gameEndAttribute,QVariant::fromValue<QString>(skat_gameEnd));
	emit skat_gameEndChanged(skat_gameEnd);
}

void SkatLiveGame::setSkat_maxPoints(int skat_maxPoints)
{
	if(skat_maxPoints == this->skat_maxPoints())
		return;
	setValue(SkatLiveGameProperties::Skat_maxPointsAttribute,QVariant::fromValue<int>(skat_maxPoints));
	emit skat_maxPointsChanged(skat_maxPoints);
}

void SkatLiveGame::setSkat_maxRounds(int skat_maxRounds)
{
	if(skat_maxRounds == this->skat_maxRounds())
		return;
	setValue(SkatLiveGameProperties::Skat_maxRoundsAttribute,QVariant::fromValue<int>(skat_maxRounds));
	emit skat_maxRoundsChanged(skat_maxRounds);
}

void SkatLiveGame::setSkat_mitRamschen(bool skat_mitRamschen)
{
	if(skat_mitRamschen == this->skat_mitRamschen())
		return;
	setValue(SkatLiveGameProperties::Skat_mitRamschenAttribute,QVariant::fromValue<bool>(skat_mitRamschen));
	emit skat_mitRamschenChanged(skat_mitRamschen);
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString SkatLiveGame::displayName() const
{
	return Entity::displayName();
}

	// END


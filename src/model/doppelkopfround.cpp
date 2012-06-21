#include "doppelkopfround.h"

#include "player.h"
#include "round.h"


const QString DoppelkopfRound::Name("doppelkopfRound");
const int DoppelkopfRound::EntityTypeId(31);

DoppelkopfRound::DoppelkopfRound(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Round(metaData, context)
{
}

bool DoppelkopfRound::doko_soloPflicht() const
{
	return value(DoppelkopfRoundProperties::Doko_soloPflichtAttribute).value<bool>();
}

QString DoppelkopfRound::doko_soloType() const
{
	return value(DoppelkopfRoundProperties::Doko_soloTypeAttribute).value<QString>();
}

int DoppelkopfRound::roundPoints() const
{
	return value(DoppelkopfRoundProperties::RoundPointsAttribute).value<int>();
}

DoppelkopfRound::Winner DoppelkopfRound::winner() const
{
	return static_cast<Winner>(value(DoppelkopfRoundProperties::WinnerAttribute).value<int>());
}

void DoppelkopfRound::setDoko_soloPflicht(bool doko_soloPflicht)
{
	if(doko_soloPflicht == this->doko_soloPflicht())
		return;
	setValue(DoppelkopfRoundProperties::Doko_soloPflichtAttribute,QVariant::fromValue<bool>(doko_soloPflicht));
	emit doko_soloPflichtChanged(doko_soloPflicht);
}

void DoppelkopfRound::setDoko_soloType(const QString &doko_soloType)
{
	if(doko_soloType == this->doko_soloType())
		return;
	setValue(DoppelkopfRoundProperties::Doko_soloTypeAttribute,QVariant::fromValue<QString>(doko_soloType));
	emit doko_soloTypeChanged(doko_soloType);
}

void DoppelkopfRound::setWinner(Winner winner)
{
	if(winner == this->winner())
		return;
	setValue(DoppelkopfRoundProperties::WinnerAttribute,QVariant::fromValue<int>(winner));
	emit winnerChanged(winner);
}

Player *DoppelkopfRound::hochzeitPlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::HochzeitPlayerRelation)->firstEntity();
}

void DoppelkopfRound::setHochzeitPlayer(Player *hochzeitPlayer)
{
	relation<Player>(DoppelkopfRoundProperties::HochzeitPlayerRelation)->addEntity(hochzeitPlayer);
}

Player *DoppelkopfRound::rePlayer1() const
{
	return relation<Player>(DoppelkopfRoundProperties::RePlayer1Relation)->firstEntity();
}

void DoppelkopfRound::setRePlayer1(Player *rePlayer1)
{
	relation<Player>(DoppelkopfRoundProperties::RePlayer1Relation)->addEntity(rePlayer1);
}

Player *DoppelkopfRound::rePlayer2() const
{
	return relation<Player>(DoppelkopfRoundProperties::RePlayer2Relation)->firstEntity();
}

void DoppelkopfRound::setRePlayer2(Player *rePlayer2)
{
	relation<Player>(DoppelkopfRoundProperties::RePlayer2Relation)->addEntity(rePlayer2);
}

Player *DoppelkopfRound::schweinereiPlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::SchweinereiPlayerRelation)->firstEntity();
}

void DoppelkopfRound::setSchweinereiPlayer(Player *schweinereiPlayer)
{
	relation<Player>(DoppelkopfRoundProperties::SchweinereiPlayerRelation)->addEntity(schweinereiPlayer);
}

Player *DoppelkopfRound::trumpfabgabePlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::TrumpfabgabePlayerRelation)->firstEntity();
}

void DoppelkopfRound::setTrumpfabgabePlayer(Player *trumpfabgabePlayer)
{
	relation<Player>(DoppelkopfRoundProperties::TrumpfabgabePlayerRelation)->addEntity(trumpfabgabePlayer);
}

Player *DoppelkopfRound::dokoSoloPlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::DokoSoloPlayerRelation)->firstEntity();
}

void DoppelkopfRound::setDokoSoloPlayer(Player *dokoSoloPlayer)
{
	relation<Player>(DoppelkopfRoundProperties::DokoSoloPlayerRelation)->addEntity(dokoSoloPlayer);
}

QList<Player *> DoppelkopfRound::currentPlayingPlayers() const
{
	return relation<Player>(DoppelkopfRoundProperties::CurrentPlayingPlayersRelation)->entities();
}

bool DoppelkopfRound::isRe(const Player *player) const
{
	return function(DoppelkopfRoundProperties::IsReFunction)->value(player).value<bool>();
}

bool DoppelkopfRound::isContra(const Player *player) const
{
	return function(DoppelkopfRoundProperties::IsContraFunction)->value(player).value<bool>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString DoppelkopfRound::displayName() const
{
	return Entity::displayName();
}

	// END


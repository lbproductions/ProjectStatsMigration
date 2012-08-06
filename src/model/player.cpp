#include "player.h"

#include "schmeisserei.h"
#include "livedrink.h"
#include "doppelkopfround.h"
#include "skatround.h"
#include "place.h"
#include "game.h"
#include "drink.h"
#include "round.h"
#include "livegame.h"


const QString Player::Name("player");
const int Player::EntityTypeId(15);

Player::Player(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

int Player::weight() const
{
	return value(PlayerProperties::WeightAttribute).value<int>();
}

int Player::size() const
{
	return value(PlayerProperties::SizeAttribute).value<int>();
}

QString Player::gender() const
{
	return value(PlayerProperties::GenderAttribute).value<QString>();
}

QString Player::name() const
{
	return value(PlayerProperties::NameAttribute).value<QString>();
}

QColor Player::color() const
{
	return value(PlayerProperties::ColorAttribute).value<QColor>();
}

QPixmap Player::avatar() const
{
	return QPixmap(value(PlayerProperties::AvatarAttribute).toString());
}

int Player::gameCount() const
{
	return value(PlayerProperties::GameCountAttribute).value<int>();
}

int Player::points() const
{
	return value(PlayerProperties::PointsAttribute).value<int>();
}

int Player::gamePoints() const
{
	return value(PlayerProperties::GamePointsAttribute).value<int>();
}

double Player::average() const
{
	return value(PlayerProperties::AverageAttribute).value<double>();
}

double Player::weightedAverage() const
{
	return value(PlayerProperties::WeightedAverageAttribute).value<double>();
}

double Player::diffAverageWeightedAverage() const
{
	return value(PlayerProperties::DiffAverageWeightedAverageAttribute).value<double>();
}

int Player::wins() const
{
	return value(PlayerProperties::WinsAttribute).value<int>();
}

int Player::losses() const
{
	return value(PlayerProperties::LossesAttribute).value<int>();
}

double Player::averagePlacement() const
{
	return value(PlayerProperties::AveragePlacementAttribute).value<double>();
}

QDateTime Player::lastWin() const
{
	return value(PlayerProperties::LastWinAttribute).value<QDateTime>();
}

QDateTime Player::lastGame() const
{
	return value(PlayerProperties::LastGameAttribute).value<QDateTime>();
}

void Player::setWeight(int weight)
{
	if(weight == this->weight())
		return;
	setValue(PlayerProperties::WeightAttribute,QVariant::fromValue<int>(weight));
	emit weightChanged(weight);
}

void Player::setSize(int size)
{
	if(size == this->size())
		return;
	setValue(PlayerProperties::SizeAttribute,QVariant::fromValue<int>(size));
	emit sizeChanged(size);
}

void Player::setGender(const QString &gender)
{
	if(gender == this->gender())
		return;
	setValue(PlayerProperties::GenderAttribute,QVariant::fromValue<QString>(gender));
	emit genderChanged(gender);
}

void Player::setName(const QString &name)
{
	if(name == this->name())
		return;
	setValue(PlayerProperties::NameAttribute,QVariant::fromValue<QString>(name));
	emit nameChanged(name);
}

QList<Schmeisserei *> Player::schmeissereien() const
{
	return relation<Schmeisserei>(PlayerProperties::SchmeissereienRelation)->entities();
}

QList<LiveDrink *> Player::liveDrinks() const
{
	return relation<LiveDrink>(PlayerProperties::LiveDrinksRelation)->entities();
}

void Player::addLiveDrink(LiveDrink *liveDrink)
{
	relation<LiveDrink>(PlayerProperties::LiveDrinksRelation)->addEntity(liveDrink);
	emit liveDrinksChanged();
}

QList<DoppelkopfRound *> Player::dokoHochzeiten() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoHochzeitenRelation)->entities();
}

QList<DoppelkopfRound *> Player::dokoReRounds1() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoReRounds1Relation)->entities();
}

QList<DoppelkopfRound *> Player::dokoReRounds2() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoReRounds2Relation)->entities();
}

QList<DoppelkopfRound *> Player::dokoSchweinereiRounds() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoSchweinereiRoundsRelation)->entities();
}

QList<DoppelkopfRound *> Player::dokoTrumpfabgabeRounds() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoTrumpfabgabeRoundsRelation)->entities();
}

QList<DoppelkopfRound *> Player::dokoRoundSoloPlayer() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoRoundSoloPlayerRelation)->entities();
}

QList<SkatRound *> Player::skatSoloRounds() const
{
	return relation<SkatRound>(PlayerProperties::SkatSoloRoundsRelation)->entities();
}

QList<Place *> Player::places() const
{
	return relation<Place>(PlayerProperties::PlacesRelation)->entities();
}

QList<Game *> Player::games() const
{
	return relation<Game>(PlayerProperties::GamesRelation)->entities();
}

QList<Drink *> Player::drinks() const
{
	return relation<Drink>(PlayerProperties::DrinksRelation)->entities();
}

QList<Round *> Player::rounds() const
{
	return relation<Round>(PlayerProperties::RoundsRelation)->entities();
}

QList<Round *> Player::roundsDealt() const
{
	return relation<Round>(PlayerProperties::RoundsDealtRelation)->entities();
}

QList<LiveGame *> Player::gamesCurrentDealer() const
{
	return relation<LiveGame>(PlayerProperties::GamesCurrentDealerRelation)->entities();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Player::displayName() const
{
    return name();
}

	// END


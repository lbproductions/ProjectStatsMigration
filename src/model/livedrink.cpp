#include "livedrink.h"

#include "round.h"
#include "player.h"
#include "drink.h"


const QString LiveDrink::Name("liveDrink");
const int LiveDrink::EntityTypeId(11);

LiveDrink::LiveDrink(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

QDateTime LiveDrink::time() const
{
	return value(LiveDrinkProperties::TimeAttribute).value<QDateTime>();
}

void LiveDrink::setTime(const QDateTime &time)
{
	if(time == this->time())
		return;
	setValue(LiveDrinkProperties::TimeAttribute,QVariant::fromValue<QDateTime>(time));
	emit timeChanged(time);
}

Round *LiveDrink::round() const
{
	return relation<Round>(LiveDrinkProperties::RoundRelation)->firstEntity();
}

void LiveDrink::setRound(Round *round)
{
	relation<Round>(LiveDrinkProperties::RoundRelation)->addEntity(round);
}

Player *LiveDrink::player() const
{
	return relation<Player>(LiveDrinkProperties::PlayerRelation)->firstEntity();
}

Drink *LiveDrink::drink() const
{
	return relation<Drink>(LiveDrinkProperties::DrinkRelation)->firstEntity();
}

void LiveDrink::setDrink(Drink *drink)
{
	relation<Drink>(LiveDrinkProperties::DrinkRelation)->addEntity(drink);
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString LiveDrink::displayName() const
{
	return Entity::displayName();
}

	// END


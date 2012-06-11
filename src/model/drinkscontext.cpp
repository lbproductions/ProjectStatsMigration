#include "drinkscontext.h"

#include "drink.h"
#include "drinkcalculator.h"

const QString DrinksContext::Name("Drinks");
DrinksContext::DrinksContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Drink>();
	registerCalculatorClass<Drink,DrinkCalculator>();

}

Drink *DrinksContext::drink(int id) const
{
	return static_cast<Drink *>(entity(id));
}

QList<Drink*> DrinksContext::drinks() const
{
	QList<Drink *> drinks;
	foreach(LBDatabase::Entity *entity, entities())
		drinks.append(static_cast<Drink *>(entity));
	return drinks;
}


	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

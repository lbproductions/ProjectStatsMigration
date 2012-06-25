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

QStringList DrinksContext::availableDrinkTypes()
{
    static QStringList list;
    foreach(LBDatabase::Entity *entity, entities()) {
        Drink *d = static_cast<Drink *>(entity);
        if(!list.contains(d->type()))
            list.append(d->type());
    }
    return list;
}

QMultiMap<QString, Drink *> DrinksContext::drinksByType()
{
    QMultiMap<QString, Drink *> hash;
    foreach(LBDatabase::Entity *entity, entities()) {
        Drink *d = static_cast<Drink *>(entity);
        hash.insert(d->type(), d);
    }
    return hash;
}

	// END

#include "livedrinkscontext.h"

#include "livedrink.h"

const QString LiveDrinksContext::Name("LiveDrinks");
LiveDrinksContext::LiveDrinksContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<LiveDrink>();
}

LiveDrink *LiveDrinksContext::liveDrink(int id) const
{
	return static_cast<LiveDrink *>(entity(id));
}

QList<LiveDrink*> LiveDrinksContext::liveDrinks() const
{
	QList<LiveDrink *> liveDrinks;
	foreach(LBDatabase::Entity *entity, entities())
		liveDrinks.append(static_cast<LiveDrink *>(entity));
	return liveDrinks;
}


	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

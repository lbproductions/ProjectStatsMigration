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

#include "storage.h"

LiveDrink *LiveDrinksContext::createLiveDrink()
{
    Storage *psstorage = static_cast<Storage *>(storage());
    LiveDrink *drink = static_cast<LiveDrink *>(insertEntity(psstorage->entityType(LiveDrink::EntityTypeId)));
    drink->setTime(QDateTime::currentDateTime());
    return drink;
}

	// END

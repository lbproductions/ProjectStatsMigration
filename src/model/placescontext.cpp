#include "placescontext.h"

#include "place.h"
#include "placecalculator.h"

const QString PlacesContext::Name("Places");
PlacesContext::PlacesContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Place>();
	registerCalculatorClass<Place,PlaceCalculator>();

}

Place *PlacesContext::place(int id) const
{
	return static_cast<Place *>(entity(id));
}

QList<Place*> PlacesContext::places() const
{
	QList<Place *> places;
	foreach(LBDatabase::Entity *entity, entities())
		places.append(static_cast<Place *>(entity));
	return places;
}


	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

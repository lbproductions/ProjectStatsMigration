#include "placecalculator.h"

#include "place.h"

PlaceCalculator::PlaceCalculator(QObject *parent) :
	Calculator(parent)
{
}

QVariant PlaceCalculator::gameCount(const LBDatabase::Entity *entity) const
{
	const Place *place = static_cast<const Place *>(entity);
    return QVariant(place->games().size());
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

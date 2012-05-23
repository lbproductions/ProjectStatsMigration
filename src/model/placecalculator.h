#ifndef PLACECALCULATOR_H
#define PLACECALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class PlaceCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit PlaceCalculator(QObject *parent = 0);

	
	Q_INVOKABLE QVariant gameCount(const LBDatabase::Entity *entity) const;
};

#endif // PLACECALCULATOR_H

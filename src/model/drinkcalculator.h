#ifndef DRINKCALCULATOR_H
#define DRINKCALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class DrinkCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit DrinkCalculator(QObject *parent = 0);

	
	Q_INVOKABLE QVariant drinkCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant mostDrinks(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE EntityVariantHash countPerPlayer(const LBDatabase::Entity *entity) const;
};

#endif // DRINKCALCULATOR_H

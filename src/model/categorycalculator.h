#ifndef CATEGORYCALCULATOR_H
#define CATEGORYCALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class CategoryCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit CategoryCalculator(QObject *parent = 0);

	
	Q_INVOKABLE QVariant entityTest(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant entityListTest(const LBDatabase::Entity *entity) const;
};

#endif // CATEGORYCALCULATOR_H

#ifndef LIVEGAMECALCULATOR_H
#define LIVEGAMECALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class LiveGameCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit LiveGameCalculator(QObject *parent = 0);

	
	Q_INVOKABLE QVariant state(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE EntityVariantHash points(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE EntityVariantHash placement(const LBDatabase::Entity *entity) const;
};

#endif // LIVEGAMECALCULATOR_H

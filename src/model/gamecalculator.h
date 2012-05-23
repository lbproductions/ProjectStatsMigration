#ifndef GAMECALCULATOR_H
#define GAMECALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class GameCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit GameCalculator(QObject *parent = 0);

	
	Q_INVOKABLE EntityVariantHash placement(const LBDatabase::Entity *entity) const;
};

#endif // GAMECALCULATOR_H

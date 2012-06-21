#ifndef PLAYERCALCULATOR_H
#define PLAYERCALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class PlayerCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit PlayerCalculator(QObject *parent = 0);

	
	Q_INVOKABLE QVariant gameCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant points(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant gamePoints(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant average(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant weightedAverage(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant diffAverageWeightedAverage(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant wins(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant losses(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant averagePlacement(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant lastWin(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant lastGame(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE RelatedEntities roundsDealt(const LBDatabase::Entity *entity) const;
};

#endif // PLAYERCALCULATOR_H

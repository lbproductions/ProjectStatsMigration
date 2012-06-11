#ifndef DOPPELKOPFROUNDCALCULATOR_H
#define DOPPELKOPFROUNDCALCULATOR_H

#include <LBDatabase/LBDatabase.h>


class DoppelkopfRoundCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit DoppelkopfRoundCalculator(QObject *parent = 0);

	
	Q_INVOKABLE RelatedEntities currentPlayingPlayers(const LBDatabase::Entity *entity) const;
};

#endif // DOPPELKOPFROUNDCALCULATOR_H

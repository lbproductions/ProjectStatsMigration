#ifndef DOPPELKOPFROUNDCALCULATOR_H
#define DOPPELKOPFROUNDCALCULATOR_H

#include <LBDatabase/LBDatabase.h>

#include "roundcalculator.h"

class DoppelkopfRoundCalculator : public RoundCalculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit DoppelkopfRoundCalculator(QObject *parent = 0);

	
	Q_INVOKABLE EntityVariantHash isRe(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE EntityVariantHash isContra(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE RelatedEntities currentPlayingPlayers(const LBDatabase::Entity *entity) const;
};

#endif // DOPPELKOPFROUNDCALCULATOR_H

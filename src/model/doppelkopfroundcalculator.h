#ifndef DOPPELKOPFROUNDCALCULATOR_H
#define DOPPELKOPFROUNDCALCULATOR_H

#include "roundcalculator.h"

class DoppelkopfRoundCalculator : public RoundCalculator
{
Q_OBJECT
public:
    Q_INVOKABLE explicit DoppelkopfRoundCalculator(QObject *parent = 0);


    Q_INVOKABLE RelatedEntities currentPlayingPlayers(const LBDatabase::Entity *entity) const;
};

#endif // DOPPELKOPFROUNDCALCULATOR_H

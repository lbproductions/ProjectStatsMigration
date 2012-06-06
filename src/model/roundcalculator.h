#ifndef ROUNDCALCULATOR_H
#define ROUNDCALCULATOR_H

#include <LBDatabase/LBDatabase.h>

class RoundCalculator : public LBDatabase::Calculator
{
Q_OBJECT
public:
    Q_INVOKABLE explicit RoundCalculator(QObject *parent = 0);


    Q_INVOKABLE RelatedEntities currentPlayingPlayers(const LBDatabase::Entity *entity) const;
};

#endif // ROUNDCALCULATOR_H

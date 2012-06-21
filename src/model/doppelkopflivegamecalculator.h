#ifndef DOPPELKOPFLIVEGAMECALCULATOR_H
#define DOPPELKOPFLIVEGAMECALCULATOR_H

#include <LBDatabase/LBDatabase.h>

#include "livegamecalculator.h"

class DoppelkopfLiveGameCalculator : public LiveGameCalculator
{
Q_OBJECT
public:
	Q_INVOKABLE explicit DoppelkopfLiveGameCalculator(QObject *parent = 0);

	
	Q_INVOKABLE QVariant allowedSoli(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant allowedSchmeissereien(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant reWins(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant contraWins(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant hochzeitenCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant soliCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant pflichtsoliCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant trumpfabgabenCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant schmeissereienCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE QVariant schweinereienCount(const LBDatabase::Entity *entity) const;
	
	Q_INVOKABLE EntityVariantHash hasPflichtsolo(const LBDatabase::Entity *entity) const;
};

#endif // DOPPELKOPFLIVEGAMECALCULATOR_H

#include "roundscontext.h"

#include "round.h"
#include "roundcalculator.h"
#include "doppelkopfround.h"
#include "doppelkopfroundcalculator.h"
#include "skatround.h"

const QString RoundsContext::Name("Rounds");
RoundsContext::RoundsContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Round>();
	registerCalculatorClass<Round,RoundCalculator>();

	registerEntityClass<DoppelkopfRound>();
	registerCalculatorClass<DoppelkopfRound,DoppelkopfRoundCalculator>();

	registerEntityClass<SkatRound>();
}

Round *RoundsContext::round(int id) const
{
	return static_cast<Round *>(entity(id));
}

QList<Round*> RoundsContext::rounds() const
{
	QList<Round *> rounds;
	foreach(LBDatabase::Entity *entity, entities())
		rounds.append(static_cast<Round *>(entity));
	return rounds;
}


	// Write anything you want to remain unchanged between these comments: 
	//START

#include "storage.h"

DoppelkopfRound *RoundsContext::createDoppelkopfRound()
{
    Storage *psstorage = static_cast<Storage *>(storage());
    DoppelkopfRound *round = static_cast<DoppelkopfRound *>(insertEntity(psstorage->entityType(DoppelkopfRound::EntityTypeId)));
    round->setState(Round::Running);
    round->setStartTime(QDateTime::currentDateTime());
    round->setNumber(1);
    return round;
}

	// END

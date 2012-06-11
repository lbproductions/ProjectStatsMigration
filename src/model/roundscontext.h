#ifndef ROUNDSCONTEXT_H
#define ROUNDSCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Round;
class DoppelkopfRound;
class SkatRound;

class RoundsContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE RoundsContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Round *round(int id) const;
	QList<Round *> rounds() const;

	// Write anything you want to remain unchanged between these comments: 
	//START

    DoppelkopfRound *createDoppelkopfRound();

	// END
};

#endif // ROUNDSCONTEXT_H

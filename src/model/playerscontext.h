#ifndef PLAYERSCONTEXT_H
#define PLAYERSCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Player;

class PlayersContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE PlayersContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Player *player(int id) const;
	QList<Player *> players() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END
};

#endif // PLAYERSCONTEXT_H

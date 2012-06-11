#ifndef GAMESCONTEXT_H
#define GAMESCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Game;
class LiveGame;
class DoppelkopfLiveGame;
class SkatLiveGame;

class GamesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE GamesContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Game *game(int id) const;
	QList<Game *> games() const;

	// Write anything you want to remain unchanged between these comments: 
    //START
    DoppelkopfLiveGame *createDoppelkopfGame();

	// END
};

#endif // GAMESCONTEXT_H

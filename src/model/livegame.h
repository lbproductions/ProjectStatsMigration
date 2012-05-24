#ifndef LIVEGAME_H
#define LIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "game.h"

namespace LiveGameProperties {
const QString StateAttribute("state");
const QString RoundsRelation("rounds");
const QString PointsFunction("points");
const QString PlacementFunction("placement");
} // namespace LiveGameProperties

class Round;
class Player;
class Round;

class LiveGame : public Game
{
	Q_OBJECT
public:
    Q_INVOKABLE LiveGame(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;

	enum State {
		Running = 1,
		Paused = 2,
		Finished = 3
	};

	State state() const;
    void setState(State state);


	int points(const Player *player) const;
	int placement(const Player *player) const;

    QList<Round *> rounds() const;
    void addRound(Round *round);

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
    void stateChanged(State);
};

Q_DECLARE_METATYPE(QList<LiveGame *>);

#endif // LIVEGAME_H

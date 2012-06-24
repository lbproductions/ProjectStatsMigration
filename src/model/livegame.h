#ifndef LIVEGAME_H
#define LIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "game.h"

namespace LiveGameProperties {
const QString StateAttribute("state");
const QString TotalPointsAttribute("totalPoints");
const QString RoundsRelation("rounds");
const QString CurrentDealerRelation("currentDealer");
const QString PointsFunction("points");
const QString DrinksPerPlayerFunction("drinksPerPlayer");
const QString PlacementFunction("placement");
} // namespace LiveGameProperties

class Round;
class Player;
class LiveDrink;

class LiveGame : public Game
{
	Q_OBJECT
public:
	Q_INVOKABLE LiveGame(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	enum State {
		Running = 1,
		Paused = 2,
		Finished = 3
	};

	State state() const;
	int totalPoints() const;

	void setState(State state);

	int points(const Player *player) const;
	QList<LiveDrink *>  drinksPerPlayer(const Player *player) const;
	int placement(const Player *player) const;


	QList<Round *> rounds() const;
	void addRound(Round *rounds);
	QList<Player *> currentDealer() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void stateChanged(LiveGame::State);
	void totalPointsChanged();
	void roundsRoundAdded(Round *round);
	void currentDealerChanged();
};

Q_DECLARE_METATYPE(QList<LiveGame *>)
Q_DECLARE_METATYPE(LiveGame *)

#endif // LIVEGAME_H

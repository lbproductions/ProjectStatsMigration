#ifndef ROUND_H
#define ROUND_H

#include <LBDatabase/LBDatabase.h>

#include <QDateTime>
#include <QTime>

namespace RoundProperties {
const QString NumberAttribute("number");
const QString CommentAttribute("comment");
const QString StartTimeAttribute("startTime");
const QString LengthAttribute("length");
const QString StateAttribute("state");
const QString LiveDrinksRelation("liveDrinks");
const QString SchmeissereienPerRoundRelation("SchmeissereienPerRound");
const QString GameRelation("game");
const QString CurrentPlayingPlayersRelation("currentPlayingPlayers");
const QString PointsFunction("points");
} // namespace RoundProperties

class LiveDrink;
class Schmeisserei;
class LiveGame;
class Player;

class Round : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Round(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	enum State {
		Running = 1,
		Paused = 2,
		Finished = 3
	};

	int number() const;
	QString comment() const;
	QDateTime startTime() const;
	QTime length() const;
	State state() const;

	void setNumber(int number);
	void setComment(const QString &comment);
	void setStartTime(const QDateTime &startTime);
	void setLength(const QTime &length);
	void setState(State state);

	int points(const Player *player) const;

	void setPoints(const Player *player, int points);

	QList<LiveDrink *> liveDrinks() const;
	QList<Schmeisserei *> schmeissereienPerRound() const;
	LiveGame *game() const;
	QList<Player *> currentPlayingPlayers() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void numberChanged(int number);
	void commentChanged(QString comment);
	void startTimeChanged(QDateTime startTime);
	void lengthChanged(QTime length);
	void stateChanged(State state);
	void pointsChanged(const Player *player,int points);
};

Q_DECLARE_METATYPE(QList<Round *>)

#endif // ROUND_H

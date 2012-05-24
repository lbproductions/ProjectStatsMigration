#ifndef PLAYER_H
#define PLAYER_H

#include <LBDatabase/LBDatabase.h>

#include <QColor>
#include <QPixmap>
#include <QDateTime>
#include <QDateTime>

namespace PlayerProperties {
const QString WeightAttribute("weight");
const QString SizeAttribute("size");
const QString GenderAttribute("gender");
const QString NameAttribute("name");
const QString ColorAttribute("color");
const QString AvatarAttribute("avatar");
const QString GameCountAttribute("gameCount");
const QString PointsAttribute("points");
const QString GamePointsAttribute("gamePoints");
const QString AverageAttribute("average");
const QString WeightedAverageAttribute("weightedAverage");
const QString DiffAverageWeightedAverageAttribute("diffAverageWeightedAverage");
const QString WinsAttribute("wins");
const QString LossesAttribute("losses");
const QString AveragePlacementAttribute("averagePlacement");
const QString LastWinAttribute("lastWin");
const QString LastGameAttribute("lastGame");
const QString SchmeissereienRelation("schmeissereien");
const QString LiveDrinksRelation("liveDrinks");
const QString DokoHochzeitenRelation("dokoHochzeiten");
const QString DokoReRounds1Relation("dokoReRounds1");
const QString DokoReRounds2Relation("dokoReRounds2");
const QString DokoSchweinereiRoundsRelation("dokoSchweinereiRounds");
const QString DokoTrumpfabgabeRoundsRelation("dokoTrumpfabgabeRounds");
const QString DokoRoundSoloPlayerRelation("DokoRoundSoloPlayer");
const QString SkatSoloRoundsRelation("skatSoloRounds");
const QString PlacesRelation("places");
const QString GamesRelation("games");
const QString DrinksRelation("drinks");
} // namespace PlayerProperties

class Schmeisserei;
class LiveDrink;
class DoppelkopfRound;
class SkatRound;
class Place;
class Game;
class Drink;

class Player : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Player(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;

	int weight() const;
	int size() const;
	QString gender() const;
	QString name() const;
	QColor color() const;
	QPixmap avatar() const;
	int gameCount() const;
	int points() const;
	int gamePoints() const;
	double average() const;
	double weightedAverage() const;
	double diffAverageWeightedAverage() const;
	int wins() const;
	int losses() const;
	double averagePlacement() const;
	QDateTime lastWin() const;
	QDateTime lastGame() const;

	void setWeight(int weight);
	void setSize(int size);
	void setGender(const QString &gender);
	void setName(const QString &name);



	QList<Schmeisserei *> schmeissereien() const;
	QList<LiveDrink *> liveDrinks() const;
	QList<DoppelkopfRound *> dokoHochzeiten() const;
	QList<DoppelkopfRound *> dokoReRounds1() const;
	QList<DoppelkopfRound *> dokoReRounds2() const;
	QList<DoppelkopfRound *> dokoSchweinereiRounds() const;
	QList<DoppelkopfRound *> dokoTrumpfabgabeRounds() const;
	QList<DoppelkopfRound *> dokoRoundSoloPlayer() const;
	QList<SkatRound *> skatSoloRounds() const;
	QList<Place *> places() const;
	QList<Game *> games() const;
	QList<Drink *> drinks() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void weightChanged(int weight);
	void sizeChanged(int size);
	void genderChanged(QString gender);
	void nameChanged(QString name);
};

Q_DECLARE_METATYPE(QList<Player *>);

class PlayersContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE PlayersContext(const::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Player *player(int id) const;
    QList<Player *> players() const;
};

#endif // PLAYER_H

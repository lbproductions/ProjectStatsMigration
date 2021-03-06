#ifndef LIVEDRINK_H
#define LIVEDRINK_H

#include <LBDatabase/LBDatabase.h>

#include <QDateTime>

namespace LiveDrinkProperties {
const QString TimeAttribute("time");
const QString RoundRelation("round");
const QString PlayerRelation("player");
const QString DrinkRelation("drink");
} // namespace LiveDrinkProperties

class Round;
class Player;
class Drink;

class LiveDrink : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE LiveDrink(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	QDateTime time() const;

	void setTime(const QDateTime &time);



	Round *round() const;
	void setRound(Round *round);
	Player *player() const;
	Drink *drink() const;
	void setDrink(Drink *drink);

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void timeChanged(QDateTime);
};

Q_DECLARE_METATYPE(QList<LiveDrink *>)
Q_DECLARE_METATYPE(LiveDrink *)

#endif // LIVEDRINK_H

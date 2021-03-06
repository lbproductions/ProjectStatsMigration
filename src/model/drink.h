#ifndef DRINK_H
#define DRINK_H

#include <LBDatabase/LBDatabase.h>

#include <QPixmap>

namespace DrinkProperties {
const QString NameAttribute("name");
const QString TypeAttribute("type");
const QString SizeAttribute("size");
const QString AlcAttribute("alc");
const QString IconAttribute("icon");
const QString DrinkCountAttribute("drinkCount");
const QString MostDrinksAttribute("mostDrinks");
const QString LiveDrinksRelation("liveDrinks");
const QString PlayersRelation("players");
const QString CountPerPlayerFunction("countPerPlayer");
} // namespace DrinkProperties

class LiveDrink;
class Player;

class Drink : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Drink(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	QString name() const;
	QString type() const;
	double size() const;
	double alc() const;
	QPixmap icon() const;
	int drinkCount() const;
	QString mostDrinks() const;

	void setName(const QString &name);
	void setType(const QString &type);
	void setSize(double size);
	void setAlc(double alc);

	int countPerPlayer(const Player *player) const;


	QList<LiveDrink *> liveDrinks() const;
	QList<Player *> players() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void nameChanged(QString);
	void typeChanged(QString);
	void sizeChanged(double);
	void alcChanged(double);
	void drinkCountChanged();
	void mostDrinksChanged();
};

Q_DECLARE_METATYPE(QList<Drink *>)
Q_DECLARE_METATYPE(Drink *)

#endif // DRINK_H

#ifndef DRINKSCONTEXT_H
#define DRINKSCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Drink;

class DrinksContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE DrinksContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Drink *drink(int id) const;
	QList<Drink *> drinks() const;

	// Write anything you want to remain unchanged between these comments: 
	//START

    QStringList availableDrinkTypes();

    QMultiMap<QString, Drink *> drinksByType();

	// END
};

#endif // DRINKSCONTEXT_H

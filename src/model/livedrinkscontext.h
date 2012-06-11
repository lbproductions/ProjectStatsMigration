#ifndef LIVEDRINKSCONTEXT_H
#define LIVEDRINKSCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class LiveDrink;

class LiveDrinksContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE LiveDrinksContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	LiveDrink *liveDrink(int id) const;
	QList<LiveDrink *> liveDrinks() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END
};

#endif // LIVEDRINKSCONTEXT_H

#ifndef STORAGE_H
#define STORAGE_H

#include <LBDatabase/LBDatabase.h>

class CategoriesContext;
class DrinksContext;
class GamesContext;
class LiveDrinksContext;
class PlacesContext;
class PlayersContext;
class RoundsContext;
class RulesContext;
class SchmeissereienContext;

class Storage : public LBDatabase::Storage
{
public:
	Storage(QObject *parent = 0);

	CategoriesContext *categoriesContext() const;
	DrinksContext *drinksContext() const;
	GamesContext *gamesContext() const;
	LiveDrinksContext *liveDrinksContext() const;
	PlacesContext *placesContext() const;
	PlayersContext *playersContext() const;
	RoundsContext *roundsContext() const;
	RulesContext *rulesContext() const;
	SchmeissereienContext *schmeissereienContext() const;
};

#endif // STORAGE_H

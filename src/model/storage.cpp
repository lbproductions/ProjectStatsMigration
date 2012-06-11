#include "storage.h"
#include "categoriescontext.h"
#include "drinkscontext.h"
#include "gamescontext.h"
#include "livedrinkscontext.h"
#include "placescontext.h"
#include "playerscontext.h"
#include "roundscontext.h"
#include "rulescontext.h"
#include "schmeissereiencontext.h"

Storage::Storage(QObject *parent) :
	LBDatabase::Storage(parent)
{
	registerContextType<CategoriesContext>();
	registerContextType<DrinksContext>();
	registerContextType<GamesContext>();
	registerContextType<LiveDrinksContext>();
	registerContextType<PlacesContext>();
	registerContextType<PlayersContext>();
	registerContextType<RoundsContext>();
	registerContextType<RulesContext>();
	registerContextType<SchmeissereienContext>();
}

CategoriesContext *Storage::categoriesContext() const
{
	return static_cast<CategoriesContext *>(context(CategoriesContext::Name));
}

DrinksContext *Storage::drinksContext() const
{
	return static_cast<DrinksContext *>(context(DrinksContext::Name));
}

GamesContext *Storage::gamesContext() const
{
	return static_cast<GamesContext *>(context(GamesContext::Name));
}

LiveDrinksContext *Storage::liveDrinksContext() const
{
	return static_cast<LiveDrinksContext *>(context(LiveDrinksContext::Name));
}

PlacesContext *Storage::placesContext() const
{
	return static_cast<PlacesContext *>(context(PlacesContext::Name));
}

PlayersContext *Storage::playersContext() const
{
	return static_cast<PlayersContext *>(context(PlayersContext::Name));
}

RoundsContext *Storage::roundsContext() const
{
	return static_cast<RoundsContext *>(context(RoundsContext::Name));
}

RulesContext *Storage::rulesContext() const
{
	return static_cast<RulesContext *>(context(RulesContext::Name));
}

SchmeissereienContext *Storage::schmeissereienContext() const
{
	return static_cast<SchmeissereienContext *>(context(SchmeissereienContext::Name));
}


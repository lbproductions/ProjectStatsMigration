#include "projectstatsstorage.h"
#include "category.h"
#include "drink.h"
#include "game.h"
#include "livedrink.h"
#include "place.h"
#include "player.h"
#include "round.h"
#include "rule.h"
#include "schmeisserei.h"

ProjectStatsStorage::ProjectStatsStorage(QObject *parent) :
    Storage(parent)
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

CategoriesContext *ProjectStatsStorage::categoriesContext() const
{
	return static_cast<CategoriesContext *>(context(CategoriesContext::Name));
}

DrinksContext *ProjectStatsStorage::drinksContext() const
{
	return static_cast<DrinksContext *>(context(DrinksContext::Name));
}

GamesContext *ProjectStatsStorage::gamesContext() const
{
	return static_cast<GamesContext *>(context(GamesContext::Name));
}

LiveDrinksContext *ProjectStatsStorage::liveDrinksContext() const
{
	return static_cast<LiveDrinksContext *>(context(LiveDrinksContext::Name));
}

PlacesContext *ProjectStatsStorage::placesContext() const
{
	return static_cast<PlacesContext *>(context(PlacesContext::Name));
}

PlayersContext *ProjectStatsStorage::playersContext() const
{
	return static_cast<PlayersContext *>(context(PlayersContext::Name));
}

RoundsContext *ProjectStatsStorage::roundsContext() const
{
	return static_cast<RoundsContext *>(context(RoundsContext::Name));
}

RulesContext *ProjectStatsStorage::rulesContext() const
{
	return static_cast<RulesContext *>(context(RulesContext::Name));
}

SchmeissereienContext *ProjectStatsStorage::schmeissereienContext() const
{
	return static_cast<SchmeissereienContext *>(context(SchmeissereienContext::Name));
}


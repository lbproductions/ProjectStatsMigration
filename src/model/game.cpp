#include "game.h"

#include "place.h"
#include "player.h"


#include "gamecalculator.h"
#include "livegame.h"
#include "livegamecalculator.h"
#include "doppelkopflivegame.h"

#include "projectstatsstorage.h"
#include "round.h"
#include "doppelkopfround.h"

const QString GamesContext::Name("Games");
const QString Game::Name("game");

Game::Game(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

QString Game::name() const
{
	return value(GameProperties::NameAttribute).value<QString>();
}

QDateTime Game::date() const
{
	return value(GameProperties::DateAttribute).value<QDateTime>();
}

QTime Game::length() const
{
	return value(GameProperties::LengthAttribute).value<QTime>();
}

QString Game::comment() const
{
	return value(GameProperties::CommentAttribute).value<QString>();
}

void Game::setName(const QString &name)
{
	if(name == this->name())
		return;
	setValue(GameProperties::NameAttribute,QVariant::fromValue<QString>(name));
	emit nameChanged(name);
}

void Game::setDate(const QDateTime &date)
{
	if(date == this->date())
		return;
	setValue(GameProperties::DateAttribute,QVariant::fromValue<QDateTime>(date));
	emit dateChanged(date);
}

void Game::setLength(const QTime &length)
{
	if(length == this->length())
		return;
	setValue(GameProperties::LengthAttribute,QVariant::fromValue<QTime>(length));
	emit lengthChanged(length);
}

void Game::setComment(const QString &comment)
{
	if(comment == this->comment())
		return;
	setValue(GameProperties::CommentAttribute,QVariant::fromValue<QString>(comment));
	emit commentChanged(comment);
}

Place *Game::site() const
{
	return relation<Place>(GameProperties::SiteRelation)->firstEntity();
}

QList<Player *> Game::players() const
{
    return relation<Player>(GameProperties::PlayersRelation)->entities();
}

void Game::addPlayer(Player *player)
{
    relation<Player>(GameProperties::PlayersRelation)->addEntity(player);
}

int Game::position(const Player *player) const
{
	return function(GameProperties::PositionFunction)->value(player).value<int>();
}

int Game::placement(const Player *player) const
{
	return function(GameProperties::PlacementFunction)->value(player).value<int>();
}

void Game::setPosition(const Player *player, int position)
{
	if(position == this->position(player))
		return;
	function(GameProperties::PositionFunction)->setValue(player, QVariant::fromValue<int>(position));
	emit positionChanged(player,position);
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Game::displayName() const
{
    return Entity::displayName();
}
int Game::points(const Player *player) const
{
    Q_UNUSED(player);
    return 0;
}

	// END

GamesContext::GamesContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	Context(metaData, parent)
{
	registerEntityClass<Game>();
	registerCalculatorClass<Game,GameCalculator>();

	registerEntityClass<LiveGame>();
	registerCalculatorClass<LiveGame,LiveGameCalculator>();

    registerEntityClass<DoppelkopfLiveGame>();
}

DoppelkopfLiveGame *GamesContext::createDoppelkopfGame()
{
    ProjectStatsStorage *psstorage = static_cast<ProjectStatsStorage *>(storage());
    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(insertEntity(psstorage->entityType(DoppelkopfLiveGame::EntityTypeId)));
    DoppelkopfRound *round1 = psstorage->roundsContext()->createDoppelkopfRound();
    game->addRound(round1);
    game->setDate(QDateTime::currentDateTime());
    return game;
}

Game *GamesContext::game(int id) const
{
	return static_cast<Game *>(entity(id));
}


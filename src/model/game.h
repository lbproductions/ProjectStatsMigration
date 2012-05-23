#ifndef GAME_H
#define GAME_H

#include <LBDatabase/LBDatabase.h>

#include <QDateTime>
#include <QTime>

namespace GameProperties {
const QString NameAttribute("name");
const QString DateAttribute("date");
const QString LengthAttribute("length");
const QString CommentAttribute("comment");
const QString SiteRelation("site");
const QString PlayersRelation("players");
const QString PositionFunction("position");
const QString PlacementFunction("placement");
} // namespace GameProperties

class Place;
class Player;

class DoppelkopfLiveGame;

class Game : public LBDatabase::Entity
{
	Q_OBJECT
public:
    Q_INVOKABLE Game(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;

	QString name() const;
	QDateTime date() const;
	QTime length() const;
	QString comment() const;

	void setName(const QString &name);
	void setDate(const QDateTime &date);
	void setLength(const QTime &length);
	void setComment(const QString &comment);

	int position(const Player *player) const;
	int placement(const Player *player) const;

	void setPosition(const Player *player, int position);

	Place *site() const;
	QList<Player *> players() const;
    void addPlayer(Player *player);

	// Write anything you want to remain unchanged between these comments: 
	//START

    virtual int points(const Player *player) const;

	// END

signals:
	void nameChanged(QString name);
	void dateChanged(QDateTime date);
	void lengthChanged(QTime length);
	void commentChanged(QString comment);
	void positionChanged(const Player *player,int position);
};

class GamesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
    Q_INVOKABLE GamesContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

    DoppelkopfLiveGame *createDoppelkopfGame();

	Game *game(int id) const;
};

#endif // GAME_H

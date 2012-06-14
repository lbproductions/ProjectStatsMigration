#ifndef PLACE_H
#define PLACE_H

#include <LBDatabase/LBDatabase.h>

#include <QIcon>

namespace PlaceProperties {
const QString PlzAttribute("plz");
const QString OrtAttribute("ort");
const QString StrasseAttribute("strasse");
const QString NummerAttribute("nummer");
const QString CommentAttribute("comment");
const QString IconPathAttribute("iconPath");
const QString GameCountAttribute("gameCount");
const QString GamesRelation("games");
const QString PlayersRelation("players");
} // namespace PlaceProperties

class Game;
class Player;

class Place : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Place(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	int plz() const;
	QString ort() const;
	QString strasse() const;
	int nummer() const;
	QString comment() const;
	QIcon iconPath() const;
	int gameCount() const;

	void setPlz(int plz);
	void setOrt(const QString &ort);
	void setStrasse(const QString &strasse);
	void setNummer(int nummer);
	void setComment(const QString &comment);



	QList<Game *> games() const;
	void addGame(Game *games);
	QList<Player *> players() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void plzChanged(int plz);
	void ortChanged(QString ort);
	void strasseChanged(QString strasse);
	void nummerChanged(int nummer);
	void commentChanged(QString comment);
	void gamesGameAdded(Game *game);
};

Q_DECLARE_METATYPE(QList<Place *>)

#endif // PLACE_H

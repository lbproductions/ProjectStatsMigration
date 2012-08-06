#include "place.h"

#include "game.h"
#include "player.h"


const QString Place::Name("place");
const int Place::EntityTypeId(13);

Place::Place(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

int Place::plz() const
{
	return value(PlaceProperties::PlzAttribute).value<int>();
}

QString Place::ort() const
{
	return value(PlaceProperties::OrtAttribute).value<QString>();
}

QString Place::strasse() const
{
	return value(PlaceProperties::StrasseAttribute).value<QString>();
}

int Place::nummer() const
{
	return value(PlaceProperties::NummerAttribute).value<int>();
}

QString Place::comment() const
{
	return value(PlaceProperties::CommentAttribute).value<QString>();
}

QIcon Place::iconPath() const
{
	return value(PlaceProperties::IconPathAttribute).value<QIcon>();
}

int Place::gameCount() const
{
	return value(PlaceProperties::GameCountAttribute).value<int>();
}

void Place::setPlz(int plz)
{
	if(plz == this->plz())
		return;
	setValue(PlaceProperties::PlzAttribute,QVariant::fromValue<int>(plz));
	emit plzChanged(plz);
}

void Place::setOrt(const QString &ort)
{
	if(ort == this->ort())
		return;
	setValue(PlaceProperties::OrtAttribute,QVariant::fromValue<QString>(ort));
	emit ortChanged(ort);
}

void Place::setStrasse(const QString &strasse)
{
	if(strasse == this->strasse())
		return;
	setValue(PlaceProperties::StrasseAttribute,QVariant::fromValue<QString>(strasse));
	emit strasseChanged(strasse);
}

void Place::setNummer(int nummer)
{
	if(nummer == this->nummer())
		return;
	setValue(PlaceProperties::NummerAttribute,QVariant::fromValue<int>(nummer));
	emit nummerChanged(nummer);
}

void Place::setComment(const QString &comment)
{
	if(comment == this->comment())
		return;
	setValue(PlaceProperties::CommentAttribute,QVariant::fromValue<QString>(comment));
	emit commentChanged(comment);
}

QList<Game *> Place::games() const
{
	return relation<Game>(PlaceProperties::GamesRelation)->entities();
}

void Place::addGame(Game *game)
{
	relation<Game>(PlaceProperties::GamesRelation)->addEntity(game);
	emit gamesChanged();
}

QList<Player *> Place::players() const
{
	return relation<Player>(PlaceProperties::PlayersRelation)->entities();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Place::displayName() const
{
    return strasse() + QLatin1String(" ") + QString::number(nummer()) + QLatin1String(", ") + QString::number(plz()) + QLatin1String(" ") + ort();
}

	// END


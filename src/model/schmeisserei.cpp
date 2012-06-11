#include "schmeisserei.h"

#include "player.h"
#include "round.h"


const QString Schmeisserei::Name("schmeisserei");
const int Schmeisserei::EntityTypeId(21);

Schmeisserei::Schmeisserei(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

QString Schmeisserei::type() const
{
	return value(SchmeissereiProperties::TypeAttribute).value<QString>();
}

void Schmeisserei::setType(const QString &type)
{
	if(type == this->type())
		return;
	setValue(SchmeissereiProperties::TypeAttribute,QVariant::fromValue<QString>(type));
	emit typeChanged(type);
}

Player *Schmeisserei::player() const
{
	return relation<Player>(SchmeissereiProperties::PlayerRelation)->firstEntity();
}

Round *Schmeisserei::round() const
{
	return relation<Round>(SchmeissereiProperties::RoundRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Schmeisserei::displayName() const
{
	return Entity::displayName();
}

	// END


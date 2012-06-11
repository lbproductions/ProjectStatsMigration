#include "skatround.h"

#include "player.h"


const QString SkatRound::Name("skatRound");
const int SkatRound::EntityTypeId(32);

SkatRound::SkatRound(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Round(metaData, context)
{
}

QString SkatRound::skat_gameType() const
{
	return value(SkatRoundProperties::Skat_gameTypeAttribute).value<QString>();
}

QString SkatRound::skat_trumpfColor() const
{
	return value(SkatRoundProperties::Skat_trumpfColorAttribute).value<QString>();
}

void SkatRound::setSkat_gameType(const QString &skat_gameType)
{
	if(skat_gameType == this->skat_gameType())
		return;
	setValue(SkatRoundProperties::Skat_gameTypeAttribute,QVariant::fromValue<QString>(skat_gameType));
	emit skat_gameTypeChanged(skat_gameType);
}

void SkatRound::setSkat_trumpfColor(const QString &skat_trumpfColor)
{
	if(skat_trumpfColor == this->skat_trumpfColor())
		return;
	setValue(SkatRoundProperties::Skat_trumpfColorAttribute,QVariant::fromValue<QString>(skat_trumpfColor));
	emit skat_trumpfColorChanged(skat_trumpfColor);
}

Player *SkatRound::skatSoloPlayer() const
{
	return relation<Player>(SkatRoundProperties::SkatSoloPlayerRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString SkatRound::displayName() const
{
	return Entity::displayName();
}

	// END


#include "doppelkopflivegame.h"



const QString DoppelkopfLiveGame::Name("doppelkopfLiveGame");
const int DoppelkopfLiveGame::EntityTypeId(23);

DoppelkopfLiveGame::DoppelkopfLiveGame(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	LiveGame(metaData, context)
{
}

bool DoppelkopfLiveGame::doko_mitHochzeit() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitHochzeitAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitPflichtsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitPflichtsoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSchmeisserei() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSchmeissereiAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSchweinerei() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSchweinereiAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitTrumpfabgabe() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitTrumpfabgabeAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitBubensolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitBubensoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitDamensolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitDamensoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFarbsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFarbsoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFleischloss() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFleischlossAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFuenfKoenige() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFuenfKoenigeAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitNeunzigPunkte() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitNeunzigPunkteAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitTrumpfabgabeSchmeisserei() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitTrumpfabgabeSchmeissereiAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitTrumpfsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitTrumpfsoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitZuWenigTrumpf() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitZuWenigTrumpfAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFleischlos() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFleischlosAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSchwarzsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSchwarzsoloAttribute).value<bool>();
}

void DoppelkopfLiveGame::setDoko_mitHochzeit(bool doko_mitHochzeit)
{
	if(doko_mitHochzeit == this->doko_mitHochzeit())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitHochzeitAttribute,QVariant::fromValue<bool>(doko_mitHochzeit));
	emit doko_mitHochzeitChanged(doko_mitHochzeit);
}

void DoppelkopfLiveGame::setDoko_mitPflichtsolo(bool doko_mitPflichtsolo)
{
	if(doko_mitPflichtsolo == this->doko_mitPflichtsolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitPflichtsoloAttribute,QVariant::fromValue<bool>(doko_mitPflichtsolo));
	emit doko_mitPflichtsoloChanged(doko_mitPflichtsolo);
}

void DoppelkopfLiveGame::setDoko_mitSchmeisserei(bool doko_mitSchmeisserei)
{
	if(doko_mitSchmeisserei == this->doko_mitSchmeisserei())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitSchmeissereiAttribute,QVariant::fromValue<bool>(doko_mitSchmeisserei));
	emit doko_mitSchmeissereiChanged(doko_mitSchmeisserei);
}

void DoppelkopfLiveGame::setDoko_mitSchweinerei(bool doko_mitSchweinerei)
{
	if(doko_mitSchweinerei == this->doko_mitSchweinerei())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitSchweinereiAttribute,QVariant::fromValue<bool>(doko_mitSchweinerei));
	emit doko_mitSchweinereiChanged(doko_mitSchweinerei);
}

void DoppelkopfLiveGame::setDoko_mitSolo(bool doko_mitSolo)
{
	if(doko_mitSolo == this->doko_mitSolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitSoloAttribute,QVariant::fromValue<bool>(doko_mitSolo));
	emit doko_mitSoloChanged(doko_mitSolo);
}

void DoppelkopfLiveGame::setDoko_mitTrumpfabgabe(bool doko_mitTrumpfabgabe)
{
	if(doko_mitTrumpfabgabe == this->doko_mitTrumpfabgabe())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitTrumpfabgabeAttribute,QVariant::fromValue<bool>(doko_mitTrumpfabgabe));
	emit doko_mitTrumpfabgabeChanged(doko_mitTrumpfabgabe);
}

void DoppelkopfLiveGame::setDoko_mitBubensolo(bool doko_mitBubensolo)
{
	if(doko_mitBubensolo == this->doko_mitBubensolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitBubensoloAttribute,QVariant::fromValue<bool>(doko_mitBubensolo));
	emit doko_mitBubensoloChanged(doko_mitBubensolo);
}

void DoppelkopfLiveGame::setDoko_mitDamensolo(bool doko_mitDamensolo)
{
	if(doko_mitDamensolo == this->doko_mitDamensolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitDamensoloAttribute,QVariant::fromValue<bool>(doko_mitDamensolo));
	emit doko_mitDamensoloChanged(doko_mitDamensolo);
}

void DoppelkopfLiveGame::setDoko_mitFarbsolo(bool doko_mitFarbsolo)
{
	if(doko_mitFarbsolo == this->doko_mitFarbsolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitFarbsoloAttribute,QVariant::fromValue<bool>(doko_mitFarbsolo));
	emit doko_mitFarbsoloChanged(doko_mitFarbsolo);
}

void DoppelkopfLiveGame::setDoko_mitFleischloss(bool doko_mitFleischloss)
{
	if(doko_mitFleischloss == this->doko_mitFleischloss())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitFleischlossAttribute,QVariant::fromValue<bool>(doko_mitFleischloss));
	emit doko_mitFleischlossChanged(doko_mitFleischloss);
}

void DoppelkopfLiveGame::setDoko_mitFuenfKoenige(bool doko_mitFuenfKoenige)
{
	if(doko_mitFuenfKoenige == this->doko_mitFuenfKoenige())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitFuenfKoenigeAttribute,QVariant::fromValue<bool>(doko_mitFuenfKoenige));
	emit doko_mitFuenfKoenigeChanged(doko_mitFuenfKoenige);
}

void DoppelkopfLiveGame::setDoko_mitNeunzigPunkte(bool doko_mitNeunzigPunkte)
{
	if(doko_mitNeunzigPunkte == this->doko_mitNeunzigPunkte())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitNeunzigPunkteAttribute,QVariant::fromValue<bool>(doko_mitNeunzigPunkte));
	emit doko_mitNeunzigPunkteChanged(doko_mitNeunzigPunkte);
}

void DoppelkopfLiveGame::setDoko_mitTrumpfabgabeSchmeisserei(bool doko_mitTrumpfabgabeSchmeisserei)
{
	if(doko_mitTrumpfabgabeSchmeisserei == this->doko_mitTrumpfabgabeSchmeisserei())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitTrumpfabgabeSchmeissereiAttribute,QVariant::fromValue<bool>(doko_mitTrumpfabgabeSchmeisserei));
	emit doko_mitTrumpfabgabeSchmeissereiChanged(doko_mitTrumpfabgabeSchmeisserei);
}

void DoppelkopfLiveGame::setDoko_mitTrumpfsolo(bool doko_mitTrumpfsolo)
{
	if(doko_mitTrumpfsolo == this->doko_mitTrumpfsolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitTrumpfsoloAttribute,QVariant::fromValue<bool>(doko_mitTrumpfsolo));
	emit doko_mitTrumpfsoloChanged(doko_mitTrumpfsolo);
}

void DoppelkopfLiveGame::setDoko_mitZuWenigTrumpf(bool doko_mitZuWenigTrumpf)
{
	if(doko_mitZuWenigTrumpf == this->doko_mitZuWenigTrumpf())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitZuWenigTrumpfAttribute,QVariant::fromValue<bool>(doko_mitZuWenigTrumpf));
	emit doko_mitZuWenigTrumpfChanged(doko_mitZuWenigTrumpf);
}

void DoppelkopfLiveGame::setDoko_mitFleischlos(bool doko_mitFleischlos)
{
	if(doko_mitFleischlos == this->doko_mitFleischlos())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitFleischlosAttribute,QVariant::fromValue<bool>(doko_mitFleischlos));
	emit doko_mitFleischlosChanged(doko_mitFleischlos);
}

void DoppelkopfLiveGame::setDoko_mitSchwarzsolo(bool doko_mitSchwarzsolo)
{
	if(doko_mitSchwarzsolo == this->doko_mitSchwarzsolo())
		return;
	setValue(DoppelkopfLiveGameProperties::Doko_mitSchwarzsoloAttribute,QVariant::fromValue<bool>(doko_mitSchwarzsolo));
	emit doko_mitSchwarzsoloChanged(doko_mitSchwarzsolo);
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString DoppelkopfLiveGame::displayName() const
{
	return Entity::displayName();
}

const QString DoppelkopfLiveGame::GameName(QObject::tr("Doppelkopf"));

	// END


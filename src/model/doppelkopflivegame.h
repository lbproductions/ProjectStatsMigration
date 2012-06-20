#ifndef DOPPELKOPFLIVEGAME_H
#define DOPPELKOPFLIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include <QStringList>
#include "livegame.h"

namespace DoppelkopfLiveGameProperties {
const QString Doko_mitHochzeitAttribute("doko_mitHochzeit");
const QString Doko_mitPflichtsoloAttribute("doko_mitPflichtsolo");
const QString Doko_mitSchmeissereiAttribute("doko_mitSchmeisserei");
const QString Doko_mitSchweinereiAttribute("doko_mitSchweinerei");
const QString Doko_mitSoloAttribute("doko_mitSolo");
const QString Doko_mitTrumpfabgabeAttribute("doko_mitTrumpfabgabe");
const QString Doko_mitBubensoloAttribute("doko_mitBubensolo");
const QString Doko_mitDamensoloAttribute("doko_mitDamensolo");
const QString Doko_mitFarbsoloAttribute("doko_mitFarbsolo");
const QString Doko_mitFleischlossAttribute("doko_mitFleischloss");
const QString Doko_mitFuenfKoenigeAttribute("doko_mitFuenfKoenige");
const QString Doko_mitNeunzigPunkteAttribute("doko_mitNeunzigPunkte");
const QString Doko_mitTrumpfabgabeSchmeissereiAttribute("doko_mitTrumpfabgabeSchmeisserei");
const QString Doko_mitTrumpfsoloAttribute("doko_mitTrumpfsolo");
const QString Doko_mitZuWenigTrumpfAttribute("doko_mitZuWenigTrumpf");
const QString Doko_mitFleischlosAttribute("doko_mitFleischlos");
const QString Doko_mitSchwarzsoloAttribute("doko_mitSchwarzsolo");
const QString AllowedSoliAttribute("allowedSoli");
const QString HasPflichtsoloFunction("hasPflichtsolo");
} // namespace DoppelkopfLiveGameProperties

class Player;

class DoppelkopfLiveGame : public LiveGame
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfLiveGame(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	bool doko_mitHochzeit() const;
	bool doko_mitPflichtsolo() const;
	bool doko_mitSchmeisserei() const;
	bool doko_mitSchweinerei() const;
	bool doko_mitSolo() const;
	bool doko_mitTrumpfabgabe() const;
	bool doko_mitBubensolo() const;
	bool doko_mitDamensolo() const;
	bool doko_mitFarbsolo() const;
	bool doko_mitFleischloss() const;
	bool doko_mitFuenfKoenige() const;
	bool doko_mitNeunzigPunkte() const;
	bool doko_mitTrumpfabgabeSchmeisserei() const;
	bool doko_mitTrumpfsolo() const;
	bool doko_mitZuWenigTrumpf() const;
	bool doko_mitFleischlos() const;
	bool doko_mitSchwarzsolo() const;
	QStringList allowedSoli() const;

	void setDoko_mitHochzeit(bool doko_mitHochzeit);
	void setDoko_mitPflichtsolo(bool doko_mitPflichtsolo);
	void setDoko_mitSchmeisserei(bool doko_mitSchmeisserei);
	void setDoko_mitSchweinerei(bool doko_mitSchweinerei);
	void setDoko_mitSolo(bool doko_mitSolo);
	void setDoko_mitTrumpfabgabe(bool doko_mitTrumpfabgabe);
	void setDoko_mitBubensolo(bool doko_mitBubensolo);
	void setDoko_mitDamensolo(bool doko_mitDamensolo);
	void setDoko_mitFarbsolo(bool doko_mitFarbsolo);
	void setDoko_mitFleischloss(bool doko_mitFleischloss);
	void setDoko_mitFuenfKoenige(bool doko_mitFuenfKoenige);
	void setDoko_mitNeunzigPunkte(bool doko_mitNeunzigPunkte);
	void setDoko_mitTrumpfabgabeSchmeisserei(bool doko_mitTrumpfabgabeSchmeisserei);
	void setDoko_mitTrumpfsolo(bool doko_mitTrumpfsolo);
	void setDoko_mitZuWenigTrumpf(bool doko_mitZuWenigTrumpf);
	void setDoko_mitFleischlos(bool doko_mitFleischlos);
	void setDoko_mitSchwarzsolo(bool doko_mitSchwarzsolo);

	bool hasPflichtsolo(const Player *player) const;



	// Write anything you want to remain unchanged between these comments: 
	//START

    Round *addRound();
    static const QString GameName;

	// END

signals:
	void doko_mitHochzeitChanged(bool);
	void doko_mitPflichtsoloChanged(bool);
	void doko_mitSchmeissereiChanged(bool);
	void doko_mitSchweinereiChanged(bool);
	void doko_mitSoloChanged(bool);
	void doko_mitTrumpfabgabeChanged(bool);
	void doko_mitBubensoloChanged(bool);
	void doko_mitDamensoloChanged(bool);
	void doko_mitFarbsoloChanged(bool);
	void doko_mitFleischlossChanged(bool);
	void doko_mitFuenfKoenigeChanged(bool);
	void doko_mitNeunzigPunkteChanged(bool);
	void doko_mitTrumpfabgabeSchmeissereiChanged(bool);
	void doko_mitTrumpfsoloChanged(bool);
	void doko_mitZuWenigTrumpfChanged(bool);
	void doko_mitFleischlosChanged(bool);
	void doko_mitSchwarzsoloChanged(bool);
	void allowedSoliChanged();
};

Q_DECLARE_METATYPE(QList<DoppelkopfLiveGame *>)
Q_DECLARE_METATYPE(DoppelkopfLiveGame *)

#endif // DOPPELKOPFLIVEGAME_H

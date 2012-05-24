#ifndef DOPPELKOPFLIVEGAME_H
#define DOPPELKOPFLIVEGAME_H

#include <LBDatabase/LBDatabase.h>

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
} // namespace DoppelkopfLiveGameProperties

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

	// Write anything you want to remain unchanged between these comments: 
	//START

    static const QString GameName;

	// END

signals:
	void doko_mitHochzeitChanged(bool doko_mitHochzeit);
	void doko_mitPflichtsoloChanged(bool doko_mitPflichtsolo);
	void doko_mitSchmeissereiChanged(bool doko_mitSchmeisserei);
	void doko_mitSchweinereiChanged(bool doko_mitSchweinerei);
	void doko_mitSoloChanged(bool doko_mitSolo);
	void doko_mitTrumpfabgabeChanged(bool doko_mitTrumpfabgabe);
	void doko_mitBubensoloChanged(bool doko_mitBubensolo);
	void doko_mitDamensoloChanged(bool doko_mitDamensolo);
	void doko_mitFarbsoloChanged(bool doko_mitFarbsolo);
	void doko_mitFleischlossChanged(bool doko_mitFleischloss);
	void doko_mitFuenfKoenigeChanged(bool doko_mitFuenfKoenige);
	void doko_mitNeunzigPunkteChanged(bool doko_mitNeunzigPunkte);
	void doko_mitTrumpfabgabeSchmeissereiChanged(bool doko_mitTrumpfabgabeSchmeisserei);
	void doko_mitTrumpfsoloChanged(bool doko_mitTrumpfsolo);
	void doko_mitZuWenigTrumpfChanged(bool doko_mitZuWenigTrumpf);
	void doko_mitFleischlosChanged(bool doko_mitFleischlos);
	void doko_mitSchwarzsoloChanged(bool doko_mitSchwarzsolo);
};

Q_DECLARE_METATYPE(QList<DoppelkopfLiveGame *>);

#endif // DOPPELKOPFLIVEGAME_H

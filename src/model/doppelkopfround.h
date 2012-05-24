#ifndef DOPPELKOPFROUND_H
#define DOPPELKOPFROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace DoppelkopfRoundProperties {
const QString Doko_soloPflichtAttribute("doko_soloPflicht");
const QString Doko_soloTypeAttribute("doko_soloType");
const QString HochzeitPlayerRelation("hochzeitPlayer");
const QString RePlayer1Relation("rePlayer1");
const QString RePlayer2Relation("rePlayer2");
const QString SchweinereiPlayerRelation("schweinereiPlayer");
const QString TrumpfabgabePlayerRelation("trumpfabgabePlayer");
const QString DokoSoloPlayerRelation("dokoSoloPlayer");
} // namespace DoppelkopfRoundProperties

class Player;

class DoppelkopfRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfRound(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
    static const int EntityTypeId;

	QString displayName() const;

	bool doko_soloPflicht() const;
	QString doko_soloType() const;

	void setDoko_soloPflicht(bool doko_soloPflicht);
	void setDoko_soloType(const QString &doko_soloType);



	Player *hochzeitPlayer() const;
	Player *rePlayer1() const;
	Player *rePlayer2() const;
	Player *schweinereiPlayer() const;
	Player *trumpfabgabePlayer() const;
	Player *dokoSoloPlayer() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void doko_soloPflichtChanged(bool doko_soloPflicht);
	void doko_soloTypeChanged(QString doko_soloType);
};

Q_DECLARE_METATYPE(QList<DoppelkopfRound *>);

#endif // DOPPELKOPFROUND_H

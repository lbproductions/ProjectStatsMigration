#ifndef DOPPELKOPFROUND_H
#define DOPPELKOPFROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace DoppelkopfRoundProperties {
const QString Doko_soloPflichtAttribute("doko_soloPflicht");
const QString Doko_soloTypeAttribute("doko_soloType");
const QString RoundPointsAttribute("roundPoints");
const QString WinnerAttribute("winner");
const QString HochzeitPlayerRelation("hochzeitPlayer");
const QString RePlayer1Relation("rePlayer1");
const QString RePlayer2Relation("rePlayer2");
const QString SchweinereiPlayerRelation("schweinereiPlayer");
const QString TrumpfabgabePlayerRelation("trumpfabgabePlayer");
const QString DokoSoloPlayerRelation("dokoSoloPlayer");
const QString CurrentPlayingPlayersRelation("currentPlayingPlayers");
const QString IsReFunction("isRe");
const QString IsContraFunction("isContra");
} // namespace DoppelkopfRoundProperties

class Player;
class Round;

class DoppelkopfRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfRound(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	enum Winner {
		Re = 1,
		Contra = 2,
		Draw = 3,
		Unknown = 4
	};

	bool doko_soloPflicht() const;
	QString doko_soloType() const;
	int roundPoints() const;
	Winner winner() const;

	void setDoko_soloPflicht(bool doko_soloPflicht);
	void setDoko_soloType(const QString &doko_soloType);
	void setWinner(Winner winner);

	bool isRe(const Player *player) const;
	bool isContra(const Player *player) const;


	Player *hochzeitPlayer() const;
	void setHochzeitPlayer(Player *hochzeitPlayer);
	Player *rePlayer1() const;
	void setRePlayer1(Player *rePlayer1);
	Player *rePlayer2() const;
	void setRePlayer2(Player *rePlayer2);
	Player *schweinereiPlayer() const;
	void setSchweinereiPlayer(Player *schweinereiPlayer);
	Player *trumpfabgabePlayer() const;
	void setTrumpfabgabePlayer(Player *trumpfabgabePlayer);
	Player *dokoSoloPlayer() const;
	void setDokoSoloPlayer(Player *dokoSoloPlayer);
	QList<Player *> currentPlayingPlayers() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void doko_soloPflichtChanged(bool);
	void doko_soloTypeChanged(QString);
	void roundPointsChanged();
	void winnerChanged(DoppelkopfRound::Winner);
	void currentPlayingPlayersChanged();
};

Q_DECLARE_METATYPE(QList<DoppelkopfRound *>)
Q_DECLARE_METATYPE(DoppelkopfRound *)

#endif // DOPPELKOPFROUND_H

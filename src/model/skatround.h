#ifndef SKATROUND_H
#define SKATROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace SkatRoundProperties {
const QString Skat_gameTypeAttribute("skat_gameType");
const QString Skat_trumpfColorAttribute("skat_trumpfColor");
const QString SkatSoloPlayerRelation("skatSoloPlayer");
} // namespace SkatRoundProperties

class Player;

class SkatRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatRound(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	QString skat_gameType() const;
	QString skat_trumpfColor() const;

	void setSkat_gameType(const QString &skat_gameType);
	void setSkat_trumpfColor(const QString &skat_trumpfColor);



	Player *skatSoloPlayer() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void skat_gameTypeChanged(QString);
	void skat_trumpfColorChanged(QString);
};

Q_DECLARE_METATYPE(QList<SkatRound *>)
Q_DECLARE_METATYPE(SkatRound *)

#endif // SKATROUND_H

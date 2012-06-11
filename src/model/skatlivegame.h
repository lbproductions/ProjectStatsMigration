#ifndef SKATLIVEGAME_H
#define SKATLIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "livegame.h"

namespace SkatLiveGameProperties {
const QString Skat_gameEndAttribute("skat_gameEnd");
const QString Skat_maxPointsAttribute("skat_maxPoints");
const QString Skat_maxRoundsAttribute("skat_maxRounds");
const QString Skat_mitRamschenAttribute("skat_mitRamschen");
} // namespace SkatLiveGameProperties


class SkatLiveGame : public LiveGame
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatLiveGame(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	QString skat_gameEnd() const;
	int skat_maxPoints() const;
	int skat_maxRounds() const;
	bool skat_mitRamschen() const;

	void setSkat_gameEnd(const QString &skat_gameEnd);
	void setSkat_maxPoints(int skat_maxPoints);
	void setSkat_maxRounds(int skat_maxRounds);
	void setSkat_mitRamschen(bool skat_mitRamschen);




	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void skat_gameEndChanged(QString skat_gameEnd);
	void skat_maxPointsChanged(int skat_maxPoints);
	void skat_maxRoundsChanged(int skat_maxRounds);
	void skat_mitRamschenChanged(bool skat_mitRamschen);
};

Q_DECLARE_METATYPE(QList<SkatLiveGame *>)

#endif // SKATLIVEGAME_H

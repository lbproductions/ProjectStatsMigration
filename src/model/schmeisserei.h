#ifndef SCHMEISSEREI_H
#define SCHMEISSEREI_H

#include <LBDatabase/LBDatabase.h>


namespace SchmeissereiProperties {
const QString TypeAttribute("type");
const QString PlayerRelation("player");
const QString RoundRelation("round");
} // namespace SchmeissereiProperties

class Player;
class Round;

class Schmeisserei : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Schmeisserei(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;

	QString type() const;

	void setType(const QString &type);



	Player *player() const;
	Round *round() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void typeChanged(QString type);
};

class SchmeissereienContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE SchmeissereienContext(const::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Schmeisserei *schmeisserei(int id) const;
};

#endif // SCHMEISSEREI_H

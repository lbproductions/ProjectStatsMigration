#ifndef SCHMEISSEREIENCONTEXT_H
#define SCHMEISSEREIENCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Schmeisserei;

class SchmeissereienContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE SchmeissereienContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Schmeisserei *schmeisserei(int id) const;
	QList<Schmeisserei *> schmeissereien() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END
};

#endif // SCHMEISSEREIENCONTEXT_H

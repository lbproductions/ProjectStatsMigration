#include "schmeissereiencontext.h"

#include "schmeisserei.h"

const QString SchmeissereienContext::Name("Schmeissereien");
SchmeissereienContext::SchmeissereienContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Schmeisserei>();
}

Schmeisserei *SchmeissereienContext::schmeisserei(int id) const
{
	return static_cast<Schmeisserei *>(entity(id));
}

QList<Schmeisserei*> SchmeissereienContext::schmeissereien() const
{
	QList<Schmeisserei *> schmeissereien;
	foreach(LBDatabase::Entity *entity, entities())
		schmeissereien.append(static_cast<Schmeisserei *>(entity));
	return schmeissereien;
}


	// Write anything you want to remain unchanged between these comments: 
	//START

#include "storage.h"

Schmeisserei *SchmeissereienContext::createSchmeisserei()
{
    Storage *psstorage = static_cast<Storage *>(storage());
    Schmeisserei *s = static_cast<Schmeisserei *>(insertEntity(psstorage->entityType(Schmeisserei::EntityTypeId)));
    return s;
}


	// END

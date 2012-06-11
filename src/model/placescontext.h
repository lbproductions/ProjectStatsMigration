#ifndef PLACESCONTEXT_H
#define PLACESCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Place;

class PlacesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE PlacesContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Place *place(int id) const;
	QList<Place *> places() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END
};

#endif // PLACESCONTEXT_H

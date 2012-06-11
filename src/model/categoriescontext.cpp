#include "categoriescontext.h"

#include "category.h"

const QString CategoriesContext::Name("Categories");
CategoriesContext::CategoriesContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Category>();
}

Category *CategoriesContext::category(int id) const
{
	return static_cast<Category *>(entity(id));
}

QList<Category*> CategoriesContext::categories() const
{
	QList<Category *> categories;
	foreach(LBDatabase::Entity *entity, entities())
		categories.append(static_cast<Category *>(entity));
	return categories;
}


	// Write anything you want to remain unchanged between these comments: 
	//START

void CategoriesContext::test()
{
}

	// END

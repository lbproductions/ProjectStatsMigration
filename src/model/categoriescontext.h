#ifndef CATEGORIESCONTEXT_H
#define CATEGORIESCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Category;

class CategoriesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE CategoriesContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Category *category(int id) const;
	QList<Category *> categories() const;

	// Write anything you want to remain unchanged between these comments: 
	//START

    void test();

	// END
};

#endif // CATEGORIESCONTEXT_H

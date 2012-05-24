#ifndef CATEGORY_H
#define CATEGORY_H

#include <LBDatabase/LBDatabase.h>


namespace CategoryProperties {
const QString ContentTypeAttribute("contentType");
const QString OrderIndicatorAttribute("orderIndicator");
const QString NameAttribute("name");
const QString IconAttribute("icon");
const QString TypeAttribute("type");
const QString ParentCategoryRelation("parentCategory");
const QString ChildCategoriesRelation("childCategories");
} // namespace CategoryProperties

class Category;

class Category : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Category(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;

	enum Type {
		ParentCategoryType = 0,
		ChildCategoryType = 1
	};

	int contentType() const;
	int orderIndicator() const;
	QString name() const;
	QString icon() const;
	Type type() const;

	void setOrderIndicator(int orderIndicator);



	Category *parentCategory() const;
	QList<Category *> childCategories() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
	void orderIndicatorChanged(int orderIndicator);
};

Q_DECLARE_METATYPE(QList<Category *>);

class CategoriesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
    Q_INVOKABLE CategoriesContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Category *category(int id) const;
};

#endif // CATEGORY_H

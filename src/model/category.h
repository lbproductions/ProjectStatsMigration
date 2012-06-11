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
	static const int EntityTypeId;

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
	void setIcon(const QString &icon);



	Category *parentCategory() const;
	QList<Category *> childCategories() const;

	// Write anything you want to remain unchanged between these comments: 
	//START

    void test();

	// END

signals:
	void orderIndicatorChanged(int orderIndicator);
	void iconChanged(QString icon);
};

Q_DECLARE_METATYPE(QList<Category *>)

#endif // CATEGORY_H

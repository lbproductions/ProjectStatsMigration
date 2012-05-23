#include "category.h"

#include "category.h"



const QString CategoriesContext::Name("Categories");
const QString Category::Name("category");

Category::Category(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

int Category::contentType() const
{
	return value(CategoryProperties::ContentTypeAttribute).value<int>();
}

int Category::orderIndicator() const
{
	return value(CategoryProperties::OrderIndicatorAttribute).value<int>();
}

QString Category::name() const
{
	return value(CategoryProperties::NameAttribute).value<QString>();
}

QString Category::icon() const
{
	return value(CategoryProperties::IconAttribute).value<QString>();
}

Category::Type Category::type() const
{
	return static_cast<Type>(value(CategoryProperties::TypeAttribute).value<int>());
}

void Category::setOrderIndicator(int orderIndicator)
{
	if(orderIndicator == this->orderIndicator())
		return;
	setValue(CategoryProperties::OrderIndicatorAttribute,QVariant::fromValue<int>(orderIndicator));
	emit orderIndicatorChanged(orderIndicator);
}

Category *Category::parentCategory() const
{
	return relation<Category>(CategoryProperties::ParentCategoryRelation)->firstEntity();
}

QList<Category *> Category::childCategories() const
{
	return relation<Category>(CategoryProperties::ChildCategoriesRelation)->entities();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Category::displayName() const
{
    return name();
}
	// END

CategoriesContext::CategoriesContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	Context(metaData, parent)
{
	registerEntityClass<Category>();
}

Category *CategoriesContext::category(int id) const
{
	return static_cast<Category *>(entity(id));
}


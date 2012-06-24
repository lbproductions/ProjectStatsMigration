#include "categorycalculator.h"

#include "category.h"
#include "categoriescontext.h"

CategoryCalculator::CategoryCalculator(QObject *parent) :
	LBDatabase::Calculator(parent)
{
}

QVariant CategoryCalculator::entityListTest(const LBDatabase::Entity *entity) const
{
	const Category *category = static_cast<const Category *>(entity);
    QList<LBDatabase::Entity *> list;
    list.append(static_cast<CategoriesContext *>(category->context())->category(2));
    list.append(static_cast<CategoriesContext *>(category->context())->category(3));
    return QVariant::fromValue<QList<LBDatabase::Entity *> >(list);
}

QVariant CategoryCalculator::entityTest(const LBDatabase::Entity *entity) const
{
	const Category *category = static_cast<const Category *>(entity);
    return QVariant::fromValue<LBDatabase::Entity *>(static_cast<CategoriesContext *>(category->context())->category(2));
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

#include "calculator.h"

#include "attributevalue.h"
#include "entity.h"
#include "functionvalue.h"
#include "property.h"
#include "relationvaluebase.h"

#include <QMetaMethod>

#include <QDebug>

namespace LBDatabase {

Calculator::Calculator(QObject *parent) :
    QObject(parent)
{
}

QVariant Calculator::calculate(const Entity *entity, AttributeValue *attributeValue)
{
    QString methodName = attributeValue->property()->identifier() + QLatin1String("(const LBDatabase::Entity*)");

    int methodIndex = metaObject()->indexOfMethod(methodName.toLocal8Bit().data());
    if(methodIndex == -1)
        return QVariant();

    QMetaMethod method = metaObject()->method(methodIndex);
    QVariant result;
    method.invoke(this, Q_RETURN_ARG(QVariant, result), Q_ARG(const ::LBDatabase::Entity*, entity));
    return result;
}

QHash<const Entity *, QVariant> Calculator::calculate(const Entity *entity, FunctionValue *functionValue)
{
    QString methodName = functionValue->property()->identifier() + QLatin1String("(const LBDatabase::Entity*)");

    int methodIndex = metaObject()->indexOfMethod(methodName.toLocal8Bit().data());
    if(methodIndex == -1)
        return QHash<const Entity *, QVariant>();

    QMetaMethod method = metaObject()->method(methodIndex);
    EntityVariantHash result;

    method.invoke(this, Q_RETURN_ARG(EntityVariantHash, result), Q_ARG(const ::LBDatabase::Entity*, entity));
    return result;
}

QList<Entity *> Calculator::calculate(const Entity *entity, const RelationValueBase *relationValue)
{
    QString methodName = relationValue->property()->identifier() + QLatin1String("(const LBDatabase::Entity*)");

    int methodIndex = metaObject()->indexOfMethod(methodName.toLocal8Bit().data());
    if(methodIndex == -1)
        return QList<Entity *>();

    QMetaMethod method = metaObject()->method(methodIndex);
    RelatedEntities result;

    method.invoke(this, Q_RETURN_ARG(RelatedEntities, result), Q_ARG(const ::LBDatabase::Entity*, entity));
    return result;
}

} // namespace LBDatabase

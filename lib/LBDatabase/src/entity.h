#ifndef LBDATABASE_ENTITY_H
#define LBDATABASE_ENTITY_H

#include <QObject>

#include "entitytype.h"

#include <QHash>
#include <QDebug>

namespace LBDatabase {

class Attribute;
class AttributeValue;
class Context;
class EntityMetaData;
class FunctionValue;
class Property;
class PropertyValue;
class Relation;
template<class EntityClass>
class RelationValue;
class RelationValueBase;
class Row;
class Storage;

class EntityPrivate;
class Entity : public QObject
{
    Q_OBJECT
public:
    ~Entity();

    // General
    int id() const;
    virtual QString displayName() const;
    EntityType *entityType() const;
    Storage *storage() const;
    Context *context() const;

    // Property values
    QList<PropertyValue *> propertyValues() const;
    PropertyValue *propertyValue(Property *property) const;
    AttributeValue *attributeValue(const QString &name) const;
    FunctionValue *function(const QString &name) const;
    template<class EntityClass>
    RelationValue<EntityClass> *relation(const QString &name) const;

    void setValue(const QString &name, const QVariant &data);
    QVariant value(const QString &name) const;

protected:
    explicit Entity(const EntityMetaData &metaData, Context *parent);

private:
    friend class AttributePrivate;
    friend class ContextPrivate;
    friend class RelationPrivate;
    friend class Context;
    friend class FunctionPrivate;

    void addAttributeValue(AttributeValue *value);
    void addRelationValue(RelationValueBase *value);
    void addFunctionValue(FunctionValue *value);

    QScopedPointer<EntityPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Entity)
    Q_DISABLE_COPY(Entity)
};

template<class EntityClass>
RelationValue<EntityClass> *Entity::relation(const QString &name) const
{
    return static_cast<LBDatabase::RelationValue<EntityClass> *>(propertyValue(entityType()->property(name)));
}

class EntityMetaData
{
public:
    int id;
    int entityTypeId;
};

} // namespace LBDatabase

Q_DECLARE_METATYPE(QList<LBDatabase::Entity *>)

#endif // LBDATABASE_ENTITY_H

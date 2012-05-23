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
    //! \cond PRIVATE
    static const QString EntityTypeIdColumn;
    //! \endcond

    ~Entity();

    virtual QString displayName() const;

    int id() const;
    EntityType *entityType() const;
    Storage *storage() const;
    Context *context() const;
    QList<PropertyValue *> propertyValues() const;
    PropertyValue *propertyValue(Property *property) const;
    QVariant value(const QString &name) const;
    void setValue(const QString &name, const QVariant &data);

    template<class EntityClass>
    RelationValue<EntityClass> *relation(const QString &name) const
    {
        return static_cast<LBDatabase::RelationValue<EntityClass> *>(propertyValue(entityType()->property(name)));
    }

    FunctionValue *function(const QString &name) const;

protected:
    friend class AttributePrivate;
    friend class ContextPrivate;
    friend class RelationPrivate;
    friend class Context;
    friend class FunctionPrivate;

    explicit Entity(const EntityMetaData &metaData, Context *parent);

    QVariant data(Property *property) const;
    bool setData(const QVariant &data, Property *property);

    void addAttributeValue(AttributeValue *value);
    void addRelationValue(RelationValueBase *value);
    void addFunctionValue(FunctionValue *value);

    QScopedPointer<EntityPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Entity)
    Q_DISABLE_COPY(Entity)
};

class EntityMetaData
{
public:
    int id;
    int entityTypeId;
};

} // namespace LBDatabase

#endif // LBDATABASE_ENTITY_H

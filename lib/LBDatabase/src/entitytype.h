#ifndef LBDATABASE_ENTITYTYPE_H
#define LBDATABASE_ENTITYTYPE_H

#include <QObject>

#include "attribute.h"
#include "relation.h"

namespace LBDatabase {

class Attribute;
class Calculator;
class Context;
class Entity;
class EntityTypeMetaData;
class Function;
class Property;
class Row;
class Storage;

class EntityTypePrivate;
class EntityType : public QObject
{
    Q_OBJECT
public:
    ~EntityType();

    // General
    int id() const;
    QString identifier() const;
    QString displayName() const;
    QString displayNamePlural() const;
    Context *context() const;

    // Inheritance
    EntityType *parentEntityType() const;
    QList<EntityType *> childEntityTypes() const;
    bool inherits(EntityType *entityType) const;

    // Entities
    QList<Entity *> entities() const;

    // Properties
    Property *property(const QString &identifier) const;
    QList<Property *> properties() const;
    QList<Attribute *> attributes() const;
    QList<Relation *> relations() const;
    QList<Function *> functions() const;

    // Used for export
    QList<Property *> nonInhertitedProperties() const;
    QList<Attribute *> nonInhertitedAttributes() const;
    QList<Relation *> nonInhertitedRelations() const;
    QList<Function *> nonInhertitedFunctions() const;

Q_SIGNALS:
    void displayNameChanged(QString);

private:
    friend class FunctionValuePrivate;
    friend class AttributeValuePrivate;
    friend class ContextPrivate;
    friend class StoragePrivate;
    friend class AttributePrivate;
    friend class RelationPrivate;
    friend class EntityPrivate;
    friend class FunctionPrivate;
    friend class TransposeRelationPrivate;

    explicit EntityType(EntityTypeMetaData metaData, Storage *parent);

    int parentEntityTypeId() const;

    void setContext(Context *context);
    void addChildEntityType(EntityType *type);
    void setParentEntityType(EntityType *type);
    void addAttribute(Attribute *attribute);
    void addRelation(Relation *relation);
    void addFunction(Function *function);
    void inheritProperties(EntityType *parent);
    void inheritCalculator(EntityType *parent);
    void addEntity(Entity *entity);

    Calculator *calculator() const;
    void setCalculator(Calculator *calculator);

    QScopedPointer<EntityTypePrivate> d_ptr;
    Q_DECLARE_PRIVATE(EntityType)
    Q_DISABLE_COPY(EntityType)
};

class EntityTypeMetaData {
public:
    int id;
    int parentEntityTypeId;
    int contextId;
    QString identifier;
    QString displayName;
    QString displayNamePlural;
};

} // namespace LBDatabase

#endif // LBDATABASE_ENTITYTYPE_H

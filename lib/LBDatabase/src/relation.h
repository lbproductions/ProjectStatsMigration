#ifndef LBDATABASE_RELATION_H
#define LBDATABASE_RELATION_H

#include "property.h"

namespace LBDatabase {

class Context;
class EntityType;
class RelationMetaData;
class RelationValueBase;
class Row;
class Storage;
class Table;

class RelationPrivate;
class Relation : public Property
{
    Q_OBJECT
public:
    enum Cardinality {
        OneToOne,
        OneToMany,
        ManyToMany
    };

    enum Direction {
        LeftToRight,
        Both
    };

    ~Relation();

    // Property implementation
    int id() const;
    QString displayName() const;
    QString identifier() const;
    Property::Type propertyType() const;
    bool isEditable() const;
    bool isCalculated() const;

    // Genereal
    EntityType *entityType() const;
    EntityType *entityTypeOther() const;
    Cardinality cardinality() const;
    Direction direction() const;

    bool isTranspose() const;
    Relation *transposeRelation() const;

    Storage* storage() const;

    // Used by drivers
    QString tableName() const;
    QString leftEntityIdColumnName() const;
    QString rightEntityIdColumnName() const;

    // Used for export
    QList<EntityType *> reimplementingEntityTypes() const;

protected:
    friend class StoragePrivate;
    friend class RelationValueRightPrivate;
    friend class EntityTypePrivate;
    friend class TransposeRelation;
    friend class EntityType;

    explicit Relation(const RelationMetaData &metaData, Storage *parent);
    explicit Relation(RelationPrivate &dd, const RelationMetaData &metaData, Storage *parent);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void addReimplementingEntityType(EntityType *type);
    void fetchValues();
    void calculateValues();

    QScopedPointer<RelationPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Relation)
    Q_DISABLE_COPY(Relation)
};

class RelationMetaData {
public:
    int id;
    QString identifier;
    QString identifierRight;
    QString tableName;
    QString leftEntityIdColumnName;
    QString rightEntityIdColumnName;
    QString displayName;
    QString displayNameRight;
    Relation::Cardinality cardinality;
    Relation::Direction direction;
    int entityTypeId;
    int entityTypeOtherId;
    bool editable;
    bool calculated;
};

class RelationReimplementationMetaData
{
public:
    int reimplementedRelationId;
    int reimplementingEntityTypeId;
};

class TransposeRelation : public Relation
{
    Q_OBJECT
public:
    ~TransposeRelation();

private:
    friend class Relation;

    TransposeRelation(Relation *relation);

    Q_DECLARE_PRIVATE(Relation)
};

} // namespace LBDatabase

#endif // LBDATABASE_RELATION_H

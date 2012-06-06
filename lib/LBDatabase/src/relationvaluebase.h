#ifndef LBDATABASE_RELATIONVALUEBASE_H
#define LBDATABASE_RELATIONVALUEBASE_H

#include "propertyvalue.h"

namespace LBDatabase {

class Relation;
class Entity;

class RelationValueBasePrivate;
class RelationValueBase : public PropertyValue
{
    Q_OBJECT
public:
    ~RelationValueBase();

    // Partial PropertyValue implementation (the rest is in RelationValue)
    Property *property() const;
    Entity *entity() const;

    // General
    Relation *relation() const;

protected:
    friend class RelationPrivate;

    explicit RelationValueBase(Relation *relation, Entity *parent);

    virtual void addOtherEntity(Entity *entity, int rowId) = 0;

    QScopedPointer<RelationValueBasePrivate> d_ptr;
    Q_DECLARE_PRIVATE(RelationValueBase)
    Q_DISABLE_COPY(RelationValueBase)
};

} // namespace LBDatabase

#endif // LBDATABASE_RELATIONVALUEBASE_H

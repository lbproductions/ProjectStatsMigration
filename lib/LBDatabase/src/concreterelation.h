#ifndef LBDATABASE_CONCRETERELATION_H
#define LBDATABASE_CONCRETERELATION_H

#include "relation.h"

#include "entity.h"
#include "entitytype.h"
#include "relationvalue.h"

namespace LBDatabase {

template<class EntityClassLeft, class EntityClassRight>
class ConcreteRelation : public Relation
{
protected:
    friend class StoragePrivate;
    friend class RelationValueRightPrivate;
    friend class EntityTypePrivate;

    explicit ConcreteRelation(Row *row, Storage *parent) :
        Relation(row, parent)
    {
    }

    virtual RelationValueBase *createLeftValue(Entity *entity);
    virtual RelationValueBase *createRightValue(Entity *entity);
};

template<class EntityClassLeft, class EntityClassRight>
RelationValueBase *ConcreteRelation<EntityClassLeft, EntityClassRight>::createLeftValue(Entity *entity)
{
    return new RelationValue<EntityClassRight>(this, entity);
}

template<class EntityClassLeft, class EntityClassRight>
RelationValueBase *ConcreteRelation<EntityClassLeft, EntityClassRight>::createRightValue(Entity *entity)
{
    return new RelationValue<EntityClassLeft>(this, entity);
}

} // namespace LBDatabase

#endif // LBDATABASE_CONCRETERELATION_H

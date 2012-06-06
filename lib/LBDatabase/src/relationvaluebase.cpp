#include "relationvaluebase.h"
#include "relationvaluebase_p.h"

#include "calculator.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "relation.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** RelationValuePrivate
*/

/******************************************************************************
** RelationValue
*/
/*!
  \class RelationValue
  \brief The RelationValue class represents a value of a relation between two
  EntityTypes.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var RelationValue::d_ptr
  \internal
  */

/*!
  Creates a RelationValue.
  */
RelationValueBase::RelationValueBase(Relation *relation, Entity *parent) :
    PropertyValue(parent),
    d_ptr(new RelationValueBasePrivate)
{
    Q_D(RelationValueBase);
    d->q_ptr = this;
    d->relation = relation;
    d->entity = parent;
    connect(this, SIGNAL(changed()), entity()->context(), SLOT(onPropertyValueChanged()));
}

/*!
  Destroys the relation value.
  */
RelationValueBase::~RelationValueBase()
{
}

/*!
  Returns the entity of this relation value.
  */
Entity *RelationValueBase::entity() const
{
    Q_D(const RelationValueBase);
    return d->entity;
}

QList<Entity *> RelationValueBase::calculate() const
{
    Calculator *calculator = entity()->entityType()->calculator();
    if(!calculator)
        return QList<Entity *>();

    return calculator->calculate(entity(),this);
}

/*!
  Returns the relation, that describes this value.
  */
Property *RelationValueBase::property() const
{
    Q_D(const RelationValueBase);
    return d->relation;
}

Relation *RelationValueBase::relation() const
{
    Q_D(const RelationValueBase);
    return d->relation;
}

} // namespace LBDatabase

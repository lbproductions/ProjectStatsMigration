#include "relationvalue.h"
#include "relationvalue_p.h"

#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "relation.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** RelationValuePrivate
*/

//! \cond PRIVATE
void RelationValueBasePrivate::init()
{
}

void RelationValueBasePrivate::fetchValue()
{
}

//! \endcond

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
    d->init();
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

/*!
  Returns false
  */
bool RelationValueBase::isEditable() const
{
    Q_D(const RelationValueBase);
    return d->relation->isEditable();
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

/*!
  Initializes the content of the relation value.
  */
void RelationValueBase::fetchValue()
{
    Q_D(RelationValueBase);
    d->fetchValue();
}

QVariant RelationValueBase::calculate()
{
    return QVariant();
}

} // namespace LBDatabase

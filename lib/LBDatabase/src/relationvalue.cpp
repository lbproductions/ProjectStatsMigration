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
    Q_Q(RelationValueBase);
    QObject::connect(q, SIGNAL(dataChanged(QVariant)), entity->context(), SLOT(onPropertyValueDataChanged(QVariant)));
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
  Does nothing.
  */
bool RelationValueBase::setData(const QVariant &data)
{
    Q_UNUSED(data);
    return false;
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

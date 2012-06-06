#ifndef LBDATABASE_RELATIONVALUEBASE_P_H
#define LBDATABASE_RELATIONVALUEBASE_P_H

#include <QObject>

#include <QHash>

namespace LBDatabase {

class Entity;
class FunctionValue;
class Relation;
class RelationValueBase;

//! \cond PRIVATE
class RelationValueBasePrivate {
protected:
    friend class RelationPrivate;

    RelationValueBasePrivate() {}

    Entity *entity;
    Relation *relation;

    RelationValueBase * q_ptr;
    Q_DECLARE_PUBLIC(RelationValueBase)
};
//! \endcond

} // namespace LBDatabase

#endif // LBDATABASE_RELATIONVALUEBASE_P_H

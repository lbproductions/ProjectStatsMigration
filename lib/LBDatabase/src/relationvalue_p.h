#ifndef LBDATABASE_RELATIONVALUE_P_H
#define LBDATABASE_RELATIONVALUE_P_H

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

    void init();
    void fetchValue();

    Entity *entity;
    Relation *relation;

    RelationValueBase * q_ptr;
    Q_DECLARE_PUBLIC(RelationValueBase)
};
//! \endcond

} // namespace LBDatabase

#endif // LBDATABASE_RELATIONVALUE_P_H

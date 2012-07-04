#ifndef LBDATABASE_STORAGE_H
#define LBDATABASE_STORAGE_H

#include <QObject>

#include <QMetaType>

#include "attribute.h"
#include "context.h"
#include "entitytype.h"
#include "function.h"
#include "relation.h"
#include "storagedriver.h"

namespace LBDatabase {


class StoragePrivate;
class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);
    ~Storage();
    bool open();

    StorageDriver *driver() const;
    void setDriver(StorageDriver *driver);

    QString name() const;

    Context *context(const QString name) const;
    QList<Context *> contexts() const;

    EntityType *entityType(int id) const;
    QList<EntityType *> entityTypes() const;

    Property *property(Property::Type type, int id) const;

    QList<Attribute *> attributes() const;
    QList<Function *> functions() const;
    QList<Relation *> relations() const;

protected:

    template<class ContextClass>
    void registerContextType();

    Context *context(int id) const;
    Attribute *attribute(int id) const;

private:
    friend class EntityType;
    friend class EntityTypePrivate;
    friend class ContextPrivate;
    friend class EntityPrivate;
    friend class AttributePrivate;
    friend class RelationPrivate;
    friend class FunctionPrivate;
    friend class GraphvizExporter;
    friend class TransposeRelationPrivate;

    void insertEntityType(EntityType *type);
    void insertAttribute(Attribute *attribute);
    void removeAttribute(Attribute *attribute);
    void insertRelation(Relation *relation);
    void insertFunction(Function *function);

    void registerContextType(const QString &contextName, QMetaObject metaObject);

    QScopedPointer<StoragePrivate> d_ptr;
    Q_DECLARE_PRIVATE(Storage)
    Q_DISABLE_COPY(Storage)
};

template<class ContextClass>
void Storage::registerContextType()
{
    registerContextType(ContextClass::Name, ContextClass::staticMetaObject);
}

} // namespace LBDatabase

Q_DECLARE_METATYPE(LBDatabase::Storage*)
Q_DECLARE_METATYPE(LBDatabase::Attribute*)
Q_DECLARE_METATYPE(LBDatabase::Relation*)
Q_DECLARE_METATYPE(LBDatabase::Function*)
Q_DECLARE_METATYPE(LBDatabase::Property*)

#endif // LBDATABASE_STORAGE_H

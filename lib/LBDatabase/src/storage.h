#ifndef LBDATABASE_STORAGE_H
#define LBDATABASE_STORAGE_H

#include <QObject>

#include <QMetaType>

namespace LBDatabase {

class Attribute;
class Context;
class EntityType;
class Function;
class Relation;
class StorageDriver;

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

protected:

    template<class ContextClass>
    void registerContextType();

    Context *context(int id) const;
    Attribute *attribute(int id) const;

private:
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
    void insertRelation(Relation *relation);
    void insertFunction(Function *function);

    QList<Relation *> relations() const;

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

#endif // LBDATABASE_STORAGE_H

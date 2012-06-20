#ifndef LBDATABASE_CONTEXT_H
#define LBDATABASE_CONTEXT_H

#include <QAbstractTableModel>

#include <QMetaType>

namespace LBDatabase {

class Attribute;
class ContextMetaData;
class Entity;
class EntityType;
class Function;
class Relation;
class Storage;

class ContextPrivate;
class Context : public QAbstractTableModel
{
    Q_OBJECT
public:
    ~Context();

    // General
    int id() const;
    QString identifier() const;
    QString displayName() const;
    QString tableName() const;
    Storage *storage() const;

    // EntityTypes
    EntityType *baseEntityType() const;
    QList<EntityType *> entityTypes() const;

    // Entities
    Entity *entity(int id) const;
    QList<Entity *> entities() const;
    Entity *insertEntity(EntityType *type);

    // QAbstractTableModel
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;


Q_SIGNALS:
    void entityInserted(Entity*);

private Q_SLOTS:
    void onEntityTypeNameChanged(QString identifier);
    void onPropertyDisplayNameChanged(QString displayName);
    void onPropertyValueChanged();

protected:
    friend class StoragePrivate;
    friend class EntityType;
    friend class EntityTypePrivate;
    friend class AttributePrivate;
    friend class RelationPrivate;
    friend class FunctionPrivate;
    friend class TransposeRelationPrivate;

    explicit Context(const ContextMetaData &metaData, Storage *parent);

    template<class EntityClass>
    void registerEntityClass();

    template<class EntityClass, class CalculatorClass>
    void registerCalculatorClass();

private:
    void createBaseEntityType(const QString &identifier);
    void addEntityType(EntityType *type);
    void addAttribute(Attribute *attribute);
    void removeAttribute(Attribute *attribute);
    void addFunction(Function *function);
    void addRelation(Relation *relation);

    void initializeEntityHierarchy();
    void loadEntities();

    void registerEntityClass(const QString &entityTypeName, QMetaObject metaObject);
    void registerCalculatorClass(const QString &entityTypeName, QMetaObject metaObject);

    QScopedPointer<ContextPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Context)
    Q_DISABLE_COPY(Context)
};

class ContextMetaData
{
public:
    int id;
    QString identifier;
    QString displayName;
    QString tableName;
};


template<class EntityClass>
void Context::registerEntityClass()
{
    registerEntityClass(EntityClass::Name, EntityClass::staticMetaObject);
}

template<class EntityClass, class CalculatorClass>
void Context::registerCalculatorClass()
{
    registerCalculatorClass(EntityClass::Name, CalculatorClass::staticMetaObject);
}

} // namespace LBDatabase

Q_DECLARE_METATYPE(LBDatabase::ContextMetaData)
Q_DECLARE_METATYPE(LBDatabase::Context*)

#endif // LBDATABASE_CONTEXT_H

#ifndef LBDATABASE_PROPERTY_H
#define LBDATABASE_PROPERTY_H

#include <QObject>

namespace LBDatabase {

class Context;
class Entity;
class EntityType;
class PropertyValue;

//! \cond PRIVATE
class Property : public QObject
{
    Q_OBJECT
public:
    explicit Property(QObject *parent = 0);

    enum Type {
        Attribute,
        EnumAttribute,
        Relation,
        Function
    };

    virtual int id() const = 0;
    virtual QString identifier() const = 0;
    virtual QString displayName() const = 0;
    virtual Type propertyType() const = 0;
    virtual bool isEditable() const = 0;
    virtual bool isCalculated() const = 0;
    virtual EntityType *entityType() const = 0;
    virtual QList<PropertyValue *> propertyValues() const = 0;

Q_SIGNALS:
    void displayNameChanged(QString);

private:
    friend class StoragePrivate;
    friend class ContextPrivate;

    virtual void addPropertyValueToEntities() = 0;
    virtual void addPropertyValue(Entity *entity) = 0;

    virtual void fetchValues() = 0;
};
//! \endcond

class DependencyMetaData {
public:
    int id;
    int dependendPropertyId;
    int dependencyPropertyId;
    Property::Type dependendPropertyType;
    Property::Type dependencyPropertyType;
    int entityRelation; //-1 for self, 0 for all, >0 for a relation
};

} // namespace LBDatabase

#endif // LBDATABASE_PROPERTY_H

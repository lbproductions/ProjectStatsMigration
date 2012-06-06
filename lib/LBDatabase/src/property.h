#ifndef LBDATABASE_PROPERTY_H
#define LBDATABASE_PROPERTY_H

#include <QObject>

namespace LBDatabase {

class Context;
class Entity;


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

} // namespace LBDatabase

#endif // LBDATABASE_PROPERTY_H

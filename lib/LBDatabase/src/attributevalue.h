#ifndef LBDATABASE_ATTRIBUTEVALUE_H
#define LBDATABASE_ATTRIBUTEVALUE_H

#include "propertyvalue.h"

namespace LBDatabase {

class Attribute;
class Entity;

class AttributeValuePrivate;
class AttributeValue : public PropertyValue
{
    Q_OBJECT
public:
    ~AttributeValue();

    // PropertyValue implementation
    Entity *entity() const;
    Property *property() const;
    bool isEditable() const;


    Attribute *attribute() const;
    QVariant data(int role = Qt::DisplayRole) const;
    bool setData(const QVariant &data);

Q_SIGNALS:
    void dataChanged(QVariant data);

private:
    friend class AttributePrivate;
    friend class LocalStorageDriver;

    explicit AttributeValue(Attribute *attribute, Entity *parent);

    QVariant calculate();

    QScopedPointer<AttributeValuePrivate> d_ptr;
    Q_DECLARE_PRIVATE(AttributeValue)
    Q_DISABLE_COPY(AttributeValue)
};

} // namespace LBDatabase

#endif // LBDATABASE_ATTRIBUTEVALUE_H

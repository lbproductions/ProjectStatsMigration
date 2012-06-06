#ifndef LBDATABASE_FUNCTIONVALUE_H
#define LBDATABASE_FUNCTIONVALUE_H

#include "propertyvalue.h"

namespace LBDatabase {

class Function;
class FunctionValueData;
class Row;

class FunctionValuePrivate;
class FunctionValue : public PropertyValue
{
    Q_OBJECT
public:
    ~FunctionValue();

    // PropertyValue implementation
    Entity *entity() const;
    Property *property() const;
    QVariant data(int role = Qt::DisplayRole) const;
    bool isEditable() const;

    // General
    Function *function() const;
    QHash<const Entity *, QVariant> values() const;
    QVariant value(const Entity *entity) const;
    void setValue(const Entity *key, const QVariant &value);

Q_SIGNALS:
    void valueChanged(const Entity *key, QVariant value);

private:
    friend class FunctionPrivate;

    explicit FunctionValue(Function *function, Entity *parent);

    void addValue(Entity *key, const FunctionValueData &data);

    QScopedPointer<FunctionValuePrivate> d_ptr;
    Q_DECLARE_PRIVATE(FunctionValue)
    Q_DISABLE_COPY(FunctionValue)
};

class FunctionValueData
{
public:
    int rowId;
    int entityId;
    int keyEntityId;
    QVariant value;
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTIONVALUE_H

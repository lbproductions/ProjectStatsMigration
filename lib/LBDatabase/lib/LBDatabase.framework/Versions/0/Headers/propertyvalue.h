#ifndef LBDATABASE_PROPERTYVALUE_H
#define LBDATABASE_PROPERTYVALUE_H

#include <QObject>

#include <QVariant>

namespace LBDatabase {

class Entity;
class Property;

//! \cond PRIVATE
class PropertyValue : public QObject
{
    Q_OBJECT
public:
    enum DataRole {
        PlainDataRole = Qt::UserRole + 1
    };

    explicit PropertyValue(QObject *parent = 0);
    virtual ~PropertyValue();

    virtual Entity *entity() const = 0;
    virtual Property *property() const = 0;
    virtual QVariant dataForModel(int role = Qt::DisplayRole) const = 0;
    virtual QVariant value() const = 0;

Q_SIGNALS:
    void changed();

public Q_SLOTS:
    virtual void recalculateAfterDependencyChange() = 0;
};
//! \endcond

} // namespace LBDatabase

#endif // LBDATABASE_PROPERTYVALUE_H

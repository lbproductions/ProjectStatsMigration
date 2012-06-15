#ifndef ATTRIBUTE_P_H
#define ATTRIBUTE_P_H

#include "attribute.h"

namespace LBDatabase {

class AttributePrivate {
protected:
    AttributePrivate() {}

    void init();
    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    AttributeMetaData metaData;

    Storage *storage;
    EntityType *entityType;
    QList<PropertyValue *> propertyValues;

    Attribute * q_ptr;
    Q_DECLARE_PUBLIC(Attribute)
};

} // namespace LBDatabase

#endif // ATTRIBUTE_P_H

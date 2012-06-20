#include "property.h"

#include "context.h"
#include "entity.h"
#include "storage.h"
#include "propertyvalue.h"
#include "relation.h"
#include "relationvalue.h"

namespace LBDatabase {

//! \cond PRIVATE
Property::Property(QObject *parent) :
    QObject(parent)
{
}

QList<DependencyMetaData> Property::dependencies() const
{
    return m_dependencies;
}

void Property::addDependency(const DependencyMetaData &metaData)
{
    m_dependencies.append(metaData);
}

void Property::initDependenciesForAllEntities()
{
    foreach(Entity *e, entityType()->entities()) {
        initDependencies(e);
    }
}

void Property::initDependencies(Entity *entity)
{
    foreach(DependencyMetaData metaData, m_dependencies) {
        PropertyValue *dependendProperty = entity->propertyValue(this);
        Property *dependency = entityType()->context()->storage()->property(metaData.dependencyPropertyType, metaData.dependencyPropertyId);

        if(metaData.dependencyPropertyType == Property::Relation &&
           !entity->propertyValue(dependency)) {
            dependency = static_cast<LBDatabase::Relation *>(dependency)->transposeRelation();
        }

        if(metaData.entityRelation == -1) {
            PropertyValue *dependencyProperty = entity->propertyValue(dependency);

            //qDebug() << "Connecting" << entity->displayName() << dependency->identifier() << dependencyProperty << "to" << entity->displayName() << this->identifier() << dependendProperty;
            QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
        }
        else if(metaData.entityRelation == 0) {
            QObject::connect(dependency->entityType()->context(), SIGNAL(entityInserted(Entity*)), this, SLOT(updateDependenciesWithInsertedEntity(Entity*)));
            foreach(PropertyValue *dependencyProperty, dependency->propertyValues()) {
                QObject::connect(dependencyProperty, SIGNAL(changed()), this, SLOT(recalculateAfterDependencyChange()));
            }
        }
        else if(metaData.entityRelation > 0) {
            Property *relation = entityType()->context()->storage()->property(Property::Relation, metaData.entityRelation);

            RelationValue<Entity> *relationValue = entity->relation<Entity>(relation->identifier());
            QObject::connect(relationValue, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
            QObject::connect(relationValue, SIGNAL(entityAdded(Entity*)), this, SLOT(updateDependenciesWithInsertedEntity(Entity*)));

            foreach(Entity *relatedEntity, relationValue->entities()) {
                PropertyValue *dependencyProperty = relatedEntity->propertyValue(dependency);
                QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
            }
        }
    }
}

void Property::updateDependenciesWithInsertedEntity(Entity *newDependencyEntity)
{
    foreach(Entity *e, entityType()->entities()) {
        PropertyValue *dependendProperty = e->propertyValue(this);

        foreach(DependencyMetaData metaData, m_dependencies) {
            Property *dependency = entityType()->context()->storage()->property(metaData.dependencyPropertyType, metaData.dependencyPropertyId);
            PropertyValue *dependencyProperty = newDependencyEntity->propertyValue(dependency);

            if(dependencyProperty) {

                if(metaData.entityRelation == 0) {
                    qDebug() << "Connecting" << newDependencyEntity->displayName() << dependency->identifier() << "to" << e->displayName() << this->identifier();
                    QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
                }
                else {
                    Property *relation = entityType()->context()->storage()->property(Property::Relation, metaData.entityRelation);

                    RelationValue<Entity> *relationValue = e->relation<Entity>(relation->identifier());
                    if(relationValue && relationValue->entities().contains(newDependencyEntity)) {
                        qDebug() << "Connecting" << newDependencyEntity->displayName() << dependency->identifier() << "to" << e->displayName() << this->identifier();
                        QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
                    }
                }
            }
        }
    }
}

//! \endcond

} // namespace LBDatabase

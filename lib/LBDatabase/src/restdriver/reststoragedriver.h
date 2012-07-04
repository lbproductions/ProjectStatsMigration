#ifndef LBDATABASE_RESTSTORAGEDRIVER_H
#define LBDATABASE_RESTSTORAGEDRIVER_H

#include "../storagedriver.h"

#include <QNetworkReply>

namespace LBDatabase {

class RestStorageDriver : public StorageDriver
{
    Q_OBJECT
public:
    RestStorageDriver(const QUrl &server, QObject *parent = 0);
    ~RestStorageDriver();

    bool init();

    // MetaData
    QList<ContextMetaData> contexts() const;
    QList<EntityTypeMetaData> entityTypes() const;
    QList<AttributeMetaData> attributes() const;
    QList<FunctionMetaData> functions() const;
    QList<RelationMetaData> relations() const;

    QList<EnumAttributeMetaData> enumValues() const;
    QList<FunctionReimplementationMetaData> functionReimplementations() const;
    QList<RelationReimplementationMetaData> relationReimplementations() const;
    QList<DependencyMetaData> dependencies() const;

    void addDependency(DependencyMetaData &metaData);

    // Attributes
    QVariant attributeValue(const AttributeValue *value) const;
    void setAttributeValue(const AttributeValue *value, const QVariant &data);

    void addAttribute(EntityType *entityType, AttributeMetaData &metaData);
    void removeAttribute(int attributeId);

    void setAttributeDisplayName(int id, const QString &displayName);
    void setAttributeIdentifier(int id, const QString &identifier);
    void setAttributeType(int id, Attribute::Type type);
    void setAttributeEditable(int id, bool editable);
    void setAttributeCalculated(int id, bool calculated);
    void setAttributeCached(int id, bool cached);
    void setAttributeDefaultValue(int id, QVariant defaultValue);

    // Relations
    QList<RelationValueData> relatedEntities(Relation *relation) const;
    int addRelatedEntity(RelationValueBase *value, const RelationValueData &data);

    void addRelation(EntityType *entityType, RelationMetaData &metaData);

    void setRelationIdentifier(int id, const QString &identifier);
    void setRelationIdentifierRight(int id, const QString &identifierRight);
    void setRelationDisplayName(int id, const QString &displayName);
    void setRelationDisplayNameRight(int id, const QString &displayNameRight);
    void setRelationCardinality(int id, Relation::Cardinality cardinality);
    void setRelationDirection(int id, Relation::Direction direction);
    void setRelationEntityTypeRight(int id, EntityType *entityType);
    void setRelationEditable(int id, bool editable);
    void setRelationCalculated(int id, bool calculated);

    // Functions
    QList<FunctionValueData> functionValues(Function *function) const;
    void setFunctionValue(FunctionValue *value, const FunctionValueData &data);

    void addFunction(EntityType *entityType, FunctionMetaData &metaData);

    void setFunctionDisplayName(int id, const QString &displayName);
    void setFunctionIdentifier(int id, const QString &identifier);
    void setFunctionType(int id, Attribute::Type type);
    void setFunctionEditable(int id, bool editable);
    void setFunctionKeyEntityType(int id, EntityType *entityType);

    // Entities
    QList<EntityMetaData> entities(Context *context) const;
    EntityMetaData createEntity(EntityType *type);

    int totalRequests() const;
    int requestsDone() const;

signals:
    void metaDataReady();
    void networkError(QNetworkReply::NetworkError);
    void finished();
    void progress(int);

private slots:
    void metaDataReplyFinished();
    void contextContentsReplyFinished();
    void entityReplyFinished();

private:
    bool m_initialized;
    QNetworkAccessManager *m_nam;

    QUrl m_serverUrl;

    int m_totalRequests;
    int m_requestsDone;

    QVariantMap m_metaData;
    QHash<QString, QHash<int, QVariantMap> > m_entities;
};

} // namespace LBDatabase

#endif // LBDATABASE_RESTSTORAGEDRIVER_H

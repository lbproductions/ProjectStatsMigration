#ifndef LBDATABASE_JSONEXPORTER_H
#define LBDATABASE_JSONEXPORTER_H

class QString;
template<class K, class T>
class QHash;
class QVariant;
typedef QHash<QString, QVariant> QVariantHash;

namespace LBDatabase {

class Context;
class Entity;
class Storage;
template<class EntityClass>
class RelationValue;

class JsonExporter
{
public:
    JsonExporter();

    static QString metaDataToJson(Storage *storage);
    static QString entityToJson(Entity *entity);
    static QString contextToJson(Context *context);
    static QVariantHash relationValueToJson(RelationValue<Entity> *value);
};

} // namespace LBDatabase

#endif // LBDATABASE_JSONEXPORTER_H

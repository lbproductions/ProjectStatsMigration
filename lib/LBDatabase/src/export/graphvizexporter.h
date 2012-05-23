#ifndef GRAPHVIZEXPORTER_H
#define GRAPHVIZEXPORTER_H

#include <QObject>

namespace LBDatabase {

class Attribute;
class EntityType;
class Function;
class Relation;
class Storage;

class GraphvizExporter : public QObject
{
    Q_OBJECT
public:
    explicit GraphvizExporter(QObject *parent = 0);

    void setStorage(Storage *storage);

    void exportGraph(const QString &fileName) const;

private:
    Storage *m_storage;

    void startDocument(QString &doc) const;
    void endDocument(QString &doc) const;

    void addEntityType(EntityType *type, QString &doc) const;
    void addAttribute(Attribute *attribute, QString &doc) const;
    void addFunction(Function *function, QString &doc) const;

    void startInheritance(QString &doc) const;
    void addInheritances(EntityType *base, QString &doc) const;

    void startRelations(QString &doc) const;
    void addRelation(Relation *relation, QString &doc) const;


    QString simplifyName(const QString &name) const;
};

} // namespace LBDatabase

#endif // GRAPHVIZEXPORTER_H

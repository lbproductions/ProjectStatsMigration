#include "graphvizexporter.h"

#include <LBDatabase/LBDatabase.h>

#include <QFile>
#include <QTextStream>

#include <QDebug>

namespace LBDatabase {

GraphvizExporter::GraphvizExporter(QObject *parent) :
    QObject(parent),
    m_storage(0)
{
}

void GraphvizExporter::setStorage(Storage *storage)
{
    m_storage = storage;
}

void GraphvizExporter::exportGraph(const QString &fileName) const
{
    if(!m_storage)
        return;

    QString doc;

    startDocument(doc);

    foreach(EntityType *type, m_storage->entityTypes()) {
        addEntityType(type, doc);
    }

    startInheritance(doc);

    foreach(Context *context, m_storage->contexts()) {
        addInheritances(context->baseEntityType(), doc);
    }

    startRelations(doc);

    foreach(Relation *relation, m_storage->relations()) {
        addRelation(relation, doc);
    }

    endDocument(doc);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << doc;
    file.close();

    qDebug() << doc;
}

void GraphvizExporter::startDocument(QString &doc) const
{
    doc.append(QLatin1String("digraph G {\n"
                    "\tfontname = \"Bitstream Vera Sans\"\n"
                    "\tfontsize = 8\n"
               "node [\n"
                    "\tfontname = \"Bitstream Vera Sans\"\n"
                     "\tfontsize = 8\n"
                       "\tshape = \"record\"\n"
                "]\n"
               "edge [\n"
                       "\tfontname = \"Bitstream Vera Sans\"\n"
                       "\tfontsize = 8\n"
               "]\n"));
}

void GraphvizExporter::endDocument(QString &doc) const
{
    doc.append(QLatin1String("}\n"));
}

void GraphvizExporter::addEntityType(EntityType *type, QString &doc) const
{
    doc.append(simplifyName(type->identifier()));
    doc.append(QLatin1String(" [\n"
                             "\tlabel = \"{"));
    doc.append(simplifyName(type->identifier()));

    doc.append(QLatin1String("|"));
    QList<Attribute *> attributes = type->attributes();
    if(type->parentEntityType()) {
        foreach(Attribute *attribute, type->parentEntityType()->attributes()) {
            attributes.removeAll(attribute);
        }
    }

    foreach(Attribute *attribute, attributes) {
        addAttribute(attribute, doc);
    }
    doc.append(QLatin1String("|"));
    QList<Function *> functions = type->functions();
    if(type->parentEntityType()) {
        foreach(Function *function, type->parentEntityType()->functions()) {
            functions.removeAll(function);
        }
    }
    foreach(Function *function, functions) {
        addFunction(function, doc);
    }
    doc.append(QLatin1String("}\"\n"
                             "]\n"));
}

void GraphvizExporter::addAttribute(Attribute *attribute, QString &doc) const
{
    doc.append(QLatin1String("+ "));
    doc.append(attribute->identifier());
    doc.append(QLatin1String(" : QVariant"));
//    doc.append(attribute->typeName());
    doc.append(QLatin1String("\\l"));
}

void GraphvizExporter::addFunction(Function *function, QString &doc) const
{
    doc.append(QLatin1String("+ "));
    doc.append(function->identifier());
    doc.append(QLatin1String("("));
    EntityType *type = function->keyEntityType();
    doc.append(simplifyName(type->identifier()));
    doc.append(QLatin1String(" *) : QVariant"));
//    doc.append(attribute->typeName());
    doc.append(QLatin1String("\\l"));
}

void GraphvizExporter::startInheritance(QString &doc) const
{
    doc.append(QLatin1String("edge [\n"
                                "\tconstraint=false\n"
                                "\tarrowhead = \"empty\"\n"
                             "]\n"));
}

void GraphvizExporter::addInheritances(EntityType *base, QString &doc) const
{
    foreach(EntityType *derived, base->childEntityTypes()) {
        doc.append(simplifyName(derived->identifier()) + QLatin1String(" -> ") + simplifyName(base->identifier()) + QLatin1String("\n"));
        addInheritances(derived, doc);
    }
}

void GraphvizExporter::startRelations(QString &doc) const
{
    doc.append(QLatin1String("edge [\n"
                             "\tarrowhead = \"none\"\n"
                             "\tconstraint=false\n"
                             "]\n"));
}

void GraphvizExporter::addRelation(Relation *relation, QString &doc) const
{
    doc.append(simplifyName(relation->entityType()->identifier()) + QLatin1String(" -> ") + simplifyName(relation->entityTypeOther()->identifier()));

    doc.append(QLatin1String("\t[ label = \""));
    doc.append(relation->identifier());
    doc.append(QLatin1String("\""));
    if(relation->cardinality() == Relation::OneToOne) {
        doc.append(QLatin1String(" taillabel = \"1\""));
        doc.append(QLatin1String(" headlabel = \"1\""));
    }
    else if(relation->cardinality() == Relation::OneToMany) {
        doc.append(QLatin1String(" taillabel = \"1\""));
        doc.append(QLatin1String(" headlabel = \"0..*\""));
    }
    else if(relation->cardinality() == Relation::ManyToMany) {
        doc.append(QLatin1String(" taillabel = \"0..*\""));
        doc.append(QLatin1String(" headlabel = \"0..*\""));
    }
    doc.append(QLatin1String(" ]\n"));
}

QString GraphvizExporter::simplifyName(const QString &name) const
{
    return name.simplified().remove(' ');
}

} // namespace LBDatabase

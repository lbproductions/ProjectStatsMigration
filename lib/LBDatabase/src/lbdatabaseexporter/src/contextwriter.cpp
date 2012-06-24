#include "contextwriter.h"

#include "calculatorwriter.h"
#include "entitytypewriter.h"

#include <LBDatabase/context.h>
#include <LBDatabase/entitytype.h>

#include <QDebug>

namespace LBDatabase {

ContextWriter::ContextWriter(const CppExporter *exporter) :
    Writer(exporter),
    m_context(0)
{
}

void ContextWriter::setContext(Context *context)
{
    m_context = context;
    m_classname = makeClassname(m_context->identifier()+"Context");
}

void ContextWriter::write() const
{
    exportHeader();
    exportSource();

    EntityTypeWriter writer(m_exporter);
    foreach(EntityType *type, m_context->entityTypes()) {
        writer.setEntityType(type);
        writer.write();
    }
}

void ContextWriter::writeDeclaration(QString &header) const
{
    QString oldContent = readFromFile(makeHeaderFilename(m_classname));
    QString extraContent = extractExtraContent(oldContent);


    QString contextName = makeClassname(m_context->identifier() + QLatin1String("Context"));
    QString baseEntityTypeName = makeClassname(m_context->baseEntityType()->identifier());

    foreach(EntityType *type, m_context->entityTypes()) {
        header.append("class "+makeClassname(type->identifier())+";\n");
    }

    header.append(QLatin1String("\nclass ")+contextName+QLatin1String(" : public LBDatabase::Context\n"
                                                                    "{\n"
                                                                    "\tQ_OBJECT\n"
                                                                    "public:\n"
                                                                    "\tQ_INVOKABLE "));

    header.append(contextName + QLatin1String("(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);\n"));
    header.append(QLatin1String("\tstatic const QString Name;\n\n\t"));
    header.append(baseEntityTypeName+QLatin1String(" *")+makeMethodName(baseEntityTypeName)+QLatin1String("(int id) const;\n"));

    QString plural = makeMethodName(m_context->baseEntityType()->displayNamePlural());
    header.append("\tQList<"+baseEntityTypeName+" *> "+plural+"() const;\n");

    writeExtraContent(extraContent, header);

    header.append(QLatin1String("};\n\n"));
}

void ContextWriter::writeImplementation(QString &source) const
{
    QString oldContent = readFromFile(makeSourceFilename(m_classname));
    QString extraContent = extractExtraContent(oldContent);

    QString contextName = makeClassname(m_context->identifier() + QLatin1String("Context"));
    QString baseEntityTypeName = makeClassname(m_context->baseEntityType()->identifier());

    CalculatorWriter writer(m_exporter);
    foreach(EntityType *type, m_context->entityTypes()) {
        writeInclude(makeClassname(type->identifier()), source);
        writer.setEntityType(type);
        if(writer.isNeeded()) {
            writeInclude(makeClassname(type->identifier() + QLatin1String("Calculator")),source);
        }
    }

    source.append(QLatin1String("\nconst QString ") + contextName + QLatin1String("::Name(\"") + m_context->identifier() + QLatin1String("\");\n"));

    source.append(
            contextName+QLatin1String("::")+contextName+QLatin1String(
    "(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :\n"
        "\tLBDatabase::Context(metaData, parent)\n"
    "{\n"));

    foreach(EntityType *type, m_context->entityTypes()) {
        source.append(QLatin1String("\tregisterEntityClass<") + makeClassname(type->identifier()) + QLatin1String(">();\n"));
        writer.setEntityType(type);
        if(writer.isNeeded()) {
            source.append(QLatin1String("\tregisterCalculatorClass<") + makeClassname(type->identifier()) + QLatin1String(",") + makeClassname(type->identifier()) + QLatin1String("Calculator>();\n\n"));
        }
    }
    source.append(QLatin1String("}\n\n"));

    source.append(
    baseEntityTypeName+QLatin1String(" *")+contextName+QLatin1String("::")+makeMethodName(baseEntityTypeName)+QLatin1String("(int id) const\n"
    "{\n"
        "\treturn static_cast<")+baseEntityTypeName+QLatin1String(" *>(entity(id));\n"
    "}\n\n"));

    QString plural = makeMethodName(m_context->baseEntityType()->displayNamePlural());
    source.append("QList<"+baseEntityTypeName +"*> "+contextName+"::"+plural+"() const\n"
                  "{\n"
                  "\tQList<"+baseEntityTypeName+" *> "+plural+";\n"
                  "\tforeach(LBDatabase::Entity *entity, entities())\n"
                  "\t\t"+plural+".append(static_cast<"+baseEntityTypeName+" *>(entity));\n"
                  "\treturn "+plural+";\n"
                  "}\n\n");

    writeExtraContent(extraContent, source);
}


void ContextWriter::exportHeader() const
{
    QString header;

    startHeader(m_classname, header);
    startNamespace(header);

    writeDeclaration(header);

    endNamespace(header);
    endHeader(m_classname, header);

    writeToFile(makeHeaderFilename(m_classname), header);
}

void ContextWriter::exportSource() const
{
    QString source;

    writeInclude(m_classname, source);

    source.append(QLatin1String("\n"));

    startNamespace(source);

    writeImplementation(source);

    endNamespace(source);

    writeToFile(makeSourceFilename(m_classname), source);
}

} // namespace LBDatabase

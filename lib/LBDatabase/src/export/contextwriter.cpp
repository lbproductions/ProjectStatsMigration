#include "contextwriter.h"

#include "calculatorwriter.h"
#include "entitytypewriter.h"

#include "../context.h"
#include "../entitytype.h"

namespace LBDatabase {

ContextWriter::ContextWriter(const CppExporter *exporter) :
    EntityTypeWriter(exporter),
    m_context(0)
{
}

void ContextWriter::setContext(Context *context)
{
    m_context = context;
    setEntityType(m_context->baseEntityType());
}

void ContextWriter::write() const
{
    EntityTypeWriter::write();

    EntityTypeWriter writer(m_exporter);
    foreach(EntityType *type, m_context->entityTypes()) {
        if(type != m_context->baseEntityType()) {
            writer.setEntityType(type);
            writer.write();
        }
    }
}

void ContextWriter::writeDeclaration(QString &header) const
{
    EntityTypeWriter::writeDeclaration(header);

    QString contextName = makeClassname(m_context->identifier() + QLatin1String("Context"));
    QString baseEntityTypeName = makeClassname(m_entityType->identifier());

    header.append(QLatin1String("class ")+contextName+QLatin1String(" : public LBDatabase::Context\n"
                                                                    "{\n"
                                                                    "\tQ_OBJECT\n"
                                                                    "public:\n"
                                                                    "\tQ_INVOKABLE "));

    header.append(contextName + QLatin1String("(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);\n"));
    header.append(QLatin1String("\tstatic const QString Name;\n\n\t"));
    header.append(baseEntityTypeName+QLatin1String(" *")+makeMethodName(baseEntityTypeName)+QLatin1String("(int id) const;\n"));
    header.append(QLatin1String("};\n\n"));
}

void ContextWriter::writeImplementation(QString &source) const
{
    QString contextName = makeClassname(m_context->identifier() + QLatin1String("Context"));
    QString baseEntityTypeName = makeClassname(m_entityType->identifier());

    CalculatorWriter writer(m_exporter);
    foreach(EntityType *type, m_context->entityTypes()) {
        if(type != m_context->baseEntityType()) {
            writeInclude(makeClassname(type->identifier()), source);
        }
        writer.setEntityType(type);
        if(writer.isNeeded()) {
            writeInclude(makeClassname(type->identifier() + QLatin1String("Calculator")),source);
        }
    }

    source.append(QLatin1String("\nconst QString ") + contextName + QLatin1String("::Name(\"") + m_context->identifier() + QLatin1String("\");\n"));

    EntityTypeWriter::writeImplementation(source);

    source.append(
            contextName+QLatin1String("::")+contextName+QLatin1String(
    "(LBDatabase::Row *row, LBDatabase::Storage *parent) :\n"
        "\tContext(row, parent)\n"
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
}

} // namespace LBDatabase

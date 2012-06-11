#include "calculatorwriter.h"

#include <LBDatabase/entitytype.h>
#include <LBDatabase/function.h>

#include <QDebug>

namespace LBDatabase {

namespace {
const QString InsertionPoint("// NEW METHODS HERE. DO NOT DELETE THIS LINE!");
}

CalculatorWriter::CalculatorWriter(const CppExporter *exporter) :
    Writer(exporter)
{
}

void CalculatorWriter::setEntityType(EntityType *type)
{
    m_entityType = type;
}

void CalculatorWriter::write() const
{
    if(isNeeded()) {
        exportHeader();
        exportSource();
    }
}

bool CalculatorWriter::isNeeded() const
{
    bool hasCalculatedProperties = false;

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isCalculated()) {
            hasCalculatedProperties = true;
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isCalculated()) {
            hasCalculatedProperties = true;
        }
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->isCalculated() && !relation->isTranspose()) {
            hasCalculatedProperties = true;
        }
    }

    return hasCalculatedProperties;
}

void CalculatorWriter::exportHeader() const
{
    QString calculatorClass = makeClassname(m_entityType->identifier() + QLatin1String("Calculator"));
    QString header;

    startHeader(calculatorClass, header);
    startNamespace(header);

    header.append(QLatin1String(
        "\nclass ")+calculatorClass+QLatin1String(" : public LBDatabase::Calculator\n"
        "{\n"
        "Q_OBJECT\n"
        "public:\n\tQ_INVOKABLE explicit ")+
            calculatorClass+QLatin1String("(QObject *parent = 0);\n\n")
    );

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isCalculated()) {
            header.append(QLatin1String("\t\n\tQ_INVOKABLE QVariant ")+makeMethodName(attribute->identifier())+QLatin1String("(const LBDatabase::Entity *entity) const;\n"));
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isCalculated()) {
            header.append(QLatin1String("\t\n\tQ_INVOKABLE EntityVariantHash ")+makeMethodName(function->identifier())+QLatin1String("(const LBDatabase::Entity *entity) const;\n"));
        }
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->isCalculated() && !relation->isTranspose()) {
            header.append(QLatin1String("\t\n\tQ_INVOKABLE RelatedEntities ")+makeMethodName(relation->identifier())+QLatin1String("(const LBDatabase::Entity *entity) const;\n"));
        }
    }

    header.append(QLatin1String("};\n\n"));

    endNamespace(header);
    endHeader(calculatorClass, header);

    writeToFile(makeHeaderFilename(calculatorClass), header);
}

void CalculatorWriter::exportSource() const
{
    QString calculatorClass = makeClassname(m_entityType->identifier() + QLatin1String("Calculator"));
    QString entityTypeClass = makeClassname(m_entityType->identifier());
    QString fileName = makeSourceFilename(calculatorClass);
    QString source = readFromFile(fileName);

    if(source.isEmpty()) {
        writeInclude(calculatorClass, source);
        source.append(QLatin1String("\n"));
        writeInclude(entityTypeClass, source);
        startNamespace(source);

        source.append(QLatin1String("\n")+
                calculatorClass+QLatin1String("::")+calculatorClass+QLatin1String(
        "(QObject *parent) :\n"
            "\tCalculator(parent)\n"
          "{\n"
          "}\n\n"));
        source.append(InsertionPoint);
        endNamespace(source);
    }

    int insertionPoint = source.indexOf(InsertionPoint);
    QString name;
    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isCalculated()) {
            name = calculatorClass+QLatin1String("::")+makeMethodName(attribute->identifier());

            if(!source.contains(name)) {
                source.insert(insertionPoint, QLatin1String("QVariant ")+calculatorClass+QLatin1String("::")+makeMethodName(attribute->identifier())+QLatin1String("(const LBDatabase::Entity *entity) const\n"
                "{\n"
                     "\t//! \\todo IMPLEMENT ME\n\tconst ")+
                              entityTypeClass+QLatin1String(" *")+makeMethodName(entityTypeClass)+
                              QLatin1String(" = static_cast<const ")+entityTypeClass+QLatin1String(" *>(entity);\n")+
                     QLatin1String("\treturn QVariant();\n"
                "}\n\n"));
            }
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isCalculated()) {
            name = calculatorClass+QLatin1String("::")+makeMethodName(function->identifier());

            if(!source.contains(name)) {
                source.insert(insertionPoint, QLatin1String("EntityVariantHash ")+calculatorClass+QLatin1String("::")+makeMethodName(function->identifier())+QLatin1String("(const LBDatabase::Entity *entity) const\n"
                "{\n"
                     "\t//! \\todo IMPLEMENT ME\n\tconst ")+
                              entityTypeClass+QLatin1String(" *")+makeMethodName(entityTypeClass)+
                              QLatin1String(" = static_cast<const ")+entityTypeClass+QLatin1String(" *>(entity);\n")+
                     QLatin1String("\treturn EntityVariantHash();\n"
                "}\n\n"));
            }
        }
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->isCalculated() && !relation->isTranspose()) {
            name = calculatorClass+QLatin1String("::")+makeMethodName(relation->identifier());

            if(!source.contains(name)) {
                source.insert(insertionPoint, QLatin1String("RelatedEntities ")+calculatorClass+QLatin1String("::")+makeMethodName(relation->identifier())+QLatin1String("(const LBDatabase::Entity *entity) const\n"
                "{\n"
                     "\t//! \\todo IMPLEMENT ME\n\tconst ")+
                              entityTypeClass+QLatin1String(" *")+makeMethodName(entityTypeClass)+
                              QLatin1String(" = static_cast<const ")+entityTypeClass+QLatin1String(" *>(entity);\n")+
                     QLatin1String("\treturn RelatedEntities();\n"
                "}\n\n"));
            }
        }
    }

    writeToFile(makeSourceFilename(calculatorClass), source);
}

} // namespace LBDatabase

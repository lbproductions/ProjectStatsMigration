#include "entitytypewriter.h"

#include "calculatorwriter.h"

#include <LBDatabase/attribute.h>
#include <LBDatabase/entitytype.h>
#include <LBDatabase/enumattribute.h>
#include <LBDatabase/function.h>

#include <QStringList>

namespace LBDatabase {

EntityTypeWriter::EntityTypeWriter(const CppExporter *exporter) :
    Writer(exporter)
{
}

void EntityTypeWriter::setEntityType(EntityType *type)
{
    m_entityType = type;
    m_classname = makeClassname(m_entityType->identifier());
}

void EntityTypeWriter::write() const
{
    exportHeader();
    exportSource();

    CalculatorWriter writer(m_exporter);
    writer.setEntityType(m_entityType);
    writer.write();
}

void EntityTypeWriter::writeNeededHeaders(QString &source) const
{
    QStringList declaredTypes;
    QString name;

    source.append(QLatin1String("\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->returnEntityType()) {
            name = attribute->returnEntityType()->className();
            if(!declaredTypes.contains(name)) {
                declaredTypes << name;
                writeInclude(name, source);
            }
        }
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->entityType() == m_entityType) {
            name = makeClassname(relation->entityTypeOther()->identifier());
        }
        else {
            name = makeClassname(relation->entityType()->identifier());
        }

        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            writeInclude(name, source);
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        name = makeClassname(function->keyEntityType()->identifier());
        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            writeInclude(name, source);
        }

        if(function->returnEntityType()) {
            name = function->returnEntityType()->className();
            if(!declaredTypes.contains(name)) {
                declaredTypes << name;
                writeInclude(name, source);
            }
        }
    }

    source.append(QLatin1String("\n"));
}

void EntityTypeWriter::writeNeededQtHeaders(QString &header) const
{
    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->type() == Attribute::Pixmap) {
            header.append(QLatin1String("#include <QPixmap>\n"));
        }
        else if(attribute->type() == Attribute::Icon) {
            header.append(QLatin1String("#include <QIcon>\n"));
        }
        else if(attribute->type() == Attribute::DateTime) {
            header.append(QLatin1String("#include <QDateTime>\n"));
        }
        else if(attribute->type() == Attribute::Time) {
            header.append(QLatin1String("#include <QTime>\n"));
        }
        else if(attribute->type() == Attribute::Color) {
            header.append(QLatin1String("#include <QColor>\n"));
        }
        else if(attribute->type() == Attribute::StringList) {
            header.append(QLatin1String("#include <QStringList>\n"));
        }
    }
}

void EntityTypeWriter::writePropertyNameStrings(QString &header) const
{
    writeNamespaceBegin(m_classname+QLatin1String("Properties"), header);

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        QString attributeName = attribute->identifier();
        header.append(QLatin1String("const QString ")+ makeClassname(attributeName) + QLatin1String("Attribute(\"") +
                      attributeName+QLatin1String("\");\n"));
    }

    QList<Relation *> visitedRelations;
    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(!visitedRelations.contains(relation)) {
            header.append(QLatin1String("const QString ")+ makeRelationName(relation) + QLatin1String("Relation(\"") +
                          relation->identifier()+QLatin1String("\");\n"));
            visitedRelations.append(relation);
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        QString functionName = function->identifier();
        header.append(QLatin1String("const QString ")+ makeClassname(functionName) + QLatin1String("Function(\"") +
                      functionName+QLatin1String("\");\n"));
    }

    writeNamespaceEnd(m_classname+QLatin1String("Properties"), header);
}

void EntityTypeWriter::writeForwardDeclarations(QString &header) const
{
    QStringList declaredTypes;
    QString name;

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->returnEntityType()) {
            name = attribute->returnEntityType()->className();
            if(!declaredTypes.contains(name)) {
                declaredTypes << name;
                header.append(QLatin1String("class ") + name + QLatin1String(";\n"));
            }
        }
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->entityType() == m_entityType) {
            name = makeClassname(relation->entityTypeOther()->identifier());
        }
        else {
            name = makeClassname(relation->entityType()->identifier());
        }

        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            header.append(QLatin1String("class ") + name + QLatin1String(";\n"));
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        name = makeClassname(function->keyEntityType()->identifier());
        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            header.append(QLatin1String("class ") + name + QLatin1String(";\n"));
        }

        if(function->returnEntityType()) {
            name = function->returnEntityType()->className();
            if(!declaredTypes.contains(name)) {
                declaredTypes << name;
                header.append(QLatin1String("class ") + name + QLatin1String(";\n"));
            }
        }
    }
}

void EntityTypeWriter::writeDeclaration(QString &header) const
{
    QString oldContent = readFromFile(makeHeaderFilename(m_classname));
    QString extraContent = extractExtraContent(oldContent);

    writeNeededQtHeaders(header);

    QString baseClass = "LBDatabase::Entity";
    if(m_entityType->parentEntityType()) {
        baseClass = makeClassname(m_entityType->parentEntityType()->identifier());
        writeInclude(baseClass,header);
    }

    header.append(QLatin1String("\n"));

    writePropertyNameStrings(header);
    writeForwardDeclarations(header);

    header.append(QLatin1String("\nclass ")+m_classname+QLatin1String(" : public ")+baseClass+QLatin1String("\n"
    "{\n"
        "\tQ_OBJECT\n"
    "public:\n"
        "\tQ_INVOKABLE ")+m_classname+QLatin1String("(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);\n"
        "\tstatic const QString Name;\n"
        "\tstatic const int EntityTypeId;\n\n"));

    header.append(QLatin1String("\tQString displayName() const;\n\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->type() == Attribute::Enum) {
            writeEnum(static_cast<EnumAttribute *>(attribute), header);
        }
    }

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        writeAttributeGetterDeclaration(attribute, header);
    }

    header.append(QLatin1String("\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isEditable()) {
           writeAttributeSetterDeclaration(attribute, header);
        }
    }

    header.append(QLatin1String("\n"));

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        writeFunctionGetterDeclaration(function, header);
    }

    header.append(QLatin1String("\n"));

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isEditable()) {
            writeFunctionSetterDeclaration(function, header);
        }
    }

    header.append(QLatin1String("\n"));

    QList<Relation *> visitedRelations;
    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(!visitedRelations.contains(relation)) {
            writeRelationDeclaration(relation, header);
            visitedRelations.append(relation);
        }
    }

    writeExtraContent(extraContent, header);

    header.append(QLatin1String("\n"));

    header.append(QLatin1String("signals:\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isEditable() || attribute->isCalculated()) {
           writeAttributeChangedSignal(attribute, header);
        }
    }
    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isEditable()) {
           writeFunctionChangedSignal(function, header);
        }
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->isCalculated() || relation->isEditable() && !relation->isTranspose()) {
           writeRelationChangedSignal(relation, header);
        }
    }

    header.append(QLatin1String("};\n\n"));

    header.append(QLatin1String("Q_DECLARE_METATYPE(QList<")+m_classname+QLatin1String(" *>)\n"));
    header.append(QLatin1String("Q_DECLARE_METATYPE(")+m_classname+QLatin1String(" *)\n\n"));
}

void EntityTypeWriter::writeImplementation(QString &source) const
{
    QString oldContent = readFromFile(makeSourceFilename(m_classname));
    QString extraContent = extractExtraContent(oldContent);

    if(extraContent.isEmpty()) {
        extraContent.append(QLatin1String("\nQString ")+m_classname+QLatin1String("::displayName() const\n"
                                                                               "{\n"
                                                                               "\treturn Entity::displayName();\n"
                                                                               "}\n"));
    }

    QString baseClass("Entity");
    if(m_entityType->parentEntityType())
        baseClass = makeClassname(m_entityType->parentEntityType()->identifier());

    source.append(QLatin1String("const QString ") + m_classname + QLatin1String("::Name(\"") + m_entityType->identifier() + QLatin1String("\");\n"));
    source.append(QLatin1String("const int ") + m_classname + QLatin1String("::EntityTypeId(") + QString::number(m_entityType->id()) + QLatin1String(");\n\n"));

    source.append(
         m_classname+QLatin1String("::")+m_classname+QLatin1String(
    "(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :\n"
        "\t") + baseClass + QLatin1String("(metaData, context)\n"
    "{\n"
    "}\n\n"));

     foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
         writeAttributeGetterImplementation(attribute, source);
     }

     foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
         if(attribute->isEditable()) {
            writeAttributeSetterImplementation(attribute, source);
         }
     }

     QList<Relation *> visitedRelations;
     foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
         if(!visitedRelations.contains(relation)) {
            writeRelationImplementation(relation, source);
            visitedRelations.append(relation);
         }
     }

     foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
         writeFunctionGetterImplementation(function, source);
     }

     foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
         if(function->isEditable()) {
             writeFunctionSetterImplementation(function, source);
         }
     }

     writeExtraContent(extraContent, source);

     source.append(QLatin1String("\n"));
}

void EntityTypeWriter::writeEnum(EnumAttribute *attribute, QString &header) const
{
    header.append(QLatin1String("\tenum ")+makeClassname(attribute->identifier())+QLatin1String(" {\n"));

    const QMap<int, QString> map = attribute->enumValues();
    QMap<int, QString>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i != map.constBegin()) {
            header.append(QLatin1String(",\n"));
        }
        header.append(QLatin1String("\t\t")+i.value()+QLatin1String(" = ")+QString::number(i.key()));
        ++i;
    }
    header.append(QLatin1String("\n\t};\n\n"));
}

void EntityTypeWriter::writeAttributeGetterDeclaration(Attribute *attribute, QString &header) const
{
    header.append(QLatin1String("\t") + attribute->qtType() + QLatin1String(" ") +
                  makeMethodName(attribute->identifier()) + QLatin1String("() const;\n"));
}

void EntityTypeWriter::writeAttributeSetterDeclaration(Attribute *attribute, QString &header) const
{
    QString constString;
    QString ampString;
    if(attribute->qtType().startsWith("Q")) {
        constString = QLatin1String("const ");
        ampString = QLatin1String("&");
    }

    header.append(QLatin1String("\tvoid set") +
                  makeClassname(attribute->identifier()) + QLatin1String("(")+constString+attribute->qtType()+QLatin1String(" ")+ampString+makeMethodName(attribute->identifier())+QLatin1String(");\n"));
}

void EntityTypeWriter::writeAttributeGetterImplementation(Attribute *attribute, QString &source) const
{
    QString attributeType = attribute->qtType();
    QString attributeName = attribute->identifier();
    if(attribute->type() == Attribute::Enum) {
        source.append(m_classname+QLatin1String("::")+makeClassname(attributeType)+QLatin1String(" ")+m_classname+QLatin1String("::")+makeMethodName(attributeName)+
                      QLatin1String("() const\n"
                                    "{\n"
                                    "\treturn static_cast<")+makeClassname(attributeType)+QLatin1String(">(value(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<int>());\n"
                                                  "}\n\n"));
    }
    else if(attribute->type() == Attribute::Pixmap){
        source.append(attributeType+QLatin1String(" ")+m_classname+QLatin1String("::")+makeMethodName(attributeName)+
                      QLatin1String("() const\n"
                                    "{\n"
                                    "\treturn QPixmap(value(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).toString());\n"
                                                  "}\n\n"));
    }
    else {
        source.append(attributeType+QLatin1String(" ")+m_classname+QLatin1String("::")+makeMethodName(attributeName)+
                      QLatin1String("() const\n"
                                    "{\n"
                                    "\treturn value(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<") +
                      attributeType+QLatin1String(">();\n"
                                                  "}\n\n"));
    }
}

void EntityTypeWriter::writeAttributeSetterImplementation(Attribute *attribute, QString &source) const
{
    QString attributeType = attribute->qtType();
    QString attributeName = attribute->identifier();
    if(attribute->type() == Attribute::Enum) {
        source.append(QLatin1String("void ")+m_classname+QLatin1String("::set")+makeClassname(attribute->identifier()) + QLatin1String("(")+attribute->qtType()+QLatin1String(" ")+makeMethodName(attribute->identifier())+QLatin1String(")\n"
                                    "{\n"
                                    "\tif(")+makeMethodName(attribute->identifier())+QLatin1String(" == this->")+makeMethodName(attribute->identifier())+QLatin1String("())\n"
                                    "\t\treturn;\n"
                                    "\tsetValue(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute,"
                                                  "QVariant::fromValue<int>(") +
                      makeMethodName(attribute->identifier())+QLatin1String("));\n"
                                                  "\temit ")+makeMethodName(attribute->identifier())+QLatin1String("Changed(")+
                     makeMethodName(attribute->identifier())+QLatin1String(");\n"
                                                  "}\n\n"));
    }
    else {
        QString constString;
        QString ampString;
        if(attribute->qtType().startsWith("Q")) {
            constString = QLatin1String("const ");
            ampString = QLatin1String("&");
        }

        source.append(QLatin1String("void ")+m_classname+QLatin1String("::set")+makeClassname(attribute->identifier()) + QLatin1String("(")+constString+attribute->qtType()+QLatin1String(" ")+ampString+makeMethodName(attribute->identifier())+QLatin1String(")\n"
                                    "{\n"
                                    "\tif(")+makeMethodName(attribute->identifier())+QLatin1String(" == this->")+makeMethodName(attribute->identifier())+QLatin1String("())\n"
                                    "\t\treturn;\n"
                                    "\tsetValue(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute,"
                                                  "QVariant::fromValue<") +
                      attributeType+QLatin1String(">(") +
                      makeMethodName(attribute->identifier())+QLatin1String("));\n"
                                                  "\temit ")+makeMethodName(attribute->identifier())+QLatin1String("Changed(")+
                     makeMethodName(attribute->identifier())+QLatin1String(");\n"
                                                  "}\n\n"));
    }
}

void EntityTypeWriter::writeAttributeChangedSignal(Attribute *attribute, QString &header) const
{
    header.append(QLatin1String("\tvoid ") + attribute->signalSignature() + QLatin1String(";\n"));
}

void EntityTypeWriter::writeRelationDeclaration(Relation *relation, QString &header) const
{
    QString relationName = makeRelationName(relation);
    QString entityType = makeRelationType(relation);

    if(relation->cardinality() == Relation::OneToOne ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->direction() == Relation::Both &&
             relation->isTranspose())) {
        header.append(QLatin1String("\t") + entityType + QLatin1String(" *") +
                  makeMethodName(relationName) + QLatin1String("() const;\n"));
    }
    else if(relation->cardinality() == Relation::ManyToMany ||
            (relation->cardinality() == Relation::OneToMany &&
             !relation->isTranspose())) {
        header.append(QLatin1String("\tQList<") + entityType + QLatin1String(" *> ") +
                  makeMethodName(relationName) + QLatin1String("() const;\n"));

        if(relation->isEditable() && !relation->isTranspose()) {
            header.append("\tvoid add"+entityType+"("+entityType+" *"+makeMethodName(relationName)+");\n");
        }
    }

    if(relation->isEditableTranspose() && relation->isTranspose()) {
        header.append("\tvoid ");
        if(relation->cardinality() == Relation::ManyToMany) {
            header.append("add");
        }
        else {
            header.append("set");
        }
        header.append(makeClassname(relationName)+"("+entityType+" *"+makeMethodName(relationName)+");\n");
    }
}

void EntityTypeWriter::writeRelationImplementation(Relation *relation, QString &source) const
{
    QString relationName = makeRelationName(relation);
    QString entityType = makeRelationType(relation);

    if(relation->cardinality() == Relation::OneToOne ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->direction() == Relation::Both &&
             relation->isTranspose())) {
         source.append(
         QLatin1String("") + entityType + QLatin1String(" *")+
                     m_classname+QLatin1String("::")+makeMethodName(relationName)+QLatin1String("() const\n"
              "{\n"
                    "\treturn relation<")+entityType+QLatin1String(">(")+m_classname+
                                QLatin1String("Properties::")+relationName+QLatin1String("Relation)->firstEntity();\n"
              "}\n\n"));
    }
    else if(relation->cardinality() == Relation::ManyToMany ||
            (relation->cardinality() == Relation::OneToMany &&
             !relation->isTranspose())) {
         source.append(
         QLatin1String("QList<") + entityType + QLatin1String(" *> ")+
                     m_classname+QLatin1String("::")+makeMethodName(relationName)+QLatin1String("() const\n"
              "{\n"
                    "\treturn relation<")+entityType+QLatin1String(">(")+m_classname+
                                QLatin1String("Properties::")+relationName+QLatin1String("Relation)->entities();\n"
              "}\n\n"));

         if(relation->isEditable() && !relation->isTranspose()) {
             source.append("void "+m_classname+"::add"+entityType+"("+entityType+" *"+makeMethodName(entityType)+")\n"
             "{\n"
                           "\trelation<"+entityType+">("+m_classname+"Properties::"+relationName+"Relation)->addEntity("+makeMethodName(entityType)+");\n"
                           "\temit " + makeMethodName(relation->identifier()) + entityType + QLatin1String("Added(") + makeMethodName(entityType) + QLatin1String(");\n"
             "}\n\n"));
         }
    }

    if(relation->isEditableTranspose() && relation->isTranspose()) {
        source.append("void "+m_classname+"::");
        if(relation->cardinality() == Relation::ManyToMany) {
            source.append("add");
        }
        else {
            source.append("set");
        }
        source.append(makeClassname(relationName)+"("+entityType+" *"+makeMethodName(relationName)+")\n"
        "{\n"
                      "\trelation<"+entityType+">("+m_classname+"Properties::"+relationName+"Relation)->addEntity("+makeMethodName(relationName)+");\n"
        "}\n\n");

        //                      "\temit " + makeMethodName(relation->identifier()) + entityType + QLatin1String("Added(") + makeMethodName(entityType) + QLatin1String(");\n"
    }
}

void EntityTypeWriter::writeRelationChangedSignal(Relation *relation, QString &header) const
{
    QString entityType = makeRelationType(relation);
    if(relation->isCalculated()) {
        header.append(QLatin1String("\tvoid ") +
                  makeMethodName(relation->identifier()) + QLatin1String("Changed();\n"));
    }
    else {
        header.append(QLatin1String("\tvoid ") +
                  makeMethodName(relation->identifier()) + entityType + QLatin1String("Added(") + entityType + QLatin1String(" *")
                  + makeMethodName(entityType) + QLatin1String(");\n"));
    }
}

void EntityTypeWriter::writeFunctionGetterDeclaration(Function *function, QString &header) const
{
    header.append(QLatin1String("\t") + function->qtTypeName() + QLatin1String(" ") +
                  makeMethodName(function->identifier()) + QLatin1String("(const ")+makeClassname(function->keyEntityType()->identifier())+
                  QLatin1String(" *")+makeMethodName(function->keyEntityType()->identifier())+QLatin1String(") const;\n"));
}

void EntityTypeWriter::writeFunctionGetterImplementation(Function *function, QString &source) const
{
    source.append(function->qtTypeName() + QLatin1String(" ") +m_classname+QLatin1String("::")+
                  makeMethodName(function->identifier()) + QLatin1String("(const ")+makeClassname(function->keyEntityType()->identifier())+
                  QLatin1String(" *")+makeMethodName(function->keyEntityType()->identifier())+QLatin1String(") const\n"
                                "{\n"
                                "\treturn function(")+m_classname+
                  QLatin1String("Properties::")+makeClassname(function->identifier()) + QLatin1String("Function)->value(")+
                  makeMethodName(function->keyEntityType()->identifier())+QLatin1String(").value<") +
                  function->qtTypeName()+QLatin1String(">();\n"
                                                       "}\n\n"));
}

void EntityTypeWriter::writeFunctionSetterDeclaration(Function *function, QString &header) const
{
    QString constString;
    QString ampString;
    if(function->qtTypeName().startsWith("Q")) {
        constString = QLatin1String("const ");
        ampString = QLatin1String("&");
    }

    header.append(QLatin1String("\tvoid set") +
                  makeClassname(function->identifier()) + QLatin1String("(const ")+makeClassname(function->keyEntityType()->identifier())+
                  QLatin1String(" *")+makeMethodName(function->keyEntityType()->identifier())+QLatin1String(", ")+constString+function->qtTypeName()+
                  QLatin1String(" ")+ampString+makeMethodName(function->identifier())+QLatin1String(");\n"));
}

void EntityTypeWriter::writeFunctionSetterImplementation(Function *function, QString &source) const
{
    QString constString;
    QString ampString;
    if(function->qtTypeName().startsWith("Q")) {
        constString = QLatin1String("const ");
        ampString = QLatin1String("&");
    }

    source.append(QLatin1String("void ")+m_classname+QLatin1String("::set")+makeClassname(function->identifier()) +
                  QLatin1String("(const ")+makeClassname(function->keyEntityType()->identifier())+QLatin1String(" *")+makeMethodName(function->keyEntityType()->identifier())+QLatin1String(", ")+constString+function->qtTypeName()+QLatin1String(" ")+ampString+makeMethodName(function->identifier())+QLatin1String(")\n"
                                "{\n"
                                                                                                                                                                                                                                                                                                                 "\tif(")+makeMethodName(function->identifier())+QLatin1String(" == this->")+makeMethodName(function->identifier())+QLatin1String("(")+makeMethodName(function->keyEntityType()->identifier())+QLatin1String("))\n"
                                "\t\treturn;\n"));


    source.append(QLatin1String("\tfunction(")+m_classname+QLatin1String("Properties::")+makeClassname(function->identifier())+QLatin1String("Function)"));
    source.append(QLatin1String("->setValue(") + makeMethodName(function->keyEntityType()->identifier()) + QLatin1String(", QVariant::fromValue<")+function->qtTypeName());
    source.append(QLatin1String(">(")+makeMethodName(function->identifier())+QLatin1String("));\n"));

    source.append(QLatin1String("\temit ")+makeMethodName(function->identifier())+QLatin1String("Changed(")+
                 makeMethodName(function->keyEntityType()->identifier())+QLatin1String(",") + makeMethodName(function->identifier()) + QLatin1String(");\n"
                                              "}\n\n"));
}

void EntityTypeWriter::writeFunctionChangedSignal(Function *function, QString &header) const
{
    header.append(QLatin1String("\tvoid ") +
                  makeMethodName(function->identifier()) + QLatin1String("Changed(const ")+
                  makeClassname(function->keyEntityType()->identifier())+QLatin1String(" *")+
                  makeMethodName(function->keyEntityType()->identifier())+QLatin1String(",") + function->qtTypeName() + QLatin1String(" ")
                  + makeMethodName(function->identifier()) + QLatin1String(");\n"));
}

void EntityTypeWriter::exportHeader() const
{
    QString header;

    startHeader(m_classname, header);
    startNamespace(header);

    writeDeclaration(header);

    endNamespace(header);
    endHeader(m_classname, header);

    writeToFile(makeHeaderFilename(m_classname), header);
}

void EntityTypeWriter::exportSource() const
{
    QString source;

    writeInclude(m_classname, source);

    writeNeededHeaders(source);

    source.append(QLatin1String("\n"));

    startNamespace(source);

    writeImplementation(source);

    endNamespace(source);

    writeToFile(makeSourceFilename(m_classname), source);
}

QString EntityTypeWriter::makeRelationName(Relation *relation) const
{
    return makeClassname(relation->identifier());
}

QString EntityTypeWriter::makeRelationType(Relation *relation) const
{
    return makeClassname(relation->entityTypeOther()->identifier());
}

} // namespace LBDatabase

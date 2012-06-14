#ifndef LBDATBASE_ENTITYTYPEWRITER_H
#define LBDATBASE_ENTITYTYPEWRITER_H

#include "writer.h"

namespace LBDatabase {

class Attribute;
class CppExporter;
class EntityType;
class EnumAttribute;
class Function;
class Relation;

class EntityTypeWriter : public Writer
{
public:
    EntityTypeWriter(const CppExporter *exporter);

    void setEntityType(EntityType *type);

    void write() const;

protected:
    EntityType *m_entityType;
    QString m_classname;

    void exportHeader() const;
    void exportSource() const;

    void writeNeededHeaders(QString &header) const;
    void writeNeededQtHeaders(QString &header) const;
    void writePropertyNameStrings(QString &header) const;
    void writeForwardDeclarations(QString &header) const;

    virtual void writeDeclaration(QString &header) const;
    virtual void writeImplementation(QString &source) const;

    void writeEnum(EnumAttribute *attribute, QString &header) const;

    void writeAttributeGetterDeclaration(Attribute *attribute, QString &header) const;
    void writeAttributeGetterImplementation(Attribute *attribute, QString &source) const;
    void writeAttributeSetterDeclaration(Attribute *attribute, QString &header) const;
    void writeAttributeSetterImplementation(Attribute *attribute, QString &source) const;
    void writeAttributeChangedSignal(Attribute *attribute, QString &header) const;

    void writeRelationDeclaration(Relation *relation, QString &header) const;
    void writeRelationImplementation(Relation *relation, QString &source) const;
    void writeRelationChangedSignal(Relation *relation, QString &header) const;

    void writeFunctionGetterDeclaration(Function *function, QString &header) const;
    void writeFunctionGetterImplementation(Function *function, QString &source) const;
    void writeFunctionSetterDeclaration(Function *function, QString &header) const;
    void writeFunctionSetterImplementation(Function *function, QString &source) const;
    void writeFunctionChangedSignal(Function *function, QString &header) const;

    QString makeRelationName(Relation *relation) const;
    QString makeRelationType(Relation *relation) const;
};

} // namespace LBDatabase

#endif // LBDATBASE_ENTITYTYPEWRITER_H

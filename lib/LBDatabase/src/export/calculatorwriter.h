#ifndef LBDATABASE_CALCULATORWRITER_H
#define LBDATABASE_CALCULATORWRITER_H

#include "writer.h"

namespace LBDatabase {

class CppExporter;
class EntityType;

class CalculatorWriter : public Writer
{
public:
    CalculatorWriter(const CppExporter *exporter);

    void setEntityType(EntityType *type);

    void write() const;

    bool isNeeded() const;

private:
    EntityType *m_entityType;

    void exportHeader() const;
    void exportSource() const;
};

} // namespace LBDatabase

#endif // LBDATABASE_CALCULATORWRITER_H

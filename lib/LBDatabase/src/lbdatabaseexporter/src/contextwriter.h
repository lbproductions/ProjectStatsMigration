#ifndef LBDATABASE_CONTEXTWRITER_H
#define LBDATABASE_CONTEXTWRITER_H

#include "entitytypewriter.h"

namespace LBDatabase {

class CppExporter;
class Context;

class ContextWriter : public Writer
{
public:
    ContextWriter(const CppExporter *exporter);

    void setContext(Context *context);

    void write() const;

private:
    Context *m_context;
    QString m_classname;

    void writeDeclaration(QString &header) const;
    void writeImplementation(QString &source) const;

    void exportHeader() const;
    void exportSource() const;
};

} // namespace LBDatabase

#endif // LBDATABASE_CONTEXTWRITER_H

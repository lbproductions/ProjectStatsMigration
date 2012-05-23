#ifndef LBDATABASE_WRITER_H
#define LBDATABASE_WRITER_H

#include <QString>

namespace LBDatabase {

class CppExporter;

class Writer
{
public:
    explicit Writer(const CppExporter * const exporter);
    
    virtual void write() const = 0;

protected:
    void startNamespace(QString &file) const;
    void endNamespace(QString &file) const;

    void writeNamespaceBegin(const QString &namespaceName, QString &file) const;
    void writeNamespaceEnd(const QString &namespaceName, QString &file) const;

    void startHeader(const QString &classname, QString &header) const;
    void endHeader(const QString &classname, QString &header) const;

    void writeInclude(const QString &className, QString &file) const;

    QString makeClassname(const QString &name) const;
    QString makeMethodName(const QString &name) const;
    QString makeHeaderFilename(const QString &classname) const;
    QString makeSourceFilename(const QString &classname) const;

    void writeToFile(const QString &fileName, const QString &content) const;
    QString readFromFile(const QString &fileName) const;

    QString extractExtraContent(const QString &content) const;
    void writeExtraContent(const QString &content, QString &file) const;

    const CppExporter * const m_exporter;
};

} // namespace LBDatabase

#endif // LBDATABASE_WRITER_H

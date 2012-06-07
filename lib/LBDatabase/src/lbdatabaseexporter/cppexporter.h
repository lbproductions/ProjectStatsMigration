#ifndef LBDATABASE_CPPEXPORTER_H
#define LBDATABASE_CPPEXPORTER_H

#include <QObject>

namespace LBDatabase {

class Storage;

class CppExporterPrivate;
class CppExporter : public QObject
{
    Q_OBJECT
public:
    explicit CppExporter(QObject *parent = 0);
    ~CppExporter();
    
    void setStorage(Storage *storage);
    Storage *storage() const;
    void setDirectory(const QString &directory);
    QString directory() const;
    void setNamespaceName(const QString &namespaceName);
    QString namespaceName() const;

    void exportCpp() const;

private:
    QScopedPointer<CppExporterPrivate> d_ptr;
    Q_DECLARE_PRIVATE(CppExporter)
    Q_DISABLE_COPY(CppExporter)
};

} // namespace LBDatabase

#endif // LBDATABASE_CPPEXPORTER_H

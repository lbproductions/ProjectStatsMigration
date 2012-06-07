#include "cppexporter.h"

#include "storagewriter.h"

#include <LBDatabase/attribute.h>
#include <LBDatabase/context.h>
#include <LBDatabase/entitytype.h>
#include <LBDatabase/storage.h>

#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include <QDebug>

namespace LBDatabase {

class CppExporterPrivate
{
    CppExporterPrivate() : storage(0) {}

    void exportCpp() const;

    Storage *storage;
    QString directory;
    QString namespaceName;

    CppExporter * q_ptr;
    Q_DECLARE_PUBLIC(CppExporter)
};

void CppExporterPrivate::exportCpp() const
{
    Q_Q(const CppExporter);
    if(!storage)
        return;

    StorageWriter storageWriter(q);
    storageWriter.write();
}

CppExporter::CppExporter(QObject *parent) :
    QObject(parent),
    d_ptr(new CppExporterPrivate)
{
    Q_D(CppExporter);
    d->q_ptr = this;
}

CppExporter::~CppExporter()
{
}

void CppExporter::setStorage(Storage *storage)
{
    Q_D(CppExporter);
    d->storage = storage;
}

Storage *CppExporter::storage() const
{
    Q_D(const CppExporter);
    return d->storage;
}

void CppExporter::setDirectory(const QString &directory)
{
    Q_D(CppExporter);
    if(!directory.endsWith('/'))
        d->directory = directory + '/';
    else
        d->directory = directory;
}

QString CppExporter::directory() const
{
    Q_D(const CppExporter);
    return d->directory;
}

void CppExporter::setNamespaceName(const QString &namespaceName)
{
    Q_D(CppExporter);
    d->namespaceName = namespaceName;
}

QString CppExporter::namespaceName() const
{
    Q_D(const CppExporter);
    return d->namespaceName;
}

void CppExporter::exportCpp() const
{
    Q_D(const CppExporter);
    d->exportCpp();
}


} // namespace LBDatabase

#include "storagewriter.h"

#include "cppexporter.h"
#include "contextwriter.h"

#include "../context.h"
#include "../storage.h"
#include "../entitytype.h"

namespace LBDatabase {

StorageWriter::StorageWriter(const CppExporter *const exporter) :
    Writer(exporter)
{
}

void StorageWriter::write() const
{
    exportStorageHeader();
    exportStorageSource();

    ContextWriter writer(m_exporter);
    foreach(Context *context, m_exporter->storage()->contexts()) {
        writer.setContext(context);
        writer.write();
    }
}

void StorageWriter::exportStorageHeader() const
{
    Storage *storage = m_exporter->storage();
    QString storageClass = makeClassname(storage->name().append(QLatin1String("Storage")));
    QString header;

    startHeader(storageClass, header);
    startNamespace(header);

    QString contextName;
    foreach(Context *context, storage->contexts()) {
        contextName = makeClassname(context->identifier() + QLatin1String("Context"));
        header.append(QLatin1String("class ")+contextName+QLatin1String(";\n"));
    }

    header.append(QLatin1String(
        "\nclass ")+storageClass+QLatin1String(" : public LBDatabase::Storage\n"
        "{\n"
        "public:\n\t")+
            storageClass+QLatin1String("(const QString &fileName, QObject *parent = 0);\n\n")
    );

    QString methodName;
    foreach(Context *context, storage->contexts()) {
        contextName = makeClassname(context->identifier() + QLatin1String("Context"));
        methodName = makeMethodName(contextName);
        header.append(QLatin1String("\t")+contextName+QLatin1String(" *")+methodName+QLatin1String("() const;\n"));
    }

    header.append(QLatin1String("};\n\n"));

    endNamespace(header);
    endHeader(storageClass, header);

    writeToFile(makeHeaderFilename(storageClass), header);
}

void StorageWriter::exportStorageSource() const
{
    Storage *storage = m_exporter->storage();
    QString storageClass = makeClassname(storage->name().append(QLatin1String("Storage")));
    QString source;

    writeInclude(storageClass, source);
    startNamespace(source);

    foreach(Context *context, storage->contexts()) {
        writeInclude(makeClassname(context->baseEntityType()->identifier()), source);
    }

    source.append(QLatin1String("\n")+
            storageClass+QLatin1String("::")+storageClass+QLatin1String(
    "(const QString &fileName, QObject *parent) :\n"
        "\tStorage(fileName, parent)\n"
    "{\n"));

    QString contextName;
    foreach(Context *context, storage->contexts()) {
        contextName = makeClassname(context->identifier()) + QLatin1String("Context");
        source.append(QLatin1String("\tregisterContextType<") + contextName + QLatin1String(">();\n"));
    }
    source.append(QLatin1String("}\n\n"));

    QString methodName;
    foreach(Context *context, storage->contexts()) {
        contextName = makeClassname(context->identifier()) + QLatin1String("Context");
        methodName = makeMethodName(contextName);
        source.append(
                    contextName+QLatin1String(" *")+storageClass+QLatin1String("::")+methodName+QLatin1String("() const\n"
        "{\n"
            "\treturn static_cast<")+contextName+QLatin1String(" *>(context(")+contextName+QLatin1String("::Name));\n"
        "}\n\n"));
    }

    endNamespace(source);

    writeToFile(makeSourceFilename(storageClass), source);
}

} // namespace LBDatabase

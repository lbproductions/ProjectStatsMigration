#include <QApplication>

#include "cppexporter.h"

#include <LBDatabase/LBDatabase.h>

#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LBDatabase::Storage *storage = new LBDatabase::Storage();

    storage->setDriver(
                new LBDatabase::LocalStorageDriver(
                    a.arguments().at(1),
                    storage)
                );


    storage->open();

    LBDatabase::CppExporter exporter;
    exporter.setStorage(storage);
    exporter.setDirectory(a.arguments().at(2));
    exporter.exportCpp();

    return a.exec();
}

#ifndef LBDATABASE_STORAGEWRITER_H
#define LBDATABASE_STORAGEWRITER_H

#include "writer.h"

namespace LBDatabase {

class CppExporter;
class Storage;

class StorageWriter : public Writer
{
public:
    explicit StorageWriter(const CppExporter * const exporter);

    void write() const;

private:
    void exportStorageHeader() const;
    void exportStorageSource() const;
};

} // namespace LBDatabase

#endif // LBDATABASE_STORAGEWRITER_H

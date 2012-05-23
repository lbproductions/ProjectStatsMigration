#include "storagedriver.h"

namespace LBDatabase {

class StorageDriverPrivate
{
    StorageDriverPrivate() :
        q_ptr(0)
    {}

    StorageDriver * q_ptr;
    Q_DECLARE_PUBLIC(StorageDriver)
};

StorageDriver::StorageDriver(QObject *parent) :
    QObject(parent),
    d_ptr(new StorageDriverPrivate)
{
}

StorageDriver::~StorageDriver()
{
}

} // namespace LBDatabase

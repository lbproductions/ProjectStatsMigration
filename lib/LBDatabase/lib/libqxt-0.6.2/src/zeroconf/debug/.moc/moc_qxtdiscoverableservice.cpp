/****************************************************************************
** Meta object code from reading C++ file 'qxtdiscoverableservice.h'
**
** Created: Wed May 16 14:17:43 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtdiscoverableservice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtdiscoverableservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtDiscoverableService[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      42,   37,   23,   23, 0x05,
      76,   65,   23,   23, 0x05,
      97,   37,   23,   23, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtDiscoverableService[] = {
    "QxtDiscoverableService\0\0registered()\0"
    "code\0registrationError(int)\0domainName\0"
    "resolved(QByteArray)\0resolveError(int)\0"
};

void QxtDiscoverableService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtDiscoverableService *_t = static_cast<QxtDiscoverableService *>(_o);
        switch (_id) {
        case 0: _t->registered(); break;
        case 1: _t->registrationError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->resolved((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->resolveError((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtDiscoverableService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtDiscoverableService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtDiscoverableService,
      qt_meta_data_QxtDiscoverableService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtDiscoverableService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtDiscoverableService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtDiscoverableService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtDiscoverableService))
        return static_cast<void*>(const_cast< QxtDiscoverableService*>(this));
    if (!strcmp(_clname, "QxtDiscoverableServiceName"))
        return static_cast< QxtDiscoverableServiceName*>(const_cast< QxtDiscoverableService*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtDiscoverableService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QxtDiscoverableService::registered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QxtDiscoverableService::registrationError(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtDiscoverableService::resolved(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QxtDiscoverableService::resolveError(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

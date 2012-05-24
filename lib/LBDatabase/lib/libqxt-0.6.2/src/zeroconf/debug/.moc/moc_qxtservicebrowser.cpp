/****************************************************************************
** Meta object code from reading C++ file 'qxtservicebrowser.h'
**
** Created: Wed May 16 14:17:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtservicebrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtservicebrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtServiceBrowser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   19,   18,   18, 0x05,
      68,   49,   18,   18, 0x05,
      98,   49,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,   18,   18,   18, 0x0a,
     139,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtServiceBrowser[] = {
    "QxtServiceBrowser\0\0errorCode\0"
    "browsingFailed(int)\0serviceName,domain\0"
    "serviceAdded(QString,QString)\0"
    "serviceRemoved(QString,QString)\0"
    "browse()\0stopBrowsing()\0"
};

void QxtServiceBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtServiceBrowser *_t = static_cast<QxtServiceBrowser *>(_o);
        switch (_id) {
        case 0: _t->browsingFailed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->serviceAdded((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->serviceRemoved((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->browse(); break;
        case 4: _t->stopBrowsing(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtServiceBrowser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtServiceBrowser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtServiceBrowser,
      qt_meta_data_QxtServiceBrowser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtServiceBrowser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtServiceBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtServiceBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtServiceBrowser))
        return static_cast<void*>(const_cast< QxtServiceBrowser*>(this));
    if (!strcmp(_clname, "QxtDiscoverableServiceName"))
        return static_cast< QxtDiscoverableServiceName*>(const_cast< QxtServiceBrowser*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtServiceBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QxtServiceBrowser::browsingFailed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtServiceBrowser::serviceAdded(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtServiceBrowser::serviceRemoved(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

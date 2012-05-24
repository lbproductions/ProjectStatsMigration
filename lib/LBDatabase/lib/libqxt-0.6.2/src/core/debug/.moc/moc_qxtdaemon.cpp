/****************************************************************************
** Meta object code from reading C++ file 'qxtdaemon.h'
**
** Created: Wed May 16 14:09:52 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtdaemon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtdaemon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtDaemon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      23,   10,   10,   10, 0x05,
      32,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtDaemon[] = {
    "QxtDaemon\0\0signal(int)\0hangup()\0"
    "terminate()\0"
};

void QxtDaemon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtDaemon *_t = static_cast<QxtDaemon *>(_o);
        switch (_id) {
        case 0: _t->signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->hangup(); break;
        case 2: _t->terminate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtDaemon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtDaemon::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtDaemon,
      qt_meta_data_QxtDaemon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtDaemon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtDaemon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtDaemon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtDaemon))
        return static_cast<void*>(const_cast< QxtDaemon*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtDaemon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QxtDaemon::signal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtDaemon::hangup()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QxtDaemon::terminate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

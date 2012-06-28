/****************************************************************************
** Meta object code from reading C++ file 'qxtabstractwebsessionmanager_p.h'
**
** Created: Wed Jun 27 16:28:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtabstractwebsessionmanager_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtabstractwebsessionmanager_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtAbstractWebSessionManagerPrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      47,   37,   36,   36, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtAbstractWebSessionManagerPrivate[] = {
    "QxtAbstractWebSessionManagerPrivate\0"
    "\0sessionID\0sessionDestroyed(int)\0"
};

void QxtAbstractWebSessionManagerPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtAbstractWebSessionManagerPrivate *_t = static_cast<QxtAbstractWebSessionManagerPrivate *>(_o);
        switch (_id) {
        case 0: _t->sessionDestroyed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtAbstractWebSessionManagerPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtAbstractWebSessionManagerPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtAbstractWebSessionManagerPrivate,
      qt_meta_data_QxtAbstractWebSessionManagerPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtAbstractWebSessionManagerPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtAbstractWebSessionManagerPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtAbstractWebSessionManagerPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtAbstractWebSessionManagerPrivate))
        return static_cast<void*>(const_cast< QxtAbstractWebSessionManagerPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtAbstractWebSessionManager>"))
        return static_cast< QxtPrivate<QxtAbstractWebSessionManager>*>(const_cast< QxtAbstractWebSessionManagerPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtAbstractWebSessionManagerPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

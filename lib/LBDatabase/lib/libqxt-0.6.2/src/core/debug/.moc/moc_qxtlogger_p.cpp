/****************************************************************************
** Meta object code from reading C++ file 'qxtlogger_p.h'
**
** Created: Wed May 16 14:09:57 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtlogger_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtlogger_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtLoggerPrivate[] = {

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
      20,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtLoggerPrivate[] = {
    "QxtLoggerPrivate\0\0,\0"
    "log(QxtLogger::LogLevel,QList<QVariant>)\0"
};

void QxtLoggerPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtLoggerPrivate *_t = static_cast<QxtLoggerPrivate *>(_o);
        switch (_id) {
        case 0: _t->log((*reinterpret_cast< QxtLogger::LogLevel(*)>(_a[1])),(*reinterpret_cast< const QList<QVariant>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtLoggerPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtLoggerPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtLoggerPrivate,
      qt_meta_data_QxtLoggerPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtLoggerPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtLoggerPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtLoggerPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtLoggerPrivate))
        return static_cast<void*>(const_cast< QxtLoggerPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtLogger>"))
        return static_cast< QxtPrivate<QxtLogger>*>(const_cast< QxtLoggerPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtLoggerPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

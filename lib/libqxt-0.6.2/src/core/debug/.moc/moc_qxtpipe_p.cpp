/****************************************************************************
** Meta object code from reading C++ file 'qxtpipe_p.h'
**
** Created: Wed Jun 27 16:26:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtpipe_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtpipe_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtPipePrivate[] = {

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
      28,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtPipePrivate[] = {
    "QxtPipePrivate\0\0data,sender\0"
    "push(QByteArray,const QxtPipe*)\0"
};

void QxtPipePrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtPipePrivate *_t = static_cast<QxtPipePrivate *>(_o);
        switch (_id) {
        case 0: _t->push((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< const QxtPipe*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtPipePrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtPipePrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtPipePrivate,
      qt_meta_data_QxtPipePrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtPipePrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtPipePrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtPipePrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtPipePrivate))
        return static_cast<void*>(const_cast< QxtPipePrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtPipe>"))
        return static_cast< QxtPrivate<QxtPipe>*>(const_cast< QxtPipePrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtPipePrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

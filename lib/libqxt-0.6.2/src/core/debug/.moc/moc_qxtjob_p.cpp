/****************************************************************************
** Meta object code from reading C++ file 'qxtjob_p.h'
**
** Created: Wed Jun 27 16:26:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtjob_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtjob_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtJobPrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtJobPrivate[] = {
    "QxtJobPrivate\0\0done()\0inwrap_d()\0"
};

void QxtJobPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtJobPrivate *_t = static_cast<QxtJobPrivate *>(_o);
        switch (_id) {
        case 0: _t->done(); break;
        case 1: _t->inwrap_d(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtJobPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtJobPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtJobPrivate,
      qt_meta_data_QxtJobPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtJobPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtJobPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtJobPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtJobPrivate))
        return static_cast<void*>(const_cast< QxtJobPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtJob>"))
        return static_cast< QxtPrivate<QxtJob>*>(const_cast< QxtJobPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtJobPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QxtJobPrivate::done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

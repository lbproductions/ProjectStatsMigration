/****************************************************************************
** Meta object code from reading C++ file 'qxtitemdelegate_p.h'
**
** Created: Wed Jun 27 16:28:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtitemdelegate_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtitemdelegate_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtItemDelegatePrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      47,   40,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtItemDelegatePrivate[] = {
    "QxtItemDelegatePrivate\0\0viewDestroyed()\0"
    "editor\0closeEditor(QWidget*)\0"
};

void QxtItemDelegatePrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtItemDelegatePrivate *_t = static_cast<QxtItemDelegatePrivate *>(_o);
        switch (_id) {
        case 0: _t->viewDestroyed(); break;
        case 1: _t->closeEditor((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtItemDelegatePrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtItemDelegatePrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtItemDelegatePrivate,
      qt_meta_data_QxtItemDelegatePrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtItemDelegatePrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtItemDelegatePrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtItemDelegatePrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtItemDelegatePrivate))
        return static_cast<void*>(const_cast< QxtItemDelegatePrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtItemDelegate>"))
        return static_cast< QxtPrivate<QxtItemDelegate>*>(const_cast< QxtItemDelegatePrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtItemDelegatePrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE

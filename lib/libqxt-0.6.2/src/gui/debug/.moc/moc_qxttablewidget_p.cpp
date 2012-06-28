/****************************************************************************
** Meta object code from reading C++ file 'qxttablewidget_p.h'
**
** Created: Wed Jun 27 16:28:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxttablewidget_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxttablewidget_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtTableWidgetPrivate[] = {

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
      29,   23,   22,   22, 0x08,
      61,   23,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtTableWidgetPrivate[] = {
    "QxtTableWidgetPrivate\0\0index\0"
    "informStartEditing(QModelIndex)\0"
    "informFinishEditing(QModelIndex)\0"
};

void QxtTableWidgetPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtTableWidgetPrivate *_t = static_cast<QxtTableWidgetPrivate *>(_o);
        switch (_id) {
        case 0: _t->informStartEditing((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->informFinishEditing((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtTableWidgetPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtTableWidgetPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtTableWidgetPrivate,
      qt_meta_data_QxtTableWidgetPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtTableWidgetPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtTableWidgetPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtTableWidgetPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtTableWidgetPrivate))
        return static_cast<void*>(const_cast< QxtTableWidgetPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtTableWidget>"))
        return static_cast< QxtPrivate<QxtTableWidget>*>(const_cast< QxtTableWidgetPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtTableWidgetPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

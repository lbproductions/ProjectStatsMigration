/****************************************************************************
** Meta object code from reading C++ file 'qxttabwidget_p.h'
**
** Created: Wed May 16 14:16:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxttabwidget_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxttabwidget_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtTabWidgetPrivate[] = {

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
      27,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtTabWidgetPrivate[] = {
    "QxtTabWidgetPrivate\0\0frame\0"
    "setMovieFrame(int)\0"
};

void QxtTabWidgetPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtTabWidgetPrivate *_t = static_cast<QxtTabWidgetPrivate *>(_o);
        switch (_id) {
        case 0: _t->setMovieFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtTabWidgetPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtTabWidgetPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtTabWidgetPrivate,
      qt_meta_data_QxtTabWidgetPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtTabWidgetPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtTabWidgetPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtTabWidgetPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtTabWidgetPrivate))
        return static_cast<void*>(const_cast< QxtTabWidgetPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtTabWidget>"))
        return static_cast< QxtPrivate<QxtTabWidget>*>(const_cast< QxtTabWidgetPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtTabWidgetPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

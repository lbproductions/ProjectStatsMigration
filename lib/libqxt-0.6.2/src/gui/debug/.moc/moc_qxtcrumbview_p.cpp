/****************************************************************************
** Meta object code from reading C++ file 'qxtcrumbview_p.h'
**
** Created: Wed Jun 27 16:28:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtcrumbview_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtcrumbview_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtCrumbViewPrivate[] = {

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
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtCrumbViewPrivate[] = {
    "QxtCrumbViewPrivate\0\0buttonPressed()\0"
};

void QxtCrumbViewPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtCrumbViewPrivate *_t = static_cast<QxtCrumbViewPrivate *>(_o);
        switch (_id) {
        case 0: _t->buttonPressed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtCrumbViewPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtCrumbViewPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtCrumbViewPrivate,
      qt_meta_data_QxtCrumbViewPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCrumbViewPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCrumbViewPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCrumbViewPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCrumbViewPrivate))
        return static_cast<void*>(const_cast< QxtCrumbViewPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtCrumbView>"))
        return static_cast< QxtPrivate<QxtCrumbView>*>(const_cast< QxtCrumbViewPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtCrumbViewPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_QxtCrumbViewDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QxtCrumbViewDelegate[] = {
    "QxtCrumbViewDelegate\0"
};

void QxtCrumbViewDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtCrumbViewDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtCrumbViewDelegate::staticMetaObject = {
    { &QAbstractItemDelegate::staticMetaObject, qt_meta_stringdata_QxtCrumbViewDelegate,
      qt_meta_data_QxtCrumbViewDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCrumbViewDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCrumbViewDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCrumbViewDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCrumbViewDelegate))
        return static_cast<void*>(const_cast< QxtCrumbViewDelegate*>(this));
    return QAbstractItemDelegate::qt_metacast(_clname);
}

int QxtCrumbViewDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE

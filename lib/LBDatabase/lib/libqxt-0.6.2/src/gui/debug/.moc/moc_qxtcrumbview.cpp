/****************************************************************************
** Meta object code from reading C++ file 'qxtcrumbview.h'
**
** Created: Wed May 16 14:16:18 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtcrumbview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtcrumbview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtCrumbView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      22,   13,   13,   13, 0x0a,
      35,   29,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtCrumbView[] = {
    "QxtCrumbView\0\0reset()\0back()\0index\0"
    "enterTree(QModelIndex)\0"
};

void QxtCrumbView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtCrumbView *_t = static_cast<QxtCrumbView *>(_o);
        switch (_id) {
        case 0: _t->reset(); break;
        case 1: _t->back(); break;
        case 2: _t->enterTree((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtCrumbView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtCrumbView::staticMetaObject = {
    { &QAbstractItemView::staticMetaObject, qt_meta_stringdata_QxtCrumbView,
      qt_meta_data_QxtCrumbView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCrumbView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCrumbView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCrumbView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCrumbView))
        return static_cast<void*>(const_cast< QxtCrumbView*>(this));
    return QAbstractItemView::qt_metacast(_clname);
}

int QxtCrumbView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

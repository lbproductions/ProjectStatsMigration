/****************************************************************************
** Meta object code from reading C++ file 'qxtscheduleview_p.h'
**
** Created: Wed May 16 14:16:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtscheduleview_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtscheduleview_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtScheduleInternalItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   25,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtScheduleInternalItem[] = {
    "QxtScheduleInternalItem\0\0item,oldGeometry\0"
    "geometryChanged(QxtScheduleInternalItem*,QVector<QRect>)\0"
};

void QxtScheduleInternalItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtScheduleInternalItem *_t = static_cast<QxtScheduleInternalItem *>(_o);
        switch (_id) {
        case 0: _t->geometryChanged((*reinterpret_cast< QxtScheduleInternalItem*(*)>(_a[1])),(*reinterpret_cast< QVector<QRect>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtScheduleInternalItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtScheduleInternalItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtScheduleInternalItem,
      qt_meta_data_QxtScheduleInternalItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScheduleInternalItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScheduleInternalItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScheduleInternalItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScheduleInternalItem))
        return static_cast<void*>(const_cast< QxtScheduleInternalItem*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtScheduleInternalItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QxtScheduleInternalItem::geometryChanged(QxtScheduleInternalItem * _t1, QVector<QRect> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_QxtScheduleViewPrivate[] = {

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
      41,   24,   23,   23, 0x0a,
     102,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtScheduleViewPrivate[] = {
    "QxtScheduleViewPrivate\0\0item,oldGeometry\0"
    "itemGeometryChanged(QxtScheduleInternalItem*,QVector<QRect>)\0"
    "scrollTimerTimeout()\0"
};

void QxtScheduleViewPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtScheduleViewPrivate *_t = static_cast<QxtScheduleViewPrivate *>(_o);
        switch (_id) {
        case 0: _t->itemGeometryChanged((*reinterpret_cast< QxtScheduleInternalItem*(*)>(_a[1])),(*reinterpret_cast< QVector<QRect>(*)>(_a[2]))); break;
        case 1: _t->scrollTimerTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtScheduleViewPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtScheduleViewPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtScheduleViewPrivate,
      qt_meta_data_QxtScheduleViewPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScheduleViewPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScheduleViewPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScheduleViewPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScheduleViewPrivate))
        return static_cast<void*>(const_cast< QxtScheduleViewPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtScheduleView>"))
        return static_cast< QxtPrivate<QxtScheduleView>*>(const_cast< QxtScheduleViewPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtScheduleViewPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

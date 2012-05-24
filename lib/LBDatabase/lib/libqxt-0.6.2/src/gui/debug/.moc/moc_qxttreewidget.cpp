/****************************************************************************
** Meta object code from reading C++ file 'qxttreewidget.h'
**
** Created: Wed May 16 14:16:43 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxttreewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxttreewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtTreeWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       2,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      57,   15,   14,   14, 0x05,
      95,   15,   14,   14, 0x05,

 // properties: name, type, flags
     158,  137, 0x0009510b,
     192,  174, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_QxtTreeWidget[] = {
    "QxtTreeWidget\0\0item\0"
    "itemEditingStarted(QTreeWidgetItem*)\0"
    "itemEditingFinished(QTreeWidgetItem*)\0"
    "itemCheckStateChanged(QxtTreeWidgetItem*)\0"
    "Qxt::DecorationStyle\0decorationStyle\0"
    "Qt::TextElideMode\0elideMode\0"
};

void QxtTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtTreeWidget *_t = static_cast<QxtTreeWidget *>(_o);
        switch (_id) {
        case 0: _t->itemEditingStarted((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->itemEditingFinished((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->itemCheckStateChanged((*reinterpret_cast< QxtTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QxtTreeWidget[] = {
        Qxt::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QxtTreeWidget[] = {
        &Qxt::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

const QMetaObjectExtraData QxtTreeWidget::staticMetaObjectExtraData = {
    qt_meta_extradata_QxtTreeWidget,  qt_static_metacall 
};

const QMetaObject QxtTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_QxtTreeWidget,
      qt_meta_data_QxtTreeWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtTreeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtTreeWidget))
        return static_cast<void*>(const_cast< QxtTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int QxtTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Qxt::DecorationStyle*>(_v) = decorationStyle(); break;
        case 1: *reinterpret_cast< Qt::TextElideMode*>(_v) = elideMode(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDecorationStyle(*reinterpret_cast< Qxt::DecorationStyle*>(_v)); break;
        case 1: setElideMode(*reinterpret_cast< Qt::TextElideMode*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QxtTreeWidget::itemEditingStarted(QTreeWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtTreeWidget::itemEditingFinished(QTreeWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtTreeWidget::itemCheckStateChanged(QxtTreeWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'qxtlistwidget.h'
**
** Created: Wed May 16 14:16:28 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtlistwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtListWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      57,   15,   14,   14, 0x05,
      95,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtListWidget[] = {
    "QxtListWidget\0\0item\0"
    "itemEditingStarted(QListWidgetItem*)\0"
    "itemEditingFinished(QListWidgetItem*)\0"
    "itemCheckStateChanged(QxtListWidgetItem*)\0"
};

void QxtListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtListWidget *_t = static_cast<QxtListWidget *>(_o);
        switch (_id) {
        case 0: _t->itemEditingStarted((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->itemEditingFinished((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->itemCheckStateChanged((*reinterpret_cast< QxtListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtListWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_QxtListWidget,
      qt_meta_data_QxtListWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtListWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtListWidget))
        return static_cast<void*>(const_cast< QxtListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int QxtListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QxtListWidget::itemEditingStarted(QListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtListWidget::itemEditingFinished(QListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtListWidget::itemCheckStateChanged(QxtListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'qxttablewidget.h'
**
** Created: Wed May 16 14:16:38 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxttablewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxttablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtTableWidget[] = {

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
      21,   16,   15,   15, 0x05,
      59,   16,   15,   15, 0x05,
      98,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtTableWidget[] = {
    "QxtTableWidget\0\0item\0"
    "itemEditingStarted(QTableWidgetItem*)\0"
    "itemEditingFinished(QTableWidgetItem*)\0"
    "itemCheckStateChanged(QxtTableWidgetItem*)\0"
};

void QxtTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtTableWidget *_t = static_cast<QxtTableWidget *>(_o);
        switch (_id) {
        case 0: _t->itemEditingStarted((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->itemEditingFinished((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->itemCheckStateChanged((*reinterpret_cast< QxtTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtTableWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_QxtTableWidget,
      qt_meta_data_QxtTableWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtTableWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtTableWidget))
        return static_cast<void*>(const_cast< QxtTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int QxtTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
void QxtTableWidget::itemEditingStarted(QTableWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtTableWidget::itemEditingFinished(QTableWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtTableWidget::itemCheckStateChanged(QxtTableWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
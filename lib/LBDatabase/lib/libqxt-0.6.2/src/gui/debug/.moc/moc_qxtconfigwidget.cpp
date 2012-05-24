/****************************************************************************
** Meta object code from reading C++ file 'qxtconfigwidget.h'
**
** Created: Wed May 16 14:16:12 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtconfigwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtconfigwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtConfigWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   39, // properties
       1,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   17,   16,   16, 0x0a,
      74,   69,   16,   16, 0x0a,
      99,   16,   16,   16, 0x0a,
     108,   16,   16,   16, 0x0a,

 // properties: name, type, flags
     121,  117, 0x02095001,
     127,  117, 0x02095103,
     145,  140, 0x01095103,
     187,  157, 0x0009510b,
     206,  200, 0x15095103,

 // enums: name, flags, count, data
     215, 0x0,    3,   58,

 // enum data: key, value
     228, uint(QxtConfigWidget::North),
     234, uint(QxtConfigWidget::West),
     239, uint(QxtConfigWidget::East),

       0        // eod
};

static const char qt_meta_stringdata_QxtConfigWidget[] = {
    "QxtConfigWidget\0\0index\0currentIndexChanged(int)\0"
    "setCurrentIndex(int)\0page\0"
    "setCurrentPage(QWidget*)\0accept()\0"
    "reject()\0int\0count\0currentIndex\0bool\0"
    "hoverEffect\0QxtConfigWidget::IconPosition\0"
    "iconPosition\0QSize\0iconSize\0IconPosition\0"
    "North\0West\0East\0"
};

void QxtConfigWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtConfigWidget *_t = static_cast<QxtConfigWidget *>(_o);
        switch (_id) {
        case 0: _t->currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setCurrentPage((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->accept(); break;
        case 4: _t->reject(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtConfigWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtConfigWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QxtConfigWidget,
      qt_meta_data_QxtConfigWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtConfigWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtConfigWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtConfigWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtConfigWidget))
        return static_cast<void*>(const_cast< QxtConfigWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QxtConfigWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = count(); break;
        case 1: *reinterpret_cast< int*>(_v) = currentIndex(); break;
        case 2: *reinterpret_cast< bool*>(_v) = hasHoverEffect(); break;
        case 3: *reinterpret_cast< QxtConfigWidget::IconPosition*>(_v) = iconPosition(); break;
        case 4: *reinterpret_cast< QSize*>(_v) = iconSize(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: setCurrentIndex(*reinterpret_cast< int*>(_v)); break;
        case 2: setHoverEffect(*reinterpret_cast< bool*>(_v)); break;
        case 3: setIconPosition(*reinterpret_cast< QxtConfigWidget::IconPosition*>(_v)); break;
        case 4: setIconSize(*reinterpret_cast< QSize*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QxtConfigWidget::currentIndexChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

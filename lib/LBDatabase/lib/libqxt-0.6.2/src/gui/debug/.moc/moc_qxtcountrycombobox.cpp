/****************************************************************************
** Meta object code from reading C++ file 'qxtcountrycombobox.h'
**
** Created: Wed May 16 14:16:14 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtcountrycombobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtcountrycombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtCountryComboBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       2,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   20,   19,   19, 0x05,
      73,   68,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     108,   20,   19,   19, 0x0a,

 // properties: name, type, flags
     152,  144, 0x0a095001,
     188,  171, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_QxtCountryComboBox[] = {
    "QxtCountryComboBox\0\0country\0"
    "currentCountryChanged(QLocale::Country)\0"
    "name\0currentCountryNameChanged(QString)\0"
    "setCurrentCountry(QLocale::Country)\0"
    "QString\0currentCountryName\0QLocale::Country\0"
    "currentCountry\0"
};

void QxtCountryComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtCountryComboBox *_t = static_cast<QxtCountryComboBox *>(_o);
        switch (_id) {
        case 0: _t->currentCountryChanged((*reinterpret_cast< QLocale::Country(*)>(_a[1]))); break;
        case 1: _t->currentCountryNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setCurrentCountry((*reinterpret_cast< QLocale::Country(*)>(_a[1]))); break;
        default: ;
        }
    }
}

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QxtCountryComboBox[] = {
        QLocale::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QxtCountryComboBox[] = {
        &QLocale::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

const QMetaObjectExtraData QxtCountryComboBox::staticMetaObjectExtraData = {
    qt_meta_extradata_QxtCountryComboBox,  qt_static_metacall 
};

const QMetaObject QxtCountryComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_QxtCountryComboBox,
      qt_meta_data_QxtCountryComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCountryComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCountryComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCountryComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCountryComboBox))
        return static_cast<void*>(const_cast< QxtCountryComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int QxtCountryComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< QString*>(_v) = currentCountryName(); break;
        case 1: *reinterpret_cast< QLocale::Country*>(_v) = currentCountry(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: setCurrentCountry(*reinterpret_cast< QLocale::Country*>(_v)); break;
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
void QxtCountryComboBox::currentCountryChanged(QLocale::Country _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtCountryComboBox::currentCountryNameChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'qxtcountrycombobox_p.h'
**
** Created: Wed May 16 14:16:15 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtcountrycombobox_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtcountrycombobox_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtCountryComboBoxPrivate[] = {

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
      35,   27,   26,   26, 0x0a,
      77,   71,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtCountryComboBoxPrivate[] = {
    "QxtCountryComboBoxPrivate\0\0country\0"
    "setCurrentCountry(QLocale::Country)\0"
    "index\0comboBoxCurrentIndexChanged(int)\0"
};

void QxtCountryComboBoxPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtCountryComboBoxPrivate *_t = static_cast<QxtCountryComboBoxPrivate *>(_o);
        switch (_id) {
        case 0: _t->setCurrentCountry((*reinterpret_cast< QLocale::Country(*)>(_a[1]))); break;
        case 1: _t->comboBoxCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtCountryComboBoxPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtCountryComboBoxPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtCountryComboBoxPrivate,
      qt_meta_data_QxtCountryComboBoxPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCountryComboBoxPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCountryComboBoxPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCountryComboBoxPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCountryComboBoxPrivate))
        return static_cast<void*>(const_cast< QxtCountryComboBoxPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtCountryComboBox>"))
        return static_cast< QxtPrivate<QxtCountryComboBox>*>(const_cast< QxtCountryComboBoxPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtCountryComboBoxPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

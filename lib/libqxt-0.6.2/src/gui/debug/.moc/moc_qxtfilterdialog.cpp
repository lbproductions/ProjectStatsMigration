/****************************************************************************
** Meta object code from reading C++ file 'qxtfilterdialog.h'
**
** Created: Wed Jun 27 16:28:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtfilterdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtfilterdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtFilterDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   59, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x0a,
      29,   16,   16,   16, 0x0a,
      38,   16,   16,   16, 0x0a,
      54,   47,   16,   16, 0x0a,
     111,   95,   16,   16, 0x0a,
     151,   16,   16,   16, 0x2a,
     177,  172,   16,   16, 0x0a,
     207,  200,   16,   16, 0x0a,
     233,  228,   16,   16, 0x0a,

 // properties: name, type, flags
     256,  252, 0x02095103,
     269,  252, 0x02095103,
     288,  280, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtFilterDialog[] = {
    "QxtFilterDialog\0\0r\0done(int)\0accept()\0"
    "reject()\0syntax\0"
    "setPatternSyntax(QRegExp::PatternSyntax)\0"
    "caseSensitivity\0setCaseSensitivity(Qt::CaseSensitivity)\0"
    "setCaseSensitivity()\0text\0"
    "setFilterText(QString)\0column\0"
    "setLookupColumn(int)\0role\0setLookupRole(int)\0"
    "int\0lookupColumn\0lookupRole\0QString\0"
    "filterText\0"
};

void QxtFilterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtFilterDialog *_t = static_cast<QxtFilterDialog *>(_o);
        switch (_id) {
        case 0: _t->done((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->accept(); break;
        case 2: _t->reject(); break;
        case 3: _t->setPatternSyntax((*reinterpret_cast< QRegExp::PatternSyntax(*)>(_a[1]))); break;
        case 4: _t->setCaseSensitivity((*reinterpret_cast< Qt::CaseSensitivity(*)>(_a[1]))); break;
        case 5: _t->setCaseSensitivity(); break;
        case 6: _t->setFilterText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setLookupColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setLookupRole((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtFilterDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtFilterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QxtFilterDialog,
      qt_meta_data_QxtFilterDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtFilterDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtFilterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtFilterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtFilterDialog))
        return static_cast<void*>(const_cast< QxtFilterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QxtFilterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = lookupColumn(); break;
        case 1: *reinterpret_cast< int*>(_v) = lookupRole(); break;
        case 2: *reinterpret_cast< QString*>(_v) = filterText(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setLookupColumn(*reinterpret_cast< int*>(_v)); break;
        case 1: setLookupRole(*reinterpret_cast< int*>(_v)); break;
        case 2: setFilterText(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE

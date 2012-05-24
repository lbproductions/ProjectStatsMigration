/****************************************************************************
** Meta object code from reading C++ file 'qxtcheckcombobox_p.h'
**
** Created: Wed May 16 14:16:09 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtcheckcombobox_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtcheckcombobox_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtCheckComboModel[] = {

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
      20,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtCheckComboModel[] = {
    "QxtCheckComboModel\0\0checkStateChanged()\0"
};

void QxtCheckComboModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtCheckComboModel *_t = static_cast<QxtCheckComboModel *>(_o);
        switch (_id) {
        case 0: _t->checkStateChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtCheckComboModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtCheckComboModel::staticMetaObject = {
    { &QStandardItemModel::staticMetaObject, qt_meta_stringdata_QxtCheckComboModel,
      qt_meta_data_QxtCheckComboModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCheckComboModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCheckComboModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCheckComboModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCheckComboModel))
        return static_cast<void*>(const_cast< QxtCheckComboModel*>(this));
    return QStandardItemModel::qt_metacast(_clname);
}

int QxtCheckComboModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStandardItemModel::qt_metacall(_c, _id, _a);
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
void QxtCheckComboModel::checkStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_QxtCheckComboBoxPrivate[] = {

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
      25,   24,   24,   24, 0x0a,
      52,   46,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtCheckComboBoxPrivate[] = {
    "QxtCheckComboBoxPrivate\0\0updateCheckedItems()\0"
    "index\0toggleCheckState(int)\0"
};

void QxtCheckComboBoxPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtCheckComboBoxPrivate *_t = static_cast<QxtCheckComboBoxPrivate *>(_o);
        switch (_id) {
        case 0: _t->updateCheckedItems(); break;
        case 1: _t->toggleCheckState((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtCheckComboBoxPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtCheckComboBoxPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtCheckComboBoxPrivate,
      qt_meta_data_QxtCheckComboBoxPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCheckComboBoxPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCheckComboBoxPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCheckComboBoxPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCheckComboBoxPrivate))
        return static_cast<void*>(const_cast< QxtCheckComboBoxPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtCheckComboBox>"))
        return static_cast< QxtPrivate<QxtCheckComboBox>*>(const_cast< QxtCheckComboBoxPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtCheckComboBoxPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

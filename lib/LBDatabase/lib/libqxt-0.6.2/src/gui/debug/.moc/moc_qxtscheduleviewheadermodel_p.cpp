/****************************************************************************
** Meta object code from reading C++ file 'qxtscheduleviewheadermodel_p.h'
**
** Created: Wed May 16 14:16:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtscheduleviewheadermodel_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtscheduleviewheadermodel_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtScheduleViewHeaderModel[] = {

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
      38,   28,   27,   27, 0x0a,
      65,   56,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtScheduleViewHeaderModel[] = {
    "QxtScheduleViewHeaderModel\0\0zoomDepth\0"
    "newZoomDepth(int)\0viewMode\0"
    "viewModeChanged(int)\0"
};

void QxtScheduleViewHeaderModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtScheduleViewHeaderModel *_t = static_cast<QxtScheduleViewHeaderModel *>(_o);
        switch (_id) {
        case 0: _t->newZoomDepth((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->viewModeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtScheduleViewHeaderModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtScheduleViewHeaderModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_QxtScheduleViewHeaderModel,
      qt_meta_data_QxtScheduleViewHeaderModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScheduleViewHeaderModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScheduleViewHeaderModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScheduleViewHeaderModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScheduleViewHeaderModel))
        return static_cast<void*>(const_cast< QxtScheduleViewHeaderModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int QxtScheduleViewHeaderModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
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

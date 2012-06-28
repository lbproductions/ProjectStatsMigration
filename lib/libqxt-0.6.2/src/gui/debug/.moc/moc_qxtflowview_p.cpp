/****************************************************************************
** Meta object code from reading C++ file 'qxtflowview_p.h'
**
** Created: Wed Jun 27 16:28:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtflowview_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtflowview_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtFlowViewPrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   20,   19,   19, 0x0a,
      83,   20,   19,   19, 0x0a,
     128,   20,   19,   19, 0x0a,
     165,   20,   19,   19, 0x0a,
     221,  201,   19,   19, 0x0a,
     281,  258,   19,   19, 0x0a,
     324,   19,   19,   19, 0x0a,
     349,   19,   19,   19, 0x0a,
     365,   19,   19,   19, 0x0a,
     387,   19,   19,   19, 0x0a,
     400,   20,   19,   19, 0x0a,
     443,   20,   19,   19, 0x0a,
     485,   20,   19,   19, 0x0a,
     519,   20,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtFlowViewPrivate[] = {
    "QxtFlowViewPrivate\0\0parent,start,end\0"
    "columnsAboutToBeInserted(QModelIndex,int,int)\0"
    "columnsAboutToBeRemoved(QModelIndex,int,int)\0"
    "columnsInserted(QModelIndex,int,int)\0"
    "columnsRemoved(QModelIndex,int,int)\0"
    "topLeft,bottomRight\0"
    "dataChanged(QModelIndex,QModelIndex)\0"
    "orientation,first,last\0"
    "headerDataChanged(Qt::Orientation,int,int)\0"
    "layoutAboutToBeChanged()\0layoutChanged()\0"
    "modelAboutToBeReset()\0modelReset()\0"
    "rowsAboutToBeInserted(QModelIndex,int,int)\0"
    "rowsAboutToBeRemoved(QModelIndex,int,int)\0"
    "rowsInserted(QModelIndex,int,int)\0"
    "rowsRemoved(QModelIndex,int,int)\0"
};

void QxtFlowViewPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtFlowViewPrivate *_t = static_cast<QxtFlowViewPrivate *>(_o);
        switch (_id) {
        case 0: _t->columnsAboutToBeInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->columnsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->columnsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->columnsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 5: _t->headerDataChanged((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->layoutAboutToBeChanged(); break;
        case 7: _t->layoutChanged(); break;
        case 8: _t->modelAboutToBeReset(); break;
        case 9: _t->modelReset(); break;
        case 10: _t->rowsAboutToBeInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->rowsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtFlowViewPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtFlowViewPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtFlowViewPrivate,
      qt_meta_data_QxtFlowViewPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtFlowViewPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtFlowViewPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtFlowViewPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtFlowViewPrivate))
        return static_cast<void*>(const_cast< QxtFlowViewPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtFlowViewPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

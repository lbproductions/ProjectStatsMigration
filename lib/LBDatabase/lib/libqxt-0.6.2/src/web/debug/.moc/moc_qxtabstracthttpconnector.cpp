/****************************************************************************
** Meta object code from reading C++ file 'qxtabstracthttpconnector.h'
**
** Created: Wed May 16 14:17:54 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtabstracthttpconnector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtabstracthttpconnector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtAbstractHttpConnector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   26,   25,   25, 0x08,
      58,   25,   25,   25, 0x28,
      73,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtAbstractHttpConnector[] = {
    "QxtAbstractHttpConnector\0\0device\0"
    "incomingData(QIODevice*)\0incomingData()\0"
    "disconnected()\0"
};

void QxtAbstractHttpConnector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtAbstractHttpConnector *_t = static_cast<QxtAbstractHttpConnector *>(_o);
        switch (_id) {
        case 0: _t->incomingData((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        case 1: _t->incomingData(); break;
        case 2: _t->disconnected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtAbstractHttpConnector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtAbstractHttpConnector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtAbstractHttpConnector,
      qt_meta_data_QxtAbstractHttpConnector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtAbstractHttpConnector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtAbstractHttpConnector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtAbstractHttpConnector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtAbstractHttpConnector))
        return static_cast<void*>(const_cast< QxtAbstractHttpConnector*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtAbstractHttpConnector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_QxtHttpServerConnector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtHttpServerConnector[] = {
    "QxtHttpServerConnector\0\0acceptConnection()\0"
};

void QxtHttpServerConnector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtHttpServerConnector *_t = static_cast<QxtHttpServerConnector *>(_o);
        switch (_id) {
        case 0: _t->acceptConnection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtHttpServerConnector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtHttpServerConnector::staticMetaObject = {
    { &QxtAbstractHttpConnector::staticMetaObject, qt_meta_stringdata_QxtHttpServerConnector,
      qt_meta_data_QxtHttpServerConnector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtHttpServerConnector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtHttpServerConnector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtHttpServerConnector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtHttpServerConnector))
        return static_cast<void*>(const_cast< QxtHttpServerConnector*>(this));
    return QxtAbstractHttpConnector::qt_metacast(_clname);
}

int QxtHttpServerConnector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QxtAbstractHttpConnector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_QxtScgiServerConnector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtScgiServerConnector[] = {
    "QxtScgiServerConnector\0\0acceptConnection()\0"
};

void QxtScgiServerConnector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtScgiServerConnector *_t = static_cast<QxtScgiServerConnector *>(_o);
        switch (_id) {
        case 0: _t->acceptConnection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtScgiServerConnector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtScgiServerConnector::staticMetaObject = {
    { &QxtAbstractHttpConnector::staticMetaObject, qt_meta_stringdata_QxtScgiServerConnector,
      qt_meta_data_QxtScgiServerConnector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScgiServerConnector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScgiServerConnector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScgiServerConnector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScgiServerConnector))
        return static_cast<void*>(const_cast< QxtScgiServerConnector*>(this));
    return QxtAbstractHttpConnector::qt_metacast(_clname);
}

int QxtScgiServerConnector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QxtAbstractHttpConnector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

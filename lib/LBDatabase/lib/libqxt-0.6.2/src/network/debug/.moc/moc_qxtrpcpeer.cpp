/****************************************************************************
** Meta object code from reading C++ file 'qxtrpcpeer.h'
**
** Created: Wed May 16 14:17:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtrpcpeer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtrpcpeer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtRPCPeer[] = {

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
      12,   11,   11,   11, 0x05,
      32,   11,   11,   11, 0x05,
      57,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtRPCPeer[] = {
    "QxtRPCPeer\0\0connectedToServer()\0"
    "disconnectedFromServer()\0"
    "serverError(QAbstractSocket::SocketError)\0"
};

void QxtRPCPeer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtRPCPeer *_t = static_cast<QxtRPCPeer *>(_o);
        switch (_id) {
        case 0: _t->connectedToServer(); break;
        case 1: _t->disconnectedFromServer(); break;
        case 2: _t->serverError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtRPCPeer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtRPCPeer::staticMetaObject = {
    { &QxtRPCService::staticMetaObject, qt_meta_stringdata_QxtRPCPeer,
      qt_meta_data_QxtRPCPeer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtRPCPeer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtRPCPeer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtRPCPeer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtRPCPeer))
        return static_cast<void*>(const_cast< QxtRPCPeer*>(this));
    return QxtRPCService::qt_metacast(_clname);
}

int QxtRPCPeer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QxtRPCService::qt_metacall(_c, _id, _a);
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
void QxtRPCPeer::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QxtRPCPeer::disconnectedFromServer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QxtRPCPeer::serverError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

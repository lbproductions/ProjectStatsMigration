/****************************************************************************
** Meta object code from reading C++ file 'qxtjsonrpccall.h'
**
** Created: Wed May 16 14:17:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtjsonrpccall.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtjsonrpccall.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtJSONRpcCall[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   16,   15,   15, 0x05,
      78,   73,   15,   15, 0x05,
     113,   15,   15,   15, 0x05,
     131,  124,   15,   15, 0x05,
     180,  159,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     210,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtJSONRpcCall[] = {
    "QxtJSONRpcCall\0\0bytesReceived,bytesTotal\0"
    "downloadProgress(qint64,qint64)\0code\0"
    "error(QNetworkReply::NetworkError)\0"
    "finished()\0errors\0sslErrors(QList<QSslError>)\0"
    "bytesSent,bytesTotal\0uploadProgress(qint64,qint64)\0"
    "d_finished()\0"
};

void QxtJSONRpcCall::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtJSONRpcCall *_t = static_cast<QxtJSONRpcCall *>(_o);
        switch (_id) {
        case 0: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 2: _t->finished(); break;
        case 3: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 4: _t->uploadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: _t->d->d_finished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtJSONRpcCall::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtJSONRpcCall::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtJSONRpcCall,
      qt_meta_data_QxtJSONRpcCall, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtJSONRpcCall::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtJSONRpcCall::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtJSONRpcCall::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtJSONRpcCall))
        return static_cast<void*>(const_cast< QxtJSONRpcCall*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtJSONRpcCall::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QxtJSONRpcCall::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtJSONRpcCall::error(QNetworkReply::NetworkError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtJSONRpcCall::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QxtJSONRpcCall::sslErrors(const QList<QSslError> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QxtJSONRpcCall::uploadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

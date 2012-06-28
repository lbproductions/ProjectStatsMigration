/****************************************************************************
** Meta object code from reading C++ file 'qxtsmtp.h'
**
** Created: Wed Jun 27 16:28:32 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtsmtp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtsmtp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSmtp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      21,    8,    8,    8, 0x05,
      44,   40,    8,    8, 0x05,
      73,    8,    8,    8, 0x05,
      85,    8,    8,    8, 0x05,
     104,   40,    8,    8, 0x05,
     133,    8,    8,    8, 0x05,
     149,    8,    8,    8, 0x05,
     172,   40,    8,    8, 0x05,
     220,  205,    8,    8, 0x05,
     267,  248,    8,    8, 0x05,
     306,  205,    8,    8, 0x05,
     337,  248,    8,    8, 0x05,
     396,  379,    8,    8, 0x05,
     437,  416,    8,    8, 0x05,
     475,  468,    8,    8, 0x05,
     489,    8,    8,    8, 0x05,
     500,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtSmtp[] = {
    "QxtSmtp\0\0connected()\0connectionFailed()\0"
    "msg\0connectionFailed(QByteArray)\0"
    "encrypted()\0encryptionFailed()\0"
    "encryptionFailed(QByteArray)\0"
    "authenticated()\0authenticationFailed()\0"
    "authenticationFailed(QByteArray)\0"
    "mailID,address\0senderRejected(int,QString)\0"
    "mailID,address,msg\0"
    "senderRejected(int,QString,QByteArray)\0"
    "recipientRejected(int,QString)\0"
    "recipientRejected(int,QString,QByteArray)\0"
    "mailID,errorCode\0mailFailed(int,int)\0"
    "mailID,errorCode,msg\0"
    "mailFailed(int,int,QByteArray)\0mailID\0"
    "mailSent(int)\0finished()\0disconnected()\0"
};

void QxtSmtp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtSmtp *_t = static_cast<QxtSmtp *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->connectionFailed(); break;
        case 2: _t->connectionFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->encrypted(); break;
        case 4: _t->encryptionFailed(); break;
        case 5: _t->encryptionFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: _t->authenticated(); break;
        case 7: _t->authenticationFailed(); break;
        case 8: _t->authenticationFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 9: _t->senderRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->senderRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 11: _t->recipientRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: _t->recipientRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 13: _t->mailFailed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->mailFailed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 15: _t->mailSent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->finished(); break;
        case 17: _t->disconnected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtSmtp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtSmtp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtSmtp,
      qt_meta_data_QxtSmtp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSmtp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSmtp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSmtp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSmtp))
        return static_cast<void*>(const_cast< QxtSmtp*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtSmtp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void QxtSmtp::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QxtSmtp::connectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QxtSmtp::connectionFailed(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QxtSmtp::encrypted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QxtSmtp::encryptionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QxtSmtp::encryptionFailed(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QxtSmtp::authenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void QxtSmtp::authenticationFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void QxtSmtp::authenticationFailed(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QxtSmtp::senderRejected(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QxtSmtp::senderRejected(int _t1, const QString & _t2, const QByteArray & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QxtSmtp::recipientRejected(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QxtSmtp::recipientRejected(int _t1, const QString & _t2, const QByteArray & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QxtSmtp::mailFailed(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void QxtSmtp::mailFailed(int _t1, int _t2, const QByteArray & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void QxtSmtp::mailSent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void QxtSmtp::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}

// SIGNAL 17
void QxtSmtp::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 17, 0);
}
QT_END_MOC_NAMESPACE

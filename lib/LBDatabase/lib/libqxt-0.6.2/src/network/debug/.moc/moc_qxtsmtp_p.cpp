/****************************************************************************
** Meta object code from reading C++ file 'qxtsmtp_p.h'
**
** Created: Wed May 16 14:17:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtsmtp_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtsmtp_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSmtpPrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   16,   15,   15, 0x0a,
      62,   15,   15,   15, 0x0a,
      75,   15,   15,   15, 0x0a,
      82,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtSmtpPrivate[] = {
    "QxtSmtpPrivate\0\0err\0"
    "socketError(QAbstractSocket::SocketError)\0"
    "socketRead()\0ehlo()\0sendNext()\0"
};

void QxtSmtpPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtSmtpPrivate *_t = static_cast<QxtSmtpPrivate *>(_o);
        switch (_id) {
        case 0: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->socketRead(); break;
        case 2: _t->ehlo(); break;
        case 3: _t->sendNext(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtSmtpPrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtSmtpPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtSmtpPrivate,
      qt_meta_data_QxtSmtpPrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSmtpPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSmtpPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSmtpPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSmtpPrivate))
        return static_cast<void*>(const_cast< QxtSmtpPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtSmtp>"))
        return static_cast< QxtPrivate<QxtSmtp>*>(const_cast< QxtSmtpPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtSmtpPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

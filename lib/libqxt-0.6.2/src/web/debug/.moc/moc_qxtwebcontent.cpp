/****************************************************************************
** Meta object code from reading C++ file 'qxtwebcontent.h'
**
** Created: Wed Jun 27 16:28:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtwebcontent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtwebcontent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtWebContent[] = {

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
      15,   14,   14,   14, 0x0a,
      40,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtWebContent[] = {
    "QxtWebContent\0\0ignoreRemainingContent()\0"
    "errorReceived(QAbstractSocket::SocketError)\0"
};

void QxtWebContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtWebContent *_t = static_cast<QxtWebContent *>(_o);
        switch (_id) {
        case 0: _t->ignoreRemainingContent(); break;
        case 1: _t->errorReceived((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QxtWebContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtWebContent::staticMetaObject = {
    { &QIODevice::staticMetaObject, qt_meta_stringdata_QxtWebContent,
      qt_meta_data_QxtWebContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtWebContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtWebContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtWebContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtWebContent))
        return static_cast<void*>(const_cast< QxtWebContent*>(this));
    return QIODevice::qt_metacast(_clname);
}

int QxtWebContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
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

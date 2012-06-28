/****************************************************************************
** Meta object code from reading C++ file 'qxtserialdevice.h'
**
** Created: Wed Jun 27 16:26:07 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtserialdevice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtserialdevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSerialDevice[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      16, 0x0,   11,   26,
      25, 0x1,   18,   48,
      37, 0x1,   18,   84,

 // enum data: key, value
      50, uint(QxtSerialDevice::Baud110),
      58, uint(QxtSerialDevice::Baud300),
      66, uint(QxtSerialDevice::Baud600),
      74, uint(QxtSerialDevice::Baud1200),
      83, uint(QxtSerialDevice::Baud2400),
      92, uint(QxtSerialDevice::Baud4800),
     101, uint(QxtSerialDevice::Baud9600),
     110, uint(QxtSerialDevice::Baud19200),
     120, uint(QxtSerialDevice::Baud38400),
     130, uint(QxtSerialDevice::Baud57600),
     140, uint(QxtSerialDevice::Baud115200),
     151, uint(QxtSerialDevice::Bit8),
     156, uint(QxtSerialDevice::Bit7),
     161, uint(QxtSerialDevice::Bit6),
     166, uint(QxtSerialDevice::Bit5),
     171, uint(QxtSerialDevice::BitMask),
     179, uint(QxtSerialDevice::FlowOff),
     187, uint(QxtSerialDevice::FlowRtsCts),
     198, uint(QxtSerialDevice::FlowXonXoff),
     210, uint(QxtSerialDevice::FlowMask),
     219, uint(QxtSerialDevice::ParityNone),
     230, uint(QxtSerialDevice::ParityOdd),
     240, uint(QxtSerialDevice::ParityEven),
     251, uint(QxtSerialDevice::ParityMark),
     262, uint(QxtSerialDevice::ParitySpace),
     274, uint(QxtSerialDevice::ParityMask),
     285, uint(QxtSerialDevice::Stop1),
     291, uint(QxtSerialDevice::Stop2),
     297, uint(QxtSerialDevice::StopMask),
     151, uint(QxtSerialDevice::Bit8),
     156, uint(QxtSerialDevice::Bit7),
     161, uint(QxtSerialDevice::Bit6),
     166, uint(QxtSerialDevice::Bit5),
     171, uint(QxtSerialDevice::BitMask),
     179, uint(QxtSerialDevice::FlowOff),
     187, uint(QxtSerialDevice::FlowRtsCts),
     198, uint(QxtSerialDevice::FlowXonXoff),
     210, uint(QxtSerialDevice::FlowMask),
     219, uint(QxtSerialDevice::ParityNone),
     230, uint(QxtSerialDevice::ParityOdd),
     240, uint(QxtSerialDevice::ParityEven),
     251, uint(QxtSerialDevice::ParityMark),
     262, uint(QxtSerialDevice::ParitySpace),
     274, uint(QxtSerialDevice::ParityMask),
     285, uint(QxtSerialDevice::Stop1),
     291, uint(QxtSerialDevice::Stop2),
     297, uint(QxtSerialDevice::StopMask),

       0        // eod
};

static const char qt_meta_stringdata_QxtSerialDevice[] = {
    "QxtSerialDevice\0BaudRate\0PortSetting\0"
    "PortSettings\0Baud110\0Baud300\0Baud600\0"
    "Baud1200\0Baud2400\0Baud4800\0Baud9600\0"
    "Baud19200\0Baud38400\0Baud57600\0Baud115200\0"
    "Bit8\0Bit7\0Bit6\0Bit5\0BitMask\0FlowOff\0"
    "FlowRtsCts\0FlowXonXoff\0FlowMask\0"
    "ParityNone\0ParityOdd\0ParityEven\0"
    "ParityMark\0ParitySpace\0ParityMask\0"
    "Stop1\0Stop2\0StopMask\0"
};

void QxtSerialDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtSerialDevice::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtSerialDevice::staticMetaObject = {
    { &QIODevice::staticMetaObject, qt_meta_stringdata_QxtSerialDevice,
      qt_meta_data_QxtSerialDevice, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSerialDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSerialDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSerialDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSerialDevice))
        return static_cast<void*>(const_cast< QxtSerialDevice*>(this));
    return QIODevice::qt_metacast(_clname);
}

int QxtSerialDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE

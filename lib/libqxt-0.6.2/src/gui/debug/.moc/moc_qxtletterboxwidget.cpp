/****************************************************************************
** Meta object code from reading C++ file 'qxtletterboxwidget.h'
**
** Created: Wed Jun 27 16:28:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qxtletterboxwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtletterboxwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtLetterBoxWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       3,   19, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,

 // properties: name, type, flags
      42,   35, 0x43095107,
      62,   58, 0x02095103,
      74,   69, 0x03095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtLetterBoxWidget[] = {
    "QxtLetterBoxWidget\0\0resizeWidget()\0"
    "QColor\0backgroundColor\0int\0margin\0"
    "uint\0resizeDelay\0"
};

void QxtLetterBoxWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QxtLetterBoxWidget *_t = static_cast<QxtLetterBoxWidget *>(_o);
        switch (_id) {
        case 0: _t->resizeWidget(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QxtLetterBoxWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QxtLetterBoxWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_QxtLetterBoxWidget,
      qt_meta_data_QxtLetterBoxWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtLetterBoxWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtLetterBoxWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtLetterBoxWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtLetterBoxWidget))
        return static_cast<void*>(const_cast< QxtLetterBoxWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int QxtLetterBoxWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = backgroundColor(); break;
        case 1: *reinterpret_cast< int*>(_v) = margin(); break;
        case 2: *reinterpret_cast< uint*>(_v) = resizeDelay(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: setMargin(*reinterpret_cast< int*>(_v)); break;
        case 2: setResizeDelay(*reinterpret_cast< uint*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        switch (_id) {
        case 0: clearBackgroundColor(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE

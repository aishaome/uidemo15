/****************************************************************************
** Meta object code from reading C++ file 'businessprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../api/businessprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'businessprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_businessProcessing_t {
    QByteArrayData data[8];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_businessProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_businessProcessing_t qt_meta_stringdata_businessProcessing = {
    {
QT_MOC_LITERAL(0, 0, 18), // "businessProcessing"
QT_MOC_LITERAL(1, 19, 5), // "Sleep"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "msec"
QT_MOC_LITERAL(4, 31, 8), // "editJson"
QT_MOC_LITERAL(5, 40, 9), // "bytearray"
QT_MOC_LITERAL(6, 50, 10), // "updateJson"
QT_MOC_LITERAL(7, 61, 10) // "exportJson"

    },
    "businessProcessing\0Sleep\0\0msec\0editJson\0"
    "bytearray\0updateJson\0exportJson"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_businessProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       6,    1,   40,    2, 0x08 /* Private */,
       7,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,

       0        // eod
};

void businessProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<businessProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Sleep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->editJson((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->updateJson((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->exportJson((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject businessProcessing::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_businessProcessing.data,
    qt_meta_data_businessProcessing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *businessProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *businessProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_businessProcessing.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int businessProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'jsonprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../api/jsonprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsonprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_jsonProcessing_t {
    QByteArrayData data[13];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_jsonProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_jsonProcessing_t qt_meta_stringdata_jsonProcessing = {
    {
QT_MOC_LITERAL(0, 0, 14), // "jsonProcessing"
QT_MOC_LITERAL(1, 15, 11), // "parsingJson"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "bytearray"
QT_MOC_LITERAL(4, 38, 15), // "postHttpRequest"
QT_MOC_LITERAL(5, 54, 3), // "url"
QT_MOC_LITERAL(6, 58, 3), // "obj"
QT_MOC_LITERAL(7, 62, 11), // "QByteArray&"
QT_MOC_LITERAL(8, 74, 11), // "requestData"
QT_MOC_LITERAL(9, 86, 15), // "requestFinished"
QT_MOC_LITERAL(10, 102, 14), // "QNetworkReply*"
QT_MOC_LITERAL(11, 117, 5), // "reply"
QT_MOC_LITERAL(12, 123, 14) // "uploadFileForm"

    },
    "jsonProcessing\0parsingJson\0\0bytearray\0"
    "postHttpRequest\0url\0obj\0QByteArray&\0"
    "requestData\0requestFinished\0QNetworkReply*\0"
    "reply\0uploadFileForm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_jsonProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   37,    2, 0x0a /* Public */,
       9,    1,   44,    2, 0x0a /* Public */,
      12,    3,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Bool, QMetaType::QUrl, QMetaType::QJsonObject, 0x80000000 | 7,    5,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Bool, QMetaType::QUrl, QMetaType::QJsonObject, 0x80000000 | 7,    5,    6,    8,

       0        // eod
};

void jsonProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<jsonProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->parsingJson((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: { bool _r = _t->postHttpRequest((*reinterpret_cast< QUrl(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->requestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: { bool _r = _t->uploadFileForm((*reinterpret_cast< QUrl(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (jsonProcessing::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&jsonProcessing::parsingJson)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject jsonProcessing::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_jsonProcessing.data,
    qt_meta_data_jsonProcessing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *jsonProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *jsonProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_jsonProcessing.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int jsonProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void jsonProcessing::parsingJson(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

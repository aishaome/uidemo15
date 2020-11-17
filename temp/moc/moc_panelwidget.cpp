/****************************************************************************
** Meta object code from reading C++ file 'panelwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../api/panelwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panelwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PanelWidget_t {
    QByteArrayData data[18];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelWidget_t qt_meta_stringdata_PanelWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PanelWidget"
QT_MOC_LITERAL(1, 12, 9), // "setWidget"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "QList<QWidget*>"
QT_MOC_LITERAL(4, 39, 7), // "widgets"
QT_MOC_LITERAL(5, 47, 11), // "columnCount"
QT_MOC_LITERAL(6, 59, 9), // "setMargin"
QT_MOC_LITERAL(7, 69, 4), // "left"
QT_MOC_LITERAL(8, 74, 3), // "top"
QT_MOC_LITERAL(9, 78, 5), // "right"
QT_MOC_LITERAL(10, 84, 6), // "bottom"
QT_MOC_LITERAL(11, 91, 6), // "margin"
QT_MOC_LITERAL(12, 98, 8), // "setSpace"
QT_MOC_LITERAL(13, 107, 5), // "space"
QT_MOC_LITERAL(14, 113, 12), // "setAutoWidth"
QT_MOC_LITERAL(15, 126, 9), // "autoWidth"
QT_MOC_LITERAL(16, 136, 13), // "setAutoHeight"
QT_MOC_LITERAL(17, 150, 10) // "autoHeight"

    },
    "PanelWidget\0setWidget\0\0QList<QWidget*>\0"
    "widgets\0columnCount\0setMargin\0left\0"
    "top\0right\0bottom\0margin\0setSpace\0space\0"
    "setAutoWidth\0autoWidth\0setAutoHeight\0"
    "autoHeight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       4,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x0a /* Public */,
       6,    4,   49,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
      12,    1,   61,    2, 0x0a /* Public */,
      14,    1,   64,    2, 0x0a /* Public */,
      16,    1,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   17,

 // properties: name, type, flags
      11, QMetaType::Int, 0x00095103,
      13, QMetaType::Int, 0x00095103,
      15, QMetaType::Bool, 0x00095103,
      17, QMetaType::Bool, 0x00095103,

       0        // eod
};

void PanelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PanelWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setWidget((*reinterpret_cast< QList<QWidget*>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setMargin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->setMargin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setAutoWidth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setAutoHeight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QWidget*> >(); break;
            }
            break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PanelWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getMargin(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getSpace(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->getAutoWidth(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->getAutoHeight(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PanelWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMargin(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setSpace(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setAutoWidth(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setAutoHeight(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PanelWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PanelWidget.data,
    qt_meta_data_PanelWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PanelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PanelWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PanelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

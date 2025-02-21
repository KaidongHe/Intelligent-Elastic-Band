/****************************************************************************
** Meta object code from reading C++ file 'ecgwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ecgwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecgwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EcgWidget_t {
    QByteArrayData data[24];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EcgWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EcgWidget_t qt_meta_stringdata_EcgWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "EcgWidget"
QT_MOC_LITERAL(1, 10, 20), // "HeartRatedataChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "newData"
QT_MOC_LITERAL(4, 40, 15), // "PVCcountChanged"
QT_MOC_LITERAL(5, 56, 22), // "ArrhythmiaLocationInfo"
QT_MOC_LITERAL(6, 79, 8), // "position"
QT_MOC_LITERAL(7, 88, 7), // "arrcode"
QT_MOC_LITERAL(8, 96, 17), // "RRIntervalChanged"
QT_MOC_LITERAL(9, 114, 7), // "newdata"
QT_MOC_LITERAL(10, 122, 19), // "ongainplusTriggered"
QT_MOC_LITERAL(11, 142, 18), // "ongainsubTriggered"
QT_MOC_LITERAL(12, 161, 17), // "onGain20Triggered"
QT_MOC_LITERAL(13, 179, 18), // "onSpeed25Triggered"
QT_MOC_LITERAL(14, 198, 18), // "onSpeed50Triggered"
QT_MOC_LITERAL(15, 217, 19), // "onSpeed100Triggered"
QT_MOC_LITERAL(16, 237, 23), // "onAntialiasingTriggered"
QT_MOC_LITERAL(17, 261, 19), // "onOptimizeTriggered"
QT_MOC_LITERAL(18, 281, 19), // "onDrawGridTriggered"
QT_MOC_LITERAL(19, 301, 20), // "onDrawPointTriggered"
QT_MOC_LITERAL(20, 322, 23), // "onPrintPreviewTriggered"
QT_MOC_LITERAL(21, 346, 16), // "printPreviewSlot"
QT_MOC_LITERAL(22, 363, 9), // "QPrinter*"
QT_MOC_LITERAL(23, 373, 7) // "printer"

    },
    "EcgWidget\0HeartRatedataChanged\0\0newData\0"
    "PVCcountChanged\0ArrhythmiaLocationInfo\0"
    "position\0arrcode\0RRIntervalChanged\0"
    "newdata\0ongainplusTriggered\0"
    "ongainsubTriggered\0onGain20Triggered\0"
    "onSpeed25Triggered\0onSpeed50Triggered\0"
    "onSpeed100Triggered\0onAntialiasingTriggered\0"
    "onOptimizeTriggered\0onDrawGridTriggered\0"
    "onDrawPointTriggered\0onPrintPreviewTriggered\0"
    "printPreviewSlot\0QPrinter*\0printer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EcgWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    2,  100,    2, 0x06 /* Public */,
       8,    1,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  108,    2, 0x0a /* Public */,
      11,    0,  109,    2, 0x0a /* Public */,
      12,    0,  110,    2, 0x0a /* Public */,
      13,    0,  111,    2, 0x0a /* Public */,
      14,    0,  112,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    0,  115,    2, 0x0a /* Public */,
      18,    0,  116,    2, 0x0a /* Public */,
      19,    0,  117,    2, 0x0a /* Public */,
      20,    0,  118,    2, 0x0a /* Public */,
      21,    1,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,

       0        // eod
};

void EcgWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EcgWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->HeartRatedataChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->PVCcountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ArrhythmiaLocationInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->RRIntervalChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ongainplusTriggered(); break;
        case 5: _t->ongainsubTriggered(); break;
        case 6: _t->onGain20Triggered(); break;
        case 7: _t->onSpeed25Triggered(); break;
        case 8: _t->onSpeed50Triggered(); break;
        case 9: _t->onSpeed100Triggered(); break;
        case 10: _t->onAntialiasingTriggered(); break;
        case 11: _t->onOptimizeTriggered(); break;
        case 12: _t->onDrawGridTriggered(); break;
        case 13: _t->onDrawPointTriggered(); break;
        case 14: _t->onPrintPreviewTriggered(); break;
        case 15: _t->printPreviewSlot((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EcgWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EcgWidget::HeartRatedataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EcgWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EcgWidget::PVCcountChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EcgWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EcgWidget::ArrhythmiaLocationInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EcgWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EcgWidget::RRIntervalChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EcgWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EcgWidget.data,
    qt_meta_data_EcgWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EcgWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EcgWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EcgWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EcgWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void EcgWidget::HeartRatedataChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EcgWidget::PVCcountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EcgWidget::ArrhythmiaLocationInfo(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void EcgWidget::RRIntervalChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

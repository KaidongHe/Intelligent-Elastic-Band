/****************************************************************************
** Meta object code from reading C++ file 'Common_wave.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Common_wave.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Common_wave.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CommonWave_t {
    QByteArrayData data[16];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CommonWave_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CommonWave_t qt_meta_stringdata_CommonWave = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CommonWave"
QT_MOC_LITERAL(1, 11, 19), // "ongainplusTriggered"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 18), // "ongainsubTriggered"
QT_MOC_LITERAL(4, 51, 17), // "onGain20Triggered"
QT_MOC_LITERAL(5, 69, 18), // "onSpeed25Triggered"
QT_MOC_LITERAL(6, 88, 18), // "onSpeed50Triggered"
QT_MOC_LITERAL(7, 107, 19), // "onSpeed100Triggered"
QT_MOC_LITERAL(8, 127, 23), // "onAntialiasingTriggered"
QT_MOC_LITERAL(9, 151, 19), // "onOptimizeTriggered"
QT_MOC_LITERAL(10, 171, 19), // "onDrawGridTriggered"
QT_MOC_LITERAL(11, 191, 20), // "onDrawPointTriggered"
QT_MOC_LITERAL(12, 212, 23), // "onPrintPreviewTriggered"
QT_MOC_LITERAL(13, 236, 16), // "printPreviewSlot"
QT_MOC_LITERAL(14, 253, 9), // "QPrinter*"
QT_MOC_LITERAL(15, 263, 7) // "printer"

    },
    "CommonWave\0ongainplusTriggered\0\0"
    "ongainsubTriggered\0onGain20Triggered\0"
    "onSpeed25Triggered\0onSpeed50Triggered\0"
    "onSpeed100Triggered\0onAntialiasingTriggered\0"
    "onOptimizeTriggered\0onDrawGridTriggered\0"
    "onDrawPointTriggered\0onPrintPreviewTriggered\0"
    "printPreviewSlot\0QPrinter*\0printer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CommonWave[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    1,   85,    2, 0x0a /* Public */,

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
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void CommonWave::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommonWave *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ongainplusTriggered(); break;
        case 1: _t->ongainsubTriggered(); break;
        case 2: _t->onGain20Triggered(); break;
        case 3: _t->onSpeed25Triggered(); break;
        case 4: _t->onSpeed50Triggered(); break;
        case 5: _t->onSpeed100Triggered(); break;
        case 6: _t->onAntialiasingTriggered(); break;
        case 7: _t->onOptimizeTriggered(); break;
        case 8: _t->onDrawGridTriggered(); break;
        case 9: _t->onDrawPointTriggered(); break;
        case 10: _t->onPrintPreviewTriggered(); break;
        case 11: _t->printPreviewSlot((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CommonWave::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CommonWave.data,
    qt_meta_data_CommonWave,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CommonWave::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommonWave::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommonWave.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CommonWave::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'dataprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../dataprocessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QQueue>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataProcessor_t {
    QByteArrayData data[23];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataProcessor_t qt_meta_stringdata_DataProcessor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DataProcessor"
QT_MOC_LITERAL(1, 14, 13), // "dataProcessed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "ECG_Data"
QT_MOC_LITERAL(4, 38, 9), // "RESP_Data"
QT_MOC_LITERAL(5, 48, 7), // "AX_Data"
QT_MOC_LITERAL(6, 56, 7), // "AY_Data"
QT_MOC_LITERAL(7, 64, 7), // "AZ_Data"
QT_MOC_LITERAL(8, 72, 14), // "accelProcessor"
QT_MOC_LITERAL(9, 87, 13), // "QQueue<float>"
QT_MOC_LITERAL(10, 101, 7), // "axQueue"
QT_MOC_LITERAL(11, 109, 7), // "ayQueue"
QT_MOC_LITERAL(12, 117, 7), // "azQueue"
QT_MOC_LITERAL(13, 125, 17), // "ecg_respProcessed"
QT_MOC_LITERAL(14, 143, 13), // "trans_ecgBuff"
QT_MOC_LITERAL(15, 157, 14), // "trans_respBuff"
QT_MOC_LITERAL(16, 172, 8), // "trans_HR"
QT_MOC_LITERAL(17, 181, 9), // "heartRate"
QT_MOC_LITERAL(18, 191, 12), // "fallDetected"
QT_MOC_LITERAL(19, 204, 18), // "ADS1292R_ADCtoData"
QT_MOC_LITERAL(20, 223, 8), // "Type_ADC"
QT_MOC_LITERAL(21, 232, 17), // "MPU6050_ADCtoData"
QT_MOC_LITERAL(22, 250, 6) // "Ax_ADC"

    },
    "DataProcessor\0dataProcessed\0\0ECG_Data\0"
    "RESP_Data\0AX_Data\0AY_Data\0AZ_Data\0"
    "accelProcessor\0QQueue<float>\0axQueue\0"
    "ayQueue\0azQueue\0ecg_respProcessed\0"
    "trans_ecgBuff\0trans_respBuff\0trans_HR\0"
    "heartRate\0fallDetected\0ADS1292R_ADCtoData\0"
    "Type_ADC\0MPU6050_ADCtoData\0Ax_ADC"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   59,    2, 0x06 /* Public */,
       8,    3,   70,    2, 0x06 /* Public */,
      13,    2,   77,    2, 0x06 /* Public */,
      14,    0,   82,    2, 0x06 /* Public */,
      15,    0,   83,    2, 0x06 /* Public */,
      16,    1,   84,    2, 0x06 /* Public */,
      18,    0,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,   88,    2, 0x0a /* Public */,
      21,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 9,   10,   11,   12,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int, QMetaType::Int,   20,
    QMetaType::Float, QMetaType::Short,   22,

       0        // eod
};

void DataProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataProcessed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 1: _t->accelProcessor((*reinterpret_cast< QQueue<float>(*)>(_a[1])),(*reinterpret_cast< QQueue<float>(*)>(_a[2])),(*reinterpret_cast< QQueue<float>(*)>(_a[3]))); break;
        case 2: _t->ecg_respProcessed((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->trans_ecgBuff(); break;
        case 4: _t->trans_respBuff(); break;
        case 5: _t->trans_HR((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->fallDetected(); break;
        case 7: { int _r = _t->ADS1292R_ADCtoData((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { float _r = _t->MPU6050_ADCtoData((*reinterpret_cast< short(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQueue<float> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataProcessor::*)(int , float , float , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::dataProcessed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(QQueue<float> , QQueue<float> , QQueue<float> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::accelProcessor)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::ecg_respProcessed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::trans_ecgBuff)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::trans_respBuff)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::trans_HR)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::fallDetected)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataProcessor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DataProcessor.data,
    qt_meta_data_DataProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DataProcessor::dataProcessed(int _t1, float _t2, float _t3, float _t4, float _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataProcessor::accelProcessor(QQueue<float> _t1, QQueue<float> _t2, QQueue<float> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataProcessor::ecg_respProcessed(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataProcessor::trans_ecgBuff()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DataProcessor::trans_respBuff()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DataProcessor::trans_HR(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DataProcessor::fallDetected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'bleinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../bleinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bleinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceInfo_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceInfo_t qt_meta_stringdata_DeviceInfo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DeviceInfo"
QT_MOC_LITERAL(1, 11, 13), // "deviceChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "deviceName"
QT_MOC_LITERAL(4, 37, 13) // "deviceAddress"

    },
    "DeviceInfo\0deviceChanged\0\0deviceName\0"
    "deviceAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       2,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00495001,
       4, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       0,

       0        // eod
};

void DeviceInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deviceChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInfo::deviceChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceInfo *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getAddress(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DeviceInfo::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DeviceInfo.data,
    qt_meta_data_DeviceInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceInfo::deviceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_BLEInterface_t {
    QByteArrayData data[40];
    char stringdata0[640];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BLEInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BLEInterface_t qt_meta_stringdata_BLEInterface = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BLEInterface"
QT_MOC_LITERAL(1, 13, 17), // "statusInfoChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 4), // "info"
QT_MOC_LITERAL(4, 37, 6), // "isGood"
QT_MOC_LITERAL(5, 44, 12), // "dataReceived"
QT_MOC_LITERAL(6, 57, 4), // "data"
QT_MOC_LITERAL(7, 62, 16), // "connectedChanged"
QT_MOC_LITERAL(8, 79, 9), // "connected"
QT_MOC_LITERAL(9, 89, 21), // "currentServiceChanged"
QT_MOC_LITERAL(10, 111, 14), // "currentService"
QT_MOC_LITERAL(11, 126, 17), // "setCurrentService"
QT_MOC_LITERAL(12, 144, 9), // "addDevice"
QT_MOC_LITERAL(13, 154, 20), // "QBluetoothDeviceInfo"
QT_MOC_LITERAL(14, 175, 14), // "onScanFinished"
QT_MOC_LITERAL(15, 190, 17), // "onDeviceScanError"
QT_MOC_LITERAL(16, 208, 37), // "QBluetoothDeviceDiscoveryAgen..."
QT_MOC_LITERAL(17, 246, 19), // "onServiceDiscovered"
QT_MOC_LITERAL(18, 266, 14), // "QBluetoothUuid"
QT_MOC_LITERAL(19, 281, 17), // "onServiceScanDone"
QT_MOC_LITERAL(20, 299, 17), // "onControllerError"
QT_MOC_LITERAL(21, 317, 27), // "QLowEnergyController::Error"
QT_MOC_LITERAL(22, 345, 17), // "onDeviceConnected"
QT_MOC_LITERAL(23, 363, 20), // "onDeviceDisconnected"
QT_MOC_LITERAL(24, 384, 21), // "onServiceStateChanged"
QT_MOC_LITERAL(25, 406, 31), // "QLowEnergyService::ServiceState"
QT_MOC_LITERAL(26, 438, 1), // "s"
QT_MOC_LITERAL(27, 440, 23), // "onCharacteristicChanged"
QT_MOC_LITERAL(28, 464, 24), // "QLowEnergyCharacteristic"
QT_MOC_LITERAL(29, 489, 1), // "c"
QT_MOC_LITERAL(30, 491, 5), // "value"
QT_MOC_LITERAL(31, 497, 12), // "serviceError"
QT_MOC_LITERAL(32, 510, 31), // "QLowEnergyService::ServiceError"
QT_MOC_LITERAL(33, 542, 1), // "e"
QT_MOC_LITERAL(34, 544, 4), // "read"
QT_MOC_LITERAL(35, 549, 20), // "onCharacteristicRead"
QT_MOC_LITERAL(36, 570, 21), // "onCharacteristicWrite"
QT_MOC_LITERAL(37, 592, 21), // "update_currentService"
QT_MOC_LITERAL(38, 614, 13), // "currentSerice"
QT_MOC_LITERAL(39, 628, 11) // "scanDevices"

    },
    "BLEInterface\0statusInfoChanged\0\0info\0"
    "isGood\0dataReceived\0data\0connectedChanged\0"
    "connected\0currentServiceChanged\0"
    "currentService\0setCurrentService\0"
    "addDevice\0QBluetoothDeviceInfo\0"
    "onScanFinished\0onDeviceScanError\0"
    "QBluetoothDeviceDiscoveryAgent::Error\0"
    "onServiceDiscovered\0QBluetoothUuid\0"
    "onServiceScanDone\0onControllerError\0"
    "QLowEnergyController::Error\0"
    "onDeviceConnected\0onDeviceDisconnected\0"
    "onServiceStateChanged\0"
    "QLowEnergyService::ServiceState\0s\0"
    "onCharacteristicChanged\0"
    "QLowEnergyCharacteristic\0c\0value\0"
    "serviceError\0QLowEnergyService::ServiceError\0"
    "e\0read\0onCharacteristicRead\0"
    "onCharacteristicWrite\0update_currentService\0"
    "currentSerice\0scanDevices"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BLEInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       2,  178, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  119,    2, 0x06 /* Public */,
       5,    1,  124,    2, 0x06 /* Public */,
       7,    1,  127,    2, 0x06 /* Public */,
       9,    1,  130,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  133,    2, 0x0a /* Public */,
      12,    1,  136,    2, 0x08 /* Private */,
      14,    0,  139,    2, 0x08 /* Private */,
      15,    1,  140,    2, 0x08 /* Private */,
      17,    1,  143,    2, 0x08 /* Private */,
      19,    0,  146,    2, 0x08 /* Private */,
      20,    1,  147,    2, 0x08 /* Private */,
      22,    0,  150,    2, 0x08 /* Private */,
      23,    0,  151,    2, 0x08 /* Private */,
      24,    1,  152,    2, 0x08 /* Private */,
      27,    2,  155,    2, 0x08 /* Private */,
      31,    1,  160,    2, 0x08 /* Private */,
      34,    0,  163,    2, 0x08 /* Private */,
      35,    2,  164,    2, 0x08 /* Private */,
      36,    2,  169,    2, 0x08 /* Private */,
      37,    1,  174,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      39,    0,  177,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Int,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, 0x80000000 | 28, QMetaType::QByteArray,   29,   30,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28, QMetaType::QByteArray,   29,   30,
    QMetaType::Void, 0x80000000 | 28, QMetaType::QByteArray,   29,   30,
    QMetaType::Void, QMetaType::Int,   38,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Bool, 0x00495001,
      10, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       2,
       3,

       0        // eod
};

void BLEInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BLEInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusInfoChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->dataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->connectedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->currentServiceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setCurrentService((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->addDevice((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 6: _t->onScanFinished(); break;
        case 7: _t->onDeviceScanError((*reinterpret_cast< QBluetoothDeviceDiscoveryAgent::Error(*)>(_a[1]))); break;
        case 8: _t->onServiceDiscovered((*reinterpret_cast< const QBluetoothUuid(*)>(_a[1]))); break;
        case 9: _t->onServiceScanDone(); break;
        case 10: _t->onControllerError((*reinterpret_cast< QLowEnergyController::Error(*)>(_a[1]))); break;
        case 11: _t->onDeviceConnected(); break;
        case 12: _t->onDeviceDisconnected(); break;
        case 13: _t->onServiceStateChanged((*reinterpret_cast< QLowEnergyService::ServiceState(*)>(_a[1]))); break;
        case 14: _t->onCharacteristicChanged((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 15: _t->serviceError((*reinterpret_cast< QLowEnergyService::ServiceError(*)>(_a[1]))); break;
        case 16: _t->read(); break;
        case 17: _t->onCharacteristicRead((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 18: _t->onCharacteristicWrite((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 19: _t->update_currentService((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->scanDevices(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothUuid >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyController::Error >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceState >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceError >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BLEInterface::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::statusInfoChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::dataReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::connectedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::currentServiceChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<BLEInterface *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isConnected(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->currentService(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BLEInterface *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setCurrentService(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject BLEInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BLEInterface.data,
    qt_meta_data_BLEInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BLEInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BLEInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BLEInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BLEInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BLEInterface::statusInfoChanged(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BLEInterface::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BLEInterface::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BLEInterface::currentServiceChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

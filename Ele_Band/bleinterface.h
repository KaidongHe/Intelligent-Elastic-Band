/**
*****************************************************************************
*  Copyright (C), 仅供实验室内部使用，未经许可禁止外传
*
*  @file    bleinterface.h
*  @brief   QT_BLE
*           1. 实现QT中的BLE(低功耗蓝牙)搜索,连接,以及数据传输
*           2. 通过QT中的信号与槽机制,供其他文件调用数据
*
*  @author  kdh
*  @date    2024-05-20
*  @version V1.0.0 2024-05-20
*----------------------------------------------------------------------------
*  @note 历史版本   修改人员        修改日期        修改内容
*  @note v1.0      kdh            2024-05-20     创建
*
*****************************************************************************
*/
#ifndef BLEINTERFACE_H
#define BLEINTERFACE_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QTimer>


#include "lib-qt-qml-tricks/src/qqmlhelpers.h"

// 定义读取间隔时间和数据块大小
#define READ_INTERVAL_MS 3000
#define CHUNK_SIZE 20

// 设备信息类，用于描述蓝牙设备的信息
class DeviceInfo: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ getName NOTIFY deviceChanged)
    Q_PROPERTY(QString deviceAddress READ getAddress NOTIFY deviceChanged)
public:
    DeviceInfo(const QBluetoothDeviceInfo &device); // 构造函数，接受一个蓝牙设备信息参数
    void setDevice(const QBluetoothDeviceInfo &device); // 设置蓝牙设备信息
    QString getName() const { return m_device.name(); } // 获取设备名称
    QString getAddress() const; // 获取设备地址
    QBluetoothDeviceInfo getDevice() const; // 获取设备信息

signals:
    void deviceChanged(); // 设备信息变化信号，用于通知属性改变

private:
    QBluetoothDeviceInfo m_device; // 存储蓝牙设备信息
};

// 蓝牙接口类，用于管理蓝牙连接和通信
class BLEInterface : public QObject
{
    Q_OBJECT

    // 属性定义
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged) // 是否连接属性
    Q_PROPERTY(int currentService READ currentService WRITE setCurrentService NOTIFY currentServiceChanged) // 当前服务属性
    QML_WRITABLE_PROPERTY(int, currentDevice) // 可写设备属性
    QML_READONLY_PROPERTY(QStringList, devicesNames) // 只读设备名称属性
    QML_READONLY_PROPERTY(QStringList, services) // 只读服务属性
public:
    explicit BLEInterface(QObject *parent = 0); // 构造函数
    ~BLEInterface(); // 析构函数

    void connectCurrentDevice(); // 连接当前设备
    void disconnectDevice(); // 断开设备连接
    Q_INVOKABLE void scanDevices(); // 扫描设备
    void write(const QByteArray& data); // 写入数据

    // 获取是否连接状态
    bool isConnected() const
    {
        return m_connected;
    }

    // 获取当前服务
    int currentService() const
    {
        return m_currentService;
    }

public slots:
    // 设置当前服务
    void setCurrentService(int currentService)
    {
        if (m_currentService == currentService)
            return;
        update_currentService(currentService);
        m_currentService = currentService;
        emit currentServiceChanged(currentService);
    }

signals:
    void statusInfoChanged(QString info, bool isGood); // 状态信息改变信号
    void dataReceived(const QByteArray &data); // 数据接收信号
    void connectedChanged(bool connected); // 连接状态改变信号

    void currentServiceChanged(int currentService); // 当前服务改变信号

private slots:
    // 设备扫描相关槽函数
    void addDevice(const QBluetoothDeviceInfo&);
    void onScanFinished();
    void onDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

    // 控制器相关槽函数
    void onServiceDiscovered(const QBluetoothUuid &);
    void onServiceScanDone();
    void onControllerError(QLowEnergyController::Error);
    void onDeviceConnected();
    void onDeviceDisconnected();

    // 服务相关槽函数
    void onServiceStateChanged(QLowEnergyService::ServiceState s);
    void onCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void serviceError(QLowEnergyService::ServiceError e);

    // 数据读取相关槽函数
    void read();
    void onCharacteristicRead(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void onCharacteristicWrite(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void update_currentService(int currentSerice);

private:
    inline void waitForWrite();// 等待写入函数
    void update_connected(bool connected){  // 更新连接状态函数
        if(connected != m_connected){
            m_connected = connected;
            emit connectedChanged(connected);
        }
    }

    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent; // 设备发现代理
    QLowEnergyDescriptor m_notificationDesc; // 低功耗蓝牙描述符
    QLowEnergyController *m_control; // 低功耗蓝牙控制器
    QList<QBluetoothUuid> m_servicesUuid; // 服务UUID列表
    QLowEnergyService *m_service; // 低功耗蓝牙服务
    QLowEnergyCharacteristic m_readCharacteristic; // 读特征
    QLowEnergyCharacteristic m_writeCharacteristic; // 写特征
    QList<DeviceInfo*> m_devices; // 设备信息列表
//    bool m_foundService;
    QTimer *m_readTimer; // 读取定时器
    bool m_connected; // 连接状态
    void searchCharacteristic();
    int m_currentService; // 当前服务索引
    QLowEnergyService::WriteMode m_writeMode; // 写入模式
};

#endif // BLEINTERFACE_H

/**
*****************************************************************************
*  Copyright (C), 仅供实验室内部使用，未经许可禁止外传
*
*  @file    bleinterface.cpp
*  @brief   QT_BLE
*           1. 实现QT中的BLE(低功耗蓝牙)搜索,连接,以及数据传输
*           2. 通过QT中的信号与槽机制,供其他文件调用数据
*
*  @author  kdh
*  @date    2024-05-20
*  @version V1.1.0 2024-05-20
*----------------------------------------------------------------------------
*  @note 历史版本   修改人员        修改日期        修改内容
*  @note v1.0.0      kdh           2024-05-20      创建
*  @note v1.1.0      kdh           2024-05-21      实现基本功能
*****************************************************************************
*/

#include "bleinterface.h"
#include <QDebug>
#include <QEventLoop>

// DeviceInfo类的构造函数，初始化设备信息
DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo &info):
    QObject(), m_device(info)
{
}

// 获取设备信息
QBluetoothDeviceInfo DeviceInfo::getDevice() const
{
    return m_device;
}

// 获取设备地址，针对macOS系统进行特殊处理
QString DeviceInfo::getAddress() const
{
#ifdef Q_OS_MAC
    // workaround for Core Bluetooth:
    return m_device.deviceUuid().toString();
#else
    return m_device.address().toString();
#endif
}

// 设置设备信息，并发出设备变更信号
void DeviceInfo::setDevice(const QBluetoothDeviceInfo &device)
{
    m_device = device;
    emit deviceChanged();
}

// BLEInterface类的构造函数，初始化成员变量并连接信号和槽
BLEInterface::BLEInterface(QObject *parent) : QObject(parent),
    m_currentDevice(0),
    m_control(0),
    m_service(0),
    m_readTimer(0),
    m_connected(false),
    m_currentService(0)
{
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(30000);    //设置超时时间

    connect(m_deviceDiscoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(addDevice(const QBluetoothDeviceInfo&)));
    connect(m_deviceDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(onDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(m_deviceDiscoveryAgent, SIGNAL(finished()), this, SLOT(onScanFinished()));
}

// BLEInterface类的析构函数，清理设备列表
BLEInterface::~BLEInterface()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

// 扫描BLE设备
void BLEInterface::scanDevices()
{
    m_devicesNames.clear();
    qDeleteAll(m_devices);
    m_devices.clear();
//    emit devicesNamesChanged(m_devicesNames);
//    m_deviceDiscoveryAgent->start();

    //仅搜索低功耗蓝牙 by antis 20240521
    m_deviceDiscoveryAgent->start();
//    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    //emit statusInfoChanged("Scanning for devices...", true);
    qDebug()<<"Scanning for devices...";
}

// 读取BLE特征值
void BLEInterface::read(){
    if(m_service && m_readCharacteristic.isValid())
        m_service->readCharacteristic(m_readCharacteristic);
}

// 等待写操作完成
void BLEInterface::waitForWrite() {
    QEventLoop loop;
    connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),
            &loop, SLOT(quit()));
    loop.exec();
}

// 写入数据到BLE特征值
void BLEInterface::write(const QByteArray &data)
{
    qDebug() << "BLEInterface::write: " << data;
    if(m_service && m_writeCharacteristic.isValid()){
        if(data.length() > CHUNK_SIZE){
            int sentBytes = 0;
            while (sentBytes < data.length()) {
                m_service->writeCharacteristic(m_writeCharacteristic,
                                               data.mid(sentBytes, CHUNK_SIZE),
                                               m_writeMode);
                sentBytes += CHUNK_SIZE;
                if(m_writeMode == QLowEnergyService::WriteWithResponse){
                    waitForWrite();
                    if(m_service->error() != QLowEnergyService::NoError)
                        return;
                }
            }

        }
        else
            m_service->writeCharacteristic(m_writeCharacteristic, data, m_writeMode);
    }
}

// 添加发现的设备到设备列表
void BLEInterface::addDevice(const QBluetoothDeviceInfo &device)
{
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        qWarning() << "Discovered LE Device name: " << device.name() << " Address: "
                   << device.address().toString();
        m_devicesNames.append(device.name());
        DeviceInfo *dev = new DeviceInfo(device);
        m_devices.append(dev);
//        emit devicesNamesChanged(m_devicesNames);
//        emit statusInfoChanged("Low Energy device found. Scanning for more...", true);
        qDebug()<<"Low Energy device found. Scanning for more...";
    }
    //...
}

// 扫描完成时的槽函数
void BLEInterface::onScanFinished()
{
    if (m_devicesNames.size() == 0)
    {
//        emit statusInfoChanged("No Low Energy devices found", false);
        qDebug()<<"No Low Energy devices found";
    }

    qDebug() <<  "Scan Finished";
}

// 设备扫描出错时的槽函数
void BLEInterface::onDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        emit statusInfoChanged("The Bluetooth adaptor is powered off, power it on before doing discovery.", false);
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        emit statusInfoChanged("Writing or reading from the device resulted in an error.", false);
    else
        emit statusInfoChanged("An unknown error has occurred.", false);
}

// 连接当前选中的设备
void BLEInterface::connectCurrentDevice()
{
    if(m_devices.isEmpty())
        return;

    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = 0;

    }
    m_control = new QLowEnergyController(m_devices[ m_currentDevice]->getDevice(), this);
    connect(m_control, SIGNAL(serviceDiscovered(QBluetoothUuid)),
            this, SLOT(onServiceDiscovered(QBluetoothUuid)));
    connect(m_control, SIGNAL(discoveryFinished()),
            this, SLOT(onServiceScanDone()));
    connect(m_control, SIGNAL(error(QLowEnergyController::Error)),
            this, SLOT(onControllerError(QLowEnergyController::Error)));
    connect(m_control, SIGNAL(connected()),
            this, SLOT(onDeviceConnected()));
    connect(m_control, SIGNAL(disconnected()),
            this, SLOT(onDeviceDisconnected()));

    m_control->connectToDevice();
}

// 设备连接成功时的槽函数
void BLEInterface::onDeviceConnected()
{
    m_servicesUuid.clear();
    m_services.clear();
    //setCurrentService(-1);
    emit servicesChanged(m_services);
    m_control->discoverServices(); //连接完成后立即搜索服务 by antis 20240521
}

// 设备断开连接时的槽函数
void BLEInterface::onDeviceDisconnected()
{
    update_connected(false);
    emit statusInfoChanged("Service disconnected", false);
    qWarning() << "Remote device disconnected";
}

// 服务发现时的槽函数
void BLEInterface::onServiceDiscovered(const QBluetoothUuid &gatt)
{
    Q_UNUSED(gatt)
    // 暂时用不上 by antis 20240521
    // emit statusInfoChanged("Service discovered. Waiting for service scan to be done...", true);
    qDebug() << "one more Service discovered. Waiting for service scan to be done...";
}

// 服务扫描完成时的槽函数
void BLEInterface::onServiceScanDone()
{
    m_servicesUuid = m_control->services();
    if(m_servicesUuid.isEmpty())
    {
        //emit statusInfoChanged("Can't find any services.", true);
        qDebug() << "Can't find any services.";
    }
    else{
        m_services.clear();
        foreach (auto uuid, m_servicesUuid)
            m_services.append(uuid.toString());
        emit servicesChanged(m_services);
        m_currentService = -1;// to force call update_currentService(once)
        //setCurrentService(0); //by antis 有必要，不然有卡死风险
        //emit statusInfoChanged("All services discovered.", true);
        qDebug()<<"All services discovered.";
    }
}

// 断开设备连接
void BLEInterface::disconnectDevice()
{
    m_readTimer->deleteLater();
    m_readTimer = NULL;

    if (m_devices.isEmpty()) {
        return;
    }

    //disable notifications
    // 禁用通知
    if (m_notificationDesc.isValid() && m_service) {
        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    } else {
        m_control->disconnectFromDevice();
        delete m_service;
        m_service = 0;
    }
}

// 控制器出错时的槽函数
void BLEInterface::onControllerError(QLowEnergyController::Error error)
{
    emit statusInfoChanged("Cannot connect to remote device.", false);
    qWarning() << "Controller Error:" << error;
}

// 特征值改变时的槽函数
void BLEInterface::onCharacteristicChanged(const QLowEnergyCharacteristic &c,
                                           const QByteArray &value)
{
    Q_UNUSED(c)
     //qDebug() << "Characteristic Changed: " << value;  //by antis 20240521 实际数据
    emit dataReceived(value);
}
// 特征值写入时的槽函数
void BLEInterface::onCharacteristicWrite(const QLowEnergyCharacteristic &c,
                                          const QByteArray &value)
{
    Q_UNUSED(c)
    qDebug() << "Characteristic Written: " << value;
}

// 更新当前服务
void BLEInterface::update_currentService(int indx)
{
    delete m_service;
    m_service = 0;

    if (indx >= 0 && m_servicesUuid.count() > indx) {
        m_service = m_control->createServiceObject(
                    m_servicesUuid.at(indx), this);
        qDebug()<< m_servicesUuid.at(indx);
    }

    if (!m_service) {
        emit statusInfoChanged("Service not found.", false);
        return;
    }

    connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(onServiceStateChanged(QLowEnergyService::ServiceState)));
    connect(m_service, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
            this, SLOT(onCharacteristicChanged(QLowEnergyCharacteristic,QByteArray)));
    connect(m_service, SIGNAL(characteristicRead(QLowEnergyCharacteristic,QByteArray)),
            this, SLOT(onCharacteristicRead(QLowEnergyCharacteristic,QByteArray)));
    connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),
            this, SLOT(onCharacteristicWrite(QLowEnergyCharacteristic,QByteArray)));
    connect(m_service, SIGNAL(error(QLowEnergyService::ServiceError)),
            this, SLOT(serviceError(QLowEnergyService::ServiceError)));

    if(m_service->state() == QLowEnergyService::DiscoveryRequired) {
        emit statusInfoChanged("Connecting to service...", true);
        m_service->discoverDetails();
    }
//    else
//        searchCharacteristic();
}

/**
 * @brief 处理特征读取完成的槽函数
 * @param c 读取的特征
 * @param value 读取到的值
 * @details 将读取到的值发射出去
 */
void BLEInterface::onCharacteristicRead(const QLowEnergyCharacteristic &c,
                                        const QByteArray &value){
    Q_UNUSED(c)
    //qDebug() << "Characteristic Read: " << value;
    emit dataReceived(value);
}

/**
 * @brief 搜索服务特征
 * @details 根据服务对象搜索所有特征，并根据特征属性进行相应处理，如设置写特征、读特征等
 */
void BLEInterface::searchCharacteristic(){
    if(m_service){
        foreach (QLowEnergyCharacteristic c, m_service->characteristics()) {
            if(c.isValid()){
                if (c.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
                    c.properties() & QLowEnergyCharacteristic::Write) {
                    m_writeCharacteristic = c;
                    update_connected(true);
                    if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse)
                        m_writeMode = QLowEnergyService::WriteWithoutResponse;
                    else
                        m_writeMode = QLowEnergyService::WriteWithResponse;

                }
                if (c.properties() & QLowEnergyCharacteristic::Read) {
                    m_readCharacteristic = c;
                    if(!m_readTimer){
                        m_readTimer = new QTimer(this);
                        connect(m_readTimer, &QTimer::timeout, this, &BLEInterface::read);
                        m_readTimer->start(READ_INTERVAL_MS);
                    }
                }
                m_notificationDesc = c.descriptor(
                            QBluetoothUuid::ClientCharacteristicConfiguration);
                if (m_notificationDesc.isValid()) {
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                }
            }
        }
    }
}

/**
 * @brief 处理服务状态改变的槽函数
 * @param s 服务状态
 * @details 当服务状态为已发现时，搜索服务特征
 */
void BLEInterface::onServiceStateChanged(QLowEnergyService::ServiceState s)
{
    qDebug() << "serviceStateChanged, state: " << s;
    if (s == QLowEnergyService::ServiceDiscovered) {
        searchCharacteristic();
    }
}

/**
 * @brief 处理服务错误的槽函数
 * @param e 服务错误
 * @details 输出服务错误信息
 */
void BLEInterface::serviceError(QLowEnergyService::ServiceError e)
{
    qWarning() << "Service error:" << e;
}

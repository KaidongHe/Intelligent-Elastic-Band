#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QDebug>
#include "QListView"
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QDir>

#include <algorithm>
#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>

#include "ui_Infowindow.h"

#include "qcustomplot.h"

#include <dataprocessor.h>
#include "bleinterface.h" // 引入 BLEInterface 类的头文件
#include "HC05.h"
#include "SimpleCircularBuffer.h"
#include <circularprogessbar.h>
#include <vProgressBars.h>
#include <common.h>


// 设置定时器的周期为 20 毫秒，20ms = 50Hz (1000ms / 50) 0.04074
#define TIMER_TIMEOUT   1
//采样率50HZ - Dt 0.02  采样率87HZ 0.0115607 采样率41Hz 0.02439
#define Dt 0.04074

struct SerialPortSettings {
/*public :*/
    QString portName;
    QString baud;
    QString dataBits;
    QString checkBits;
    QString stopBits;
};


namespace Ui {
class infoWindow;
}

class infoWindow : public QWidget
{
    Q_OBJECT // 使用 Qt 的宏来支持信号与槽机制

public:
     //test ble
    int isfirst = 0;
    QVector<float> Data_floatVector; //数据要清除，否侧占用内存过大
    QVector<float> ALL_Velocity_floatVector; //数据要清除，否侧占用内存过大
    QVector<float> Filter_floatVector; //滤波数据堆栈
    const int dataHistoryMaxSize = 500; //设置最大数据容量为500

    explicit infoWindow(QWidget *parent = nullptr);
    ~infoWindow() override;

    void initConfig();
    void serialThreadStart();
    void slot_receiveSerialPortData();
    void receiveSerialPortData();
    void receiveBleData();
    void receiveLinkZillData();

    ///// 均值滤波相关  /////
    void addFilterData(QVector<float>& ArgFilter_floatVector,float newData,int AccLength);
    float Average(const QVector<float>& vec);

    ///// 从文件读取数据  /////
    void ReadDatafromFile();

    ///// 速度平均值相关 /////
    void AverPosSpeed_RateofSpeedLoss(float newData);
    void AverNegSpeed_OverSpeedDecision(float newData);
    void calculate_Average_positive_Velocity(float newData);
    const int debounceThreshold = 15; // 数据抖动防抖门限值

    QVector<float> dataBetweenCrossings;  // 用于存储穿越点之间的速度(Velocity)数据
    int sampleCounter = 0; // 采样点计数
    bool isAboveZero = true; // 记录当前是正数还是负数    
    int lastCrossingIndex = -10; // 上一次穿越0值的位置
    int crossingPoints = -1;

    QVector<float> dataBetweenCrossings_Neg;  // 用于存储穿越点之间的速度(Velocity)数据
    int sampleCounter_Neg = 0; // 采样点计数
    bool isAboveZero_Neg = true; // 记录当前是正数还是负数
    int lastCrossingIndex_Neg = -10; // 上一次穿越0值的位置
    int crossingPoints_Neg = -1;

    ///// 环形缓冲区 /////


    ///// 速度损失率相关 /////
    float Max_Average_Velocity = -1;
    float Rate_of_Speed_Loss = 0;

    ////// 弹力带力计算相关 /////
    float R0 = 13.3039;
    float a0 = 15.45844;
    float a0_V = 0.36;

//    float R0 = 16.340f;
//    float a0 = 15.45844f;
//    float a0_V = 0.36f;

    ////// 功率计算相关 /////
    QVector<float> Power_floatVector; //功率数据堆栈

    ////// 超速计算相关 /////
    float interval_positive = 0;
    float interval_negative = 0;
    float interval_rate = 0;
    int  interval_flag = 0;
    QVector<float> ForceBetweenCrossings;  // 用于存储穿越点之间的力(Force)数据
    int label_change_flag = 0;

    ////// 数据库缓存数组 /////
    QVector<float> Database_Vector;
    QVector<float> Timestamps_Vector;
    QVector<QPair<float, float>> TimestampsandData;
    float accumulatedTime = 0.0f;
    uint32_t data_pointer = 0;
    QElapsedTimer Elapsed_timer; //Qt高精度计时器

    ////// 运行次数计数 //////
    int Times_of_stretches = 0;

    ////// 单次计时器,用于标签显示 /////
    void startSingleShotTimer();

    ///// 能量条显示函数 ////
    vProgressBars *progressBar_radius;

    ///// 柱状图显示函数 ////
    void initPlot();
//    QCPBars *barsAveragepower;
    QCPBarsGroup *barGroup;  // 添加为类成员变量
    QCPBarsGroup *FatiguebarGroup;  // 添加为类成员变量
//    QCPBars *barsVloss;

    //Class for Serial Data Parsing.
    DataProcessor SerialDataParsing;
    QByteArray Serial_Buffer; // 使用 QByteArray 来存储串口数据
    QString Ble_Buffer; // 使用 QString 来存储BLE数据，未启用！

    ///// 超速更新label /////
    void OverSpeedupdateLabel(float newData);

    ///// 速度损失率缓冲区更新 /////
    /// \brief updateVlossData
    /// \param newData
    QVector<float> VlossBuffer_Vector;
    QVector<float> AveragepowerBuffer_Vector;
    int VlossBuffer_Current_Location = 0;
    int AveragepowerBuffer_Current_Location = 0;
    int BufferLength = 5;
    int Buffer_Position = 0;
    void updateVlossData(float newData);
    void updateAveragepowerData(float newData);
    void updateBarGroupData(QCPBarsGroup* barGroup, const QVector<float>& newData);
    void updateFatigueBarGroupData(QCPBarsGroup* barGroup, const QVector<float>& newData);

    ///// 全局渐变颜色变量 /////
    // 全局渐变变量
    QLinearGradient OrangeGradient;
    QLinearGradient RedGradient;
    QLinearGradient GreenGradient;
    void setupGradients(); // 用于初始化渐变

    ///// 武体老师提出的速度波形绘制 //////
    QVector<float> VelocityBetweenCrossings;  // 用于存储穿越点之间的力(Force)数据

signals:
    void Function_Change_cliked();


    ///// 速度平均值相关 /////
    void averageVelocityCalculated(float AverageVelocity);  // 声明信号

    ///// 环形进度条相关 /////
    void BarDataChanged(int value);  // 声明信号


public slots:
     ///// 速度平均值相关 /////
    void handleAverageVelocity(float AverageVelocity);  // 槽函数处理平均速度,用于接收averageVelocityCalculated（）函数计算出的速度平均值

    void setCircleProgressBar(int value); // 设置环形进度条显示

    void handleTimeout();  //超时处理函数

    void handleTimeout_timestamps(); //超时处理函数(根据时间戳送入数据)

private slots:
    void on_read_filename_clicked();

    void on_pushButton_Next_clicked();

    //add by antis for labelchanged
    void VelocityupdateLabel(float newData);

    void ForceupdateLabel(float newData);

    void VlossupdateLabel(float newData);

    void PowerupdateLabel(float newData);

    void CycleupdateLabel(int newData);

    void on_pushButton_Previous_clicked();

    void on_pushButton_FunSel_clicked();

    void on_pushButton_SaveData_clicked();

    void on_pushButton_BLEconnect_clicked();

    //////////////// 弹力带计算相关 //////////////////
    float VelocityCalculation(int Res);

    /********** (socket) 蓝牙相关的槽函数 **********/
    void discoverBlueTooth(QBluetoothDeviceInfo info);

    void discoveryFinished();

    void readBluetoothDataEvent();

    void bluetoothConnectedEvent();
    /*********** END *************/



protected:
    void keyPressEvent(QKeyEvent *event) override
    {
            if (event->key() == Qt::Key_Escape)
            {
                if (isFullScreen()) {
                    showMinimized(); // 如果当前不是全屏，则最小化窗口
                }
                event->accept(); // 标记事件已处理
            }
            else
            {
                QWidget::keyPressEvent(event); // 对于其他键，调用基类的实现
            }
        }

private:
    Ui::infoWindow *ui;

    QSerialPort *serial;

    bool isSerialOpen;

    SerialPortSettings Serial_set;

    int Function_Selection;

    /************** (ble)蓝牙相关 *************/
    uint8_t CodedFormatFlag; //接收编码格式标志位
    BLEInterface *m_bleInterface; // BLE 接口对象的指针
    void BledataReceived(QByteArray data); // 处理接收到的数据的私有函数

    /************* (socket)蓝牙相关 **************/
    void bluetoothDataSend(QString str);
    QString BTaddress;
    QBluetoothSocket *socket;
    /************ END ************/

    /*************** 圆形进度条 *****************/
    CircularProgessBar *circularProgressBar3;

    /**********静态模式（模拟数据传输）**********/
    QTimer *m_pTimer;


};











#endif // INFOWINDOW_H

/*
*****************************************************************************
*  Copyright (C), 仅供实验室内部使用，未经许可禁止外传
*
*  @file    infowindow.cpp
*  @brief   主窗口  (串口接收,蓝牙接收等数据接收也在此实现)
*           蓝牙连接流程: 打开程序后，4s内自动搜索蓝牙，在此期间不要进行蓝牙相关操作，搜索完成后，
*                       点击连接设备，会自动连接当前选中的设备，并开始搜索服务，此时应等待1s左右，
*                       服务搜索完成后，需要点击连接服务，完成整个连接流程。
*           1. 在ui文件中内嵌ecgwidget窗口，用于ecg波形绘制
*           2. 在ui文件中内嵌comwave窗口(x2)，用于三轴加速度、呼吸波形绘制
*           3. 修复QT串口传输的粘包丢包问题，具体见
*               infoWindow::receiveSerialPortData()函数实现
*           4. 基本蓝牙功能实现      by antis 2024 051
*           5. (todo) 蓝牙与串口开启按钮应该互斥，一个开启另一个则应无法点击 by antis 20240521
*           6. (todo) 蓝牙接收由于每次发5-6个包(视下位机而定),导致绘图的时间间隔为0.012S
*               即1s仅能刷新10次，视觉上会有点卡顿，最好1s刷新20次以上，解决方法为蓝牙接收到的每一个包，
*               将其拆解为2-3个，分三次让波形刷新(刷新间隔需要设置定时器) ,这样刷新率会如串口一致
*           7. (todo) 蓝牙连接有程序崩溃的风险，初步判断是蓝牙连接流程中间，各个流程需要一定延时
*               可能在该程序中还存在不规范之处。
*           8. 文件读取功能正常使用前提:左侧项目选项设置构建目录为当前文件目录(100p.txt所在目录)
*              修改.ui文件也需要修改这个，推荐设置！
*
*  @author  kdh
*  @date    2024-05-20
*  @version V1.1.1 2024-05-20
*  @advice  尽量不要将各个功能都在同一文件中实现
*           文件解耦会极大提高工程可扩展性、可测试性,保证软件效率和质量
*----------------------------------------------------------------------------
*  @note 历史版本     修改人员        修改日期        修改内容
*  @note v1.0.0      kdh           2023-12-20     创建
*  @note v1.1.0      kdh           2024-05-08     完成1.2.3.基本功能
*  @note v1.1.0      kdh           2024-05-22     修复读取文件功能(仅测试debug)
*****************************************************************************
**/
#include "infowindow.h"
#include "ui_Infowindow.h"


#define Dynamic_Mode 0
#define Static_Mode 1


#define MOST_ACTIVE_NULL      			0      	 /*未找到最活跃轴*/
#define MOST_ACTIVE_X					1		 /*最活跃轴X*/
#define MOST_ACTIVE_Y					2        /*最活跃轴Y*/
#define MOST_ACTIVE_Z					3        /*最活跃轴Z*/
#define INACTIVE 0
#define ACTIVE 1
#define ACTIVE_PRECISION 1                      //活跃轴阈值

#define MODE 1  // 软件运行模式 0 为静态;1 为动态

#define SEVERE 0.6
#define MODERATE 0.3


infoWindow::infoWindow(QWidget *parent) :
QWidget(parent),
ui(new Ui::infoWindow)
{
    ui->setupUi(this);
    //串口、蓝牙初始化及柱状图样式设置
    initConfig();
}

infoWindow::~infoWindow()
{
    delete ui;
}


/**********静态模式（模拟数据传输）**********/
// 已弃用
void infoWindow::handleTimeout()
{
    ReadDatafromFile();
}

// 在使用
void infoWindow::handleTimeout_timestamps()
{
    qint64 elapsedMilliseconds = Elapsed_timer.elapsed(); // 获取经过的时间（毫秒）
    float elapsedSeconds = static_cast<float>(elapsedMilliseconds) / 1000.0f;
    if (elapsedSeconds >= Timestamps_Vector[data_pointer]) {
        ReadDatafromFile();
    }
}

// 封装的函数，用于读取 CSV 文件并提取第三列数据
QVector<float> readThirdColumnFromFile(const QString &filePath)
{
    QVector<float> thirdColumnData;
    // 打开 CSV 文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file!";
        return thirdColumnData; // 返回空的 QVector
    }
    QTextStream in(&file);
    bool isFirstLine = true;
    // 逐行读取 CSV 文件
    while (!in.atEnd()) {
        QString line = in.readLine();
        // 跳过第一行
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        QStringList fields = line.split(',');
        // 读取第三列数据，索引为 2（从 0 开始计数）
        if (fields.size() > 2) {
            // 去除字段中的双引号和空格
            QString thirdColumnValue = fields[2].trimmed().remove('"');

            bool ok;
            float value = thirdColumnValue.toFloat(&ok);  // 转换为 float
            if (ok) {
                thirdColumnData.append(value);  // 仅在转换成功时添加到数组
            } else {
                qDebug() << "Failed to convert third column to float. Value: '" << thirdColumnValue << "' in row: " << line;
            }
        } else {
            qDebug() << "This row doesn't have a third column. Row: " << line;
        }
    }

    file.close();
    qDebug() << "Third column float data:";
    for (float data : thirdColumnData) {
        qDebug() << data;
    }
    return thirdColumnData;
}

QVector<float> readSecondColumnTimestamps(const QString &filePath)
{
    QVector<float> secondColumnData;

    // 打开 CSV 文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file!";
        return secondColumnData; // 返回空的 QVector
    }

    QTextStream in(&file);
    bool isFirstLine = true;

    // 逐行读取 CSV 文件
    while (!in.atEnd()) {
        QString line = in.readLine();

        // 跳过第一行（如果需要）
        if (isFirstLine) {
            isFirstLine = false;
            // 如果需要读取第二行的时间戳，可以在这里继续
            continue;
        }

        QStringList fields = line.split(',');

        // 读取第二列数据，索引为 1（从 0 开始计数）
        if (fields.size() > 1) {
            // 去除字段中的双引号和空格
            QString secondColumnValue = fields[1].trimmed().remove('"');

            bool ok;
            float value = secondColumnValue.toFloat(&ok);  // 转换为 float
            if (ok) {
                secondColumnData.append(value);  // 仅在转换成功时添加到数组
            } else {
                qDebug() << "Failed to convert second column to float. Value: '" << secondColumnValue << "' in row: " << line;
            }
        } else {
            qDebug() << "This row doesn't have a second column. Row: " << line;
        }
    }

    file.close();

    qDebug() << "Second column float data:";
    for (float data : secondColumnData) {
        qDebug() << data;
    }

    return secondColumnData;
}

// 读取 CSV 文件的时间戳（第一列）和数据（第二列），并分别存入两个 QVector<float>
void readTimestampsAndData(const QString &filePath, QVector<float> &timestamps, QVector<float> &dataValues)
{
    // 清空传入的 QVector，防止重复调用时数据叠加
    timestamps.clear();
    dataValues.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file!";
        return;
    }

    QTextStream in(&file);
    bool isFirstLine = true;

    while (!in.atEnd()) {
        QString line = in.readLine();

        // 跳过第一行（通常是表头）
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        QStringList fields = line.split(',');

        // 确保至少有两列（时间戳和数据）
        if (fields.size() > 1) {
            // 处理数据，去除双引号和空格
            QString timestampStr = fields[0].trimmed().remove('"');
            QString dataStr = fields[1].trimmed().remove('"');

            bool ok1, ok2;
            float timestamp = timestampStr.toFloat(&ok1)  / 1000.0f ;
            float data = dataStr.toFloat(&ok2);

            if (ok1 && ok2) {
                timestamps.append(timestamp);   // 添加时间戳
                dataValues.append(data);        // 添加数据
            } else {
                qDebug() << "Failed to convert values. Timestamp: '" << timestampStr
                         << "', Data: '" << dataStr << "' in row: " << line;
            }
        } else {
            qDebug() << "This row doesn't have enough columns. Row: " << line;
        }
    }

    file.close();

    // 输出调试信息
//    qDebug() << "Extracted timestamps:";
//    for (float t : timestamps) qDebug() << t;

//    qDebug() << "Extracted data values:";
//    for (float d : dataValues) qDebug() << d;
}

//////////////// 暂时没有在ui中加入该按键，使用Save按键替代  /////////////////
void infoWindow::on_read_filename_clicked()
{
    QString path = QDir::currentPath();
    QString filename = path + "/100p.txt";
    qDebug()<< "当前路径" <<filename ;
    // 调用封装的函数，读取 CSV 文件的第三列数据
    Database_Vector = readThirdColumnFromFile(filename);
}

//蓝牙与串口初始化
void infoWindow::initConfig() {
    // 创建一个最大容量为 5 的环形缓冲区

    /***************************(socket)蓝牙相关**************************/
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent;
    discoveryAgent->setLowEnergyDiscoveryTimeout(1000);    //设置超时时间
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(discoverBlueTooth(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(discoveryFinished()));
    discoveryAgent->start();
    /*****************************  END  ****************************/

    // 模式设置
    Function_Selection = Static_Mode;

    // 柱状图样式设置
    initPlot();

    ////// 弹力带平均速度计算相关 //////
    QObject::connect(this, &infoWindow::averageVelocityCalculated, this, &infoWindow::handleAverageVelocity); //弃用！！！
    ui->Force_Wave->SetdrawColor(YELLOW);
    ui->Velocity_Wave->SetdrawColor(BLUE);
    SerialDataParsing.setRespFilterLength(ui->Velocity_Wave->returnDisplayWaveformLength());
    ui->label_Fatiguetext->setProperty("customTextColor", false);

    //////////// ！！！！！！！！！ 记得修改控件让其数值变化 //////////////////////////
    connect(this,SIGNAL(BarDataChanged(int)),this,SLOT(setCircleProgressBar(int))); //连接信号与槽

    /**********静态模式（模拟数据传输）**********/
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout_timestamps()));

    ui->progressBar->setValue(100);


}

/**
 * @brief   超速显示更新
 * @param   当前超速程度
 * @details 在主界面显示当前超速信息
 */
void infoWindow::OverSpeedupdateLabel(float newData)
{
    ui->label_OS->setText(QString::number(newData, 'f', 1));

}


/**
 * @brief   速度显示更新
 * @param   当前速度
 * @details 在主界面显示当前速度信息
 */
void infoWindow::VelocityupdateLabel(float newData)
{
    ui->label_Velocity->setText(QString::number(newData, 'f', 1));

}

/**
 * @brief   拉力显示更新
 * @param   当前拉力
 * @details 在主界面显示当前拉力信息
 */
void infoWindow::ForceupdateLabel(float newData)
{
    ui->label_Force->setText(QString::number(newData, 'f', 1));

}

/**
 * @brief   速度损失率显示更新
 * @param   当前速度损失率
 * @details 在主界面显示当前速度损失率
 */
void infoWindow::VlossupdateLabel(float newData)
{
    if(newData == -1)
    {
//        ui->label_Warn_pic->setText("--");
    }
    else{
//        ui->label_Vloss->setText(" "+QString::number(qRound(newData * 100))); //先乘以100后保留整数部分
        VlossBuffer_Vector.append(newData);
        updateBarGroupData(barGroup,VlossBuffer_Vector);
        // 更新坐标轴范围（根据新数据范围自动调整）
//        ui->QCustom_Vloss->rescaleAxes();
        // 刷新绘图
        ui->QCustom_Vloss->replot();
        if ((newData*100) > 60)
        {

             qDebug() << "Alarm";

        }
        else if ((newData*100) > 30)
        {

             qDebug() << "Alarm";

        }
        else if((newData*100) <= 30)
        {

        }
    }
}

void infoWindow::PowerupdateLabel(float newData)
{
    if(newData < 0){
        newData = 0;
    }
    ui->label_Power->setText(QString::number(qRound(newData)) + "W"); //保留整数部分
    AveragepowerBuffer_Vector.append(newData);
    updateFatigueBarGroupData(FatiguebarGroup,AveragepowerBuffer_Vector);
//    updateVlossBarData(AveragepowerBuffer_Vector);
    // 更新坐标轴范围（根据新数据范围自动调整）
//    ui->QCustom_Averagepower->rescaleAxes();
    // 刷新绘图
    ui->QCustom_Averagepower->replot();

}

void infoWindow::CycleupdateLabel(int newData)
{
    if(newData < 0){
        newData = 0;
    }
    ui->label_Cycle->setText(QString::number(newData)); //保留整数部分
}



//Implementing Pagination through Semaphores
void infoWindow::on_pushButton_Next_clicked()
{
    if(Function_Selection == Static_Mode)
    {
//        ui->Resis_Wave->SetEcgDataShow(1);
//        ui->Resis_Wave->update();
    }
    else if(Function_Selection == Dynamic_Mode)
    {
//        ui->Resis_Wave->update();
    }

}

void infoWindow::on_pushButton_Previous_clicked()
{
    if(Function_Selection == Static_Mode)
    {

    }
    else if(Function_Selection == Dynamic_Mode)
    {

    }
}

void infoWindow::on_pushButton_FunSel_clicked()
{
    if(Function_Selection == Dynamic_Mode)
    {
        Function_Selection = Static_Mode;
        qDebug() << "Static";
    }
    else {
        Function_Selection = Dynamic_Mode;
        qDebug() << "Dynamic";
    }
}

/////////////// 该槽函数暂时用于数据读取而不是保存 ///////////////
//void infoWindow::on_pushButton_SaveData_clicked()
//{
//    ui->Resis_Wave->saveVectorToFile_float();
//    ui->Velocity_Wave->saveVectorToFile_float();
//}
void infoWindow::on_pushButton_SaveData_clicked()
{
    if(Function_Selection == Static_Mode)
    {
        QString path = QDir::currentPath();
        QString filename = path + "/underwater1.csv";
        qDebug()<< "当前路径" <<filename ;
        // 调用封装的函数，读取 CSV 文件的第三列数据
        Database_Vector = readThirdColumnFromFile(filename);
        Timestamps_Vector = readSecondColumnTimestamps(filename);
    //    readTimestampsAndData(filename, Timestamps_Vector, Database_Vector);
        Elapsed_timer.start();
        m_pTimer->start(TIMER_TIMEOUT);   // 读取数据完成后开启定时器
    }
    else if(Function_Selection == Dynamic_Mode)
    {
        qDebug()<< "动态模式,等待蓝牙连接" ;
    }
}


/*
在该函数中，主要进行以下四种情况的讨论：
1.没有找到帧头，说明当前数据是数据的后半部分，有部分数据丢失，属于无效数据
2.找到帧头，但帧头不在第一个，说明前面部分无效，丢弃
3.有没有找到帧尾，并且数据长度符合要求，进行解包
4.没有找到帧尾，等待数据帧完整后下一次处理
*/
void infoWindow::receiveSerialPortData()
{
    // 先找到帧头的位置
    int headerIndex = Serial_Buffer.indexOf(0xAA);  // 这里截断的原因是"0xAA"需要指定数据类型
    bool Recflag;
    if (-1 == headerIndex) {
        Serial_Buffer.clear();  // 找不到帧头，则将所有缓存数据清空
    } else {
        if (headerIndex > 0) {
            // 如果帧头不在第一个，则说明前面的数据是没用的，直接舍弃
            Serial_Buffer.remove(0, headerIndex);
        }
        // 此时帧数,
        // 数据长度位的索引为2,3  所以size需要>=4
        if (Serial_Buffer.size() >= 16 &&  static_cast<unsigned char>(Serial_Buffer.at(15)) == 0xFE ) {  // 1.有包含数据长度位   2.从0开始数，所以是31
            // 取出完整的数据
            QByteArray final_data = Serial_Buffer.left(16);
            Recflag = SerialDataParsing.processData(final_data);
            if(Recflag)
            {
                ui->Velocity_Wave->updateWaveData(SerialDataParsing.RESP_Data);

            }
            Serial_Buffer.remove(0, 16);  // 将取出的指令数据从缓存中移除(删除从0开始的16个字节)
        }
    }
}

/*
 * 该函数用于挚盒数据读取
 * 读取前需发送单通道电阻读取命令：F001 A10D 0A
 * 读取数据格式为：#,电池剩余电量百分比,电阻
*/
void infoWindow::receiveLinkZillData()
{
    // 先找到帧头的位置
    int headerIndex = Serial_Buffer.indexOf("#");
    float Velocity = 0;
    float Force = 0;
    float Power = 0;
    float Velocity_filtered = 0;
    static float last_ResisData = 0;
    static bool first_Velocity_flag = true;
    //ui->label_data->setText(QString::number(Serial_Buffer.size()/16));
    bool Recflag;
    if (-1 == headerIndex) {
        Serial_Buffer.clear();  // 找不到帧头，则将所有缓存数据清空
    }
    else {
        if (headerIndex > 0)
        {
            // 如果帧头不在第一个，则说明前面的数据是没用的，直接舍弃
            Serial_Buffer.remove(0, headerIndex); //这里+1是因为仅仅取出#前一位的数据
        }
        // 此时帧头一定在第一个
        else{
            headerIndex = Serial_Buffer.indexOf("\n#");
            if (headerIndex >= 0) {  //找到了下一帧的帧头，可以截取一帧完整的数据
                // 取出完整的数据
                QByteArray final_data = Serial_Buffer.left(headerIndex);
                Recflag = SerialDataParsing.processData(final_data);
                if(Recflag)
                {
                    //打算这里继续集成一下，更新缓存改为当前infowindow任务，通过函数参数来传入数据即可；
//                    ui->Resis_Wave->updateWaveData_float(SerialDataParsing.Res_Data);

                    //////////////// 计算速度 ///////////////////
                    if(first_Velocity_flag){ // 为了避免第一次数据过大，导致波形显示不正确
                        // do nothing
                        first_Velocity_flag = false;
//                        ui->label_Power->setStyleSheet(
//                            "QLabel#label_Power {"
//                            "font-family: \"Microsoft YaHei\";"
//                            "font-weight: bold;"
//                            "font-size: 50pt;"
//                            "color: yellow;"
//                            "border-radius: 10px;"  // 设置圆角半径为10px
//                            "}; "
//                        );
                    }
                    else{
                        Velocity = (std::sqrt(SerialDataParsing.Res_Data) - std::sqrt(last_ResisData))/Dt;
                        Velocity = Velocity * a0_V;
                        float x = (30.91688 * 100000 * (SerialDataParsing.Res_Data - R0)/SerialDataParsing.Res_Data) + 141087.54824;
                        Force = (std::sqrt(x) - 441) / a0;
                        if(Force <= 0)
                        {       
                            Force = 0;  
                        }
                    }
                    ////////////////////////////////////////////

                    last_ResisData = SerialDataParsing.Res_Data;
//                    Data_floatVector.append(SerialDataParsing.Res_Data); // !!!!!!!!! 这里一直存储可能有隐患
                    addFilterData(Filter_floatVector,Velocity,6);

                    Velocity_filtered =Average(Filter_floatVector);
                    VelocityupdateLabel(Velocity_filtered);

                    ForceupdateLabel(Force);
                    ALL_Velocity_floatVector.append(Velocity_filtered); // 此处添加所有的速度数值 ！！！！！！！！！！ 可能存在隐患
                    ui->Velocity_Wave->updateWaveData_float(Velocity_filtered);
//                    ui->Force_Wave->updateWaveData_float(Force);
                    ui->progressBar->setValue(Force*1.5);

                    // 计算功率
                    Power = Velocity_filtered * Force;
                    Power_floatVector.append(Power);

                    // 计算速度损失率
                    AverPosSpeed_RateofSpeedLoss(Velocity_filtered);
                    AverNegSpeed_OverSpeedDecision(Velocity_filtered);



                }
                Serial_Buffer.remove(0, headerIndex);  // 将取出的指令数据从缓存中移除(删除从0开始的16个字节)
            }
        }
    }
}


/*
 * 该函数用于从文件读取仪表数据
 * 读取数据为:数据采集时间，电阻大小
 * 该函数通过计时器自动读取
*/
void infoWindow::ReadDatafromFile()
{
    // 先找到帧头的位置
    float Velocity = 0;
    float Force = 0;
    float Power = 0;
    float Velocity_filtered = 0;
    static float last_ResisData = 0;
    static bool first_Velocity_flag = true;
    if(!Database_Vector.isEmpty())
    {
        SerialDataParsing.Res_Data = Database_Vector[data_pointer];
        //////////////// 计算速度 ///////////////////
        if(first_Velocity_flag){ // 为了避免第一次数据过大，导致波形显示不正确
            // do nothing
            first_Velocity_flag = false;
            //            ui->label_Power->setStyleSheet(
            //                "QLabel#label_Power {"
            //                "font-family: \"Microsoft YaHei\";"
            //                "font-weight: bold;"
            //                "font-size: 70pt;"
            //                "color: yellow;"
            //                "border-radius: 10px;"  // 设置圆角半径为10px
            //                "}; "
            //            );
            //            ui->label_Cycle->setStyleSheet(
            //                "QLabel#label_Cycle {"
            //                "font-family: \"Microsoft YaHei\";"
            //                "font-weight: bold;"
            //                "font-size: 70pt;"
            //                "color: white;"
            //                "border-radius: 10px;"  // 设置圆角半径为10px
            //                "}; "
            //            );
        }

            else{
            float dt_Velocity = Timestamps_Vector[data_pointer] - Timestamps_Vector[data_pointer-1];

            Velocity = (std::sqrt(SerialDataParsing.Res_Data) - std::sqrt(last_ResisData))/dt_Velocity;
            Velocity = a0_V * Velocity;
            float x = (30.91688 * 100000 * (SerialDataParsing.Res_Data - R0)/SerialDataParsing.Res_Data) + 141087.54824;
            Force = (std::sqrt(x) - 441) / a0;
            if(Force <= 0)
            {
                Force = 0;
            }
        }
        last_ResisData = SerialDataParsing.Res_Data;
        addFilterData(Filter_floatVector,Velocity,6);
        Velocity_filtered =Average(Filter_floatVector);
        VelocityupdateLabel(Velocity_filtered);
        ForceupdateLabel(Force);
        ALL_Velocity_floatVector.append(Velocity_filtered); // 此处添加所有的速度数值 ！！！！！！！！！！ 可能存在隐患
        ui->Velocity_Wave->updateWaveData_float(Velocity_filtered);
    //  ui->Force_Wave->updateWaveData_float(Force);
        ui->progressBar->setValue(Force*1.5);
        Power = Velocity_filtered * Force;
        Power_floatVector.append(Power);
        // 计算平均正速度、速度损失率、平均功率计算
        AverPosSpeed_RateofSpeedLoss(Velocity_filtered);
        // 计算平均负速度、速度损失率
        AverNegSpeed_OverSpeedDecision(Velocity_filtered);
    }
    data_pointer ++;
//    qDebug()<<"data_pointer"<<data_pointer;
}


void printData(const QVector<float>& dataBetweenCrossings) {
    for (float value : dataBetweenCrossings) {
        qDebug() << value;
    }
}

void infoWindow::startSingleShotTimer() {
    // 使用 QTimer::singleShot 创建一个0.6秒后触发的定时器
    QTimer::singleShot(600, [this]() {
        label_change_flag = 0;
        qDebug() << "计时器触发，执行一次操作";
    });
}

/* *************** *
 * 速度曲线穿越横坐标事件监测函数  （同时完成平均速度的计算）
 * 1.暂存数组防溢
 * 2.从上半轴穿越到下半轴：进行积分平均处理
 * 3.从下半轴穿越到上半轴：仅对穿越点坐标进行记录处理
 * 4.完成平均速度计算，并通过信号与槽发送出去
 * 5.20240928添加：对信号时间轴进行区分
 * 6.20241027添加：正负穿越点阈值(+0.1)，以及防抖动阈值30
 * *************** */
void infoWindow::AverPosSpeed_RateofSpeedLoss(float newData)
{
    // 数据记录
    dataBetweenCrossings.append(newData);
//    QFile file("./velocity_loss_data/velocity_data(overhang3).csv");
//    if (file.open(QIODevice::Append | QIODevice::Text)) {
//        QTextStream out(&file);
//        out << Timestamps_Vector[data_pointer] << "," << newData << "\n";
//        file.close();
//    } else {
//        qDebug() << "Unable to open file for writing";
//    }
    ++sampleCounter;
    if (dataBetweenCrossings.size() > 2000)  // 一次拉伸动作不太可能有2000个数据
    {
        dataBetweenCrossings.remove(0);
    }
    if (newData < 0.1 && isAboveZero)  // 只在正到负的穿越点时执行积分
    {
        crossingPoints = sampleCounter;  // 记录这一次的穿越点位置
        if (crossingPoints == -1) // 第一次启动软件不进行计算
        {
            qDebug() << "crossingPoints: " << crossingPoints << "初始化完成";
            crossingPoints = sampleCounter;
            lastCrossingIndex = sampleCounter;
        }
        else if (sampleCounter - lastCrossingIndex > debounceThreshold)  // 数据放抖动数值设置
        {
            int interval = sampleCounter - lastCrossingIndex; // 计算间隔
            interval_positive = interval;
            qDebug() << "interval_positive: " << interval_positive;
            if (dataBetweenCrossings.size() > interval) { // 获取正半轴速度波形数据
                // 如果 QVector 的大小超过 interval，移除多余的元素
                dataBetweenCrossings.erase(dataBetweenCrossings.begin(),
                                           dataBetweenCrossings.end() - interval);
                }
                    /////////// 只在信号从正到负时进行积分 /////////////
                    float Average_positive_Velocity = Average(dataBetweenCrossings);

                    if (Average_positive_Velocity != 0)
                    {
                    qDebug() << "Average positive velocity: " << Average_positive_Velocity;
                    // 发射信号，发送计算出的平均正速度
                        if(Average_positive_Velocity > 0.1)
                        {
                            handleAverageVelocity(Average_positive_Velocity);
                        }
                    }
                    /////////////////// END ////////////////////
            // (穿越事件)清空存储的数据，为下一次穿越点做准备
            dataBetweenCrossings.clear();
            sampleCounter = 0;
            lastCrossingIndex = 0; //上个状态也清0
            isAboveZero = false;  // 更新状态为低于零

            ////// 拉伸次数更新 //////
            CycleupdateLabel(Times_of_stretches);
            Times_of_stretches += 1;

            ////// 更新平均功率 //////
            float AveragePower = 0;
            AveragePower = Average(Power_floatVector);
            PowerupdateLabel(AveragePower);
            Power_floatVector.clear();
        }
    }
    else if (newData > 0.1 && !isAboveZero){   // 从负到正的时候更新状态
        crossingPoints = sampleCounter;  // 记录这一次的穿越点位置，其实为起始点
        if (crossingPoints == -1) // 第一次启动软件不进行计算
        {
            qDebug() << "crossingPoints: " << crossingPoints << "初始化完成";
            crossingPoints = sampleCounter;
            lastCrossingIndex = sampleCounter;
        }
        else if (sampleCounter - lastCrossingIndex > debounceThreshold)  // 数据放抖动数值设置
        {
            lastCrossingIndex = sampleCounter;  // 记录这一次穿越点的索引
            isAboveZero = true;  // 更新状态为大于零
            Power_floatVector.clear();
        }
    }
}

/* *************** *
 * 速度曲线穿越横坐标事件监测函数  （同时完成平均速度的计算）
 * 1.暂存数组防溢
 * 2.从上半轴穿越到下半轴：进行积分平均处理
 * 3.从下半轴穿越到上半轴：仅对穿越点坐标进行记录处理
 * 4.完成平均速度计算，并通过信号与槽发送出去
 * 5.20240928添加：对信号时间轴进行区分
 * 6.20241027添加：负穿越点阈值(-0.1)，以及防抖动阈值30
 * *************** */
void infoWindow::AverNegSpeed_OverSpeedDecision(float newData)
{
    // 数据记录
    dataBetweenCrossings_Neg.append(newData);
    ++sampleCounter_Neg;
    if (dataBetweenCrossings_Neg.size() > 2000)  // 一次拉伸动作不太可能有2000个数据
    {
        dataBetweenCrossings_Neg.remove(0);
    }
    if (newData < -0.1 && isAboveZero_Neg)  // 在正到负的穿越点时执行积分
    {
        crossingPoints_Neg = sampleCounter_Neg;  // 记录这一次的穿越点位置
        if (crossingPoints_Neg == -1) // 第一次启动软件不进行计算
        {
            qDebug() << "crossingPoints: " << crossingPoints_Neg << "初始化完成";
            crossingPoints_Neg = sampleCounter_Neg;
            lastCrossingIndex_Neg = sampleCounter_Neg;
        }
        else if (sampleCounter_Neg - lastCrossingIndex_Neg > debounceThreshold)  // 数据放抖动数值设置为30
        {
            lastCrossingIndex_Neg = sampleCounter_Neg;  // 记录这一次穿越点的索引 -> 供穿越点计算
            isAboveZero_Neg = false;  // 更新状态为低于零
        }
    }
    else if (newData > -0.1 && !isAboveZero_Neg){   // 从负到正的时候计算积分，更新状态
        crossingPoints_Neg = sampleCounter_Neg;  // 记录这一次的穿越点位置，其实为起始点
        if (crossingPoints_Neg == -1) // 第一次启动软件不进行计算
        {
            qDebug() << "crossingPoints_Neg: " << crossingPoints_Neg << "初始化完成";
            crossingPoints_Neg = sampleCounter_Neg;
            lastCrossingIndex_Neg = sampleCounter_Neg;
        }
        else if (sampleCounter_Neg - lastCrossingIndex_Neg > debounceThreshold)  // 数据放抖动数值设置为30
        {
            int interval = sampleCounter_Neg - lastCrossingIndex_Neg; // 计算间隔
            interval_negative = interval;
            qDebug() << "interval_negative: " << interval_negative;
            if (dataBetweenCrossings_Neg.size() > interval) { // 获取负半轴速度波形数据
                // 如果 QVector 的大小超过 interval，移除多余的元素
                dataBetweenCrossings_Neg.erase(dataBetweenCrossings_Neg.begin(),
                                           dataBetweenCrossings_Neg.end() - interval);
            }
            if(interval_positive != 0)
            {
                interval_rate = interval_negative / interval_positive; //速度损失率的计算 -> 负半轴时间与正半轴时间之比
                qDebug() << "interval_rate: " << interval_rate;
                  float Average_negative_Velocity = Average(dataBetweenCrossings_Neg);
                    qDebug() << "Average_negative_Velocity: " << Average_negative_Velocity;
                      if(Average_negative_Velocity < -0.05)
                      {
                          OverSpeedupdateLabel(interval_rate);
                          if(interval_rate < 0.5)//速度比率
                          {
                              ui->label_OS->setStyleSheet(
                                  "QLabel#label_OS {"
                                  "font-family: \"Microsoft YaHei\";"
                                  "font-weight: bold;"
                                  "font-size: 50pt;"
                                  "color: #FF2619;"
                                  "border-radius: 10px;"  // 设置圆角半径为10px
                                  "}; "
                              );
                              startSingleShotTimer();
                              label_change_flag = 1;

                          }
                          else if(interval_rate < 1.0)
                          {
                              ui->label_OS->setStyleSheet(
                                  "QLabel#label_OS {"
                                  "font-family: \"Microsoft YaHei\";"
                                  "font-weight: bold;"
                                  "font-size: 50pt;"
                                  "color: #FF2619;"
                                  "border-radius: 10px;"  // 设置圆角半径为10px
                                  "}; "
                              );
                              startSingleShotTimer();
                              label_change_flag = 1;

                          }
                          else{
                              ui->label_OS->setStyleSheet(
                                  "QLabel#label_OS {"
                                  "font-family: \"Microsoft YaHei\";"
                                  "font-weight: bold;"
                                  "font-size: 50pt;"
                                  "color: #DA879C;"
                                  "border-radius: 10px;"  // 设置圆角半径为10px
                                  "}; "
                              );
                          }
                      }
                      else if(label_change_flag != 1){
                          ui->label_OS->setStyleSheet(
                              "QLabel#label_OS {"
                              "font-family: \"Microsoft YaHei\";"
                              "font-weight: bold;"
                              "font-size: 50pt;"
                              "color: #DA879C;"
                              "border-radius: 10px;"  // 设置圆角半径为10px
                              "}; "
                          );
                      }
            }
            // 清空存储的数据，为下一次穿越点做准备
            dataBetweenCrossings_Neg.clear();
            sampleCounter_Neg = 0;
            lastCrossingIndex_Neg = 0; //上个状态也清0
//            lastCrossingIndex_Neg = sampleCounter_Neg;  // 记录这一次穿越点的索引
            isAboveZero_Neg = true;  // 更新状态为大于零
        }
    }
}


/************************************************************
 * 均值滤波 */
void infoWindow::addFilterData(QVector<float>& ArgFilter_floatVector,float newData,int AccLength)
{
    // 添加新的 ACC 数据到容器尾部
    ArgFilter_floatVector.append(newData);

    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    while (ArgFilter_floatVector.size() > AccLength)
    {
        ArgFilter_floatVector.removeFirst();
    }
}


float infoWindow::Average(const QVector<float>& dataBetweenCrossings) {
    if (dataBetweenCrossings.isEmpty()) {
        return 0;  // 如果数据为空，返回 0 或其他默认值
    }

    float sum = 0;
    for (float value : dataBetweenCrossings) {
        sum += value;  // 计算总和
    }

    float average = sum / dataBetweenCrossings.size();  // 计算平均值
    return average;
}

/************************************************************
 * END */


/* *************** *
 * 平均速度处理函数  （通过信号与槽接收数据）
 * 1.接收计算出的信号与槽的数据
 * 2.完成最大平均速度的更新
 * 3.计算速度损失率
 * *************** */
void infoWindow::handleAverageVelocity(float AverageVelocity)
{
    if(Max_Average_Velocity == -1){ // 初始化阶段，不计算速度损失率
        Max_Average_Velocity = AverageVelocity;
    }
    else if(AverageVelocity >= Max_Average_Velocity){ // 如果当前速度大于最大平均速度，重新更新最大平均速度，然后计算速度损失率
        Max_Average_Velocity = AverageVelocity;
        Rate_of_Speed_Loss = (Max_Average_Velocity - AverageVelocity)/Max_Average_Velocity;
        VlossupdateLabel(-1);
//        QFile file("./velocity_loss_data/velocity_loss_data(underwater1)-real(update).csv");
//        if (file.open(QIODevice::Append | QIODevice::Text)) {
//            QTextStream out(&file);
//            out << Timestamps_Vector[data_pointer] << "," << Rate_of_Speed_Loss << "\n";
//            file.close();
//        } else {
//            qDebug() << "Unable to open file for writing";
//        }
    }
    else{ // 完成初始化之后，计算速度损失率
        Rate_of_Speed_Loss = (Max_Average_Velocity - AverageVelocity)/Max_Average_Velocity;
        VlossupdateLabel(Rate_of_Speed_Loss);
        emit BarDataChanged(qRound(Rate_of_Speed_Loss * 100));
        qDebug() << "velocity loss: " << Rate_of_Speed_Loss;
        // 将Rate_of_Speed_Loss与时间戳写入CSV文件
//        QFile file("./velocity_loss_data/velocity_loss_data(underwater1)-real.csv");
//        if (file.open(QIODevice::Append | QIODevice::Text)) {
//            QTextStream out(&file);
//            out << Timestamps_Vector[data_pointer] << "," << Rate_of_Speed_Loss << "\n";
//            file.close();
//        } else {
//            qDebug() << "Unable to open file for writing";
//        }
    }
}


float infoWindow::VelocityCalculation(int Res)
{
    float squareRoot = std::sqrt(Res); // 计算平方根

    return squareRoot;
}


void infoWindow::slot_receiveSerialPortData()
{
     receiveSerialPortData();
}


/***************************蓝牙相关**************************/
void infoWindow::on_pushButton_BLEconnect_clicked()
{
//    // 连接按钮点击事件
//    m_bleInterface->set_currentDevice(ui->devicesComboBox->currentIndex()); // 设置当前连接的设备
//    m_bleInterface->connectCurrentDevice(); // 连接当前设备
}

/*********************** (BLE)蓝牙相关 **************************/
void infoWindow::BledataReceived(QByteArray data){
   // qDebug() << data.toHex();
    if (isfirst == 0)
    {
        if(Serial_Buffer.size() > 500*16*2)
        {
            Serial_Buffer.clear();
            isfirst = 1;
            qDebug() << "清除完成";
        }
    }

    if (!data.isEmpty() )
    {
        Serial_Buffer.append(data);         // 由于先写的串口接收，这里的buffer为Serial_Buffer
        if(isfirst == 1)
        {
            while(Serial_Buffer.size()>16)      // (todo)考虑之后换一个更加通用的变量名，避免歧义  by antis 20240521
            {
                receiveSerialPortData();
            }
        }
    }
}

/*********************** (socket)蓝牙相关 **************************/
void infoWindow::discoveryFinished()
{
    qDebug()<<"discoveryFinished";
    static QString serviceUuid("00001101-0000-1000-8000-00805F9B34FB");
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(QBluetoothAddress(BTaddress), QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
    connect(socket,SIGNAL(readyRead()), this, SLOT(readBluetoothDataEvent()));
    connect(socket,SIGNAL(connected()), this, SLOT(bluetoothConnectedEvent()));
}

void infoWindow::discoverBlueTooth(QBluetoothDeviceInfo info)
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    if(info.name()=="RC1033")
    {
        BTaddress = info.address().toString();
    }
    ui->devicesComboBox->addItem(info.name());
    qDebug()<<label;
}


// 蓝牙(socket)数据读取函数，通过信号与槽被动调用
void infoWindow::readBluetoothDataEvent()
{
    char data[100];
    qint64 len = socket->read((char *)data, 100);
    QByteArray qa2((char*)data,len);

    QString qstr(qa2.toHex());
    //   qDebug()<<"----"<<qstr.toUpper();

    Serial_Buffer.append(qa2);

    while(Serial_Buffer.size()>30)
    {
       receiveLinkZillData();
    }
}

void infoWindow::bluetoothConnectedEvent()
{
    qDebug()<<"bluetoothConnectedEvent";

    bluetoothDataSend("hellow bluetooth");
}

void infoWindow::bluetoothDataSend(QString str)
{
    QByteArray arrayData;
    arrayData = str.toUtf8();
    socket->write(arrayData);

    //  单通道电阻读取命令，暂未生效
    QByteArray data;
    unsigned char send_data[] = {0xF0,0x01,0xA1,0x0D,0x0A};
    data.append(send_data[0]);  // 十六进制的F0
    data.append(send_data[1]);  // 十六进制的01
    data.append(send_data[2]);  // 十六进制的A1
    data.append(send_data[3]);  // 十六进制的0D
    data.append(send_data[4]);  // 十六进制的0A
    //    data = data.toHex(' ');
    //    socket->write(data);

    qDebug()<<  "单通道电阻读取命令:"  << data;

}
/************************ END ************************/


/****************** 设置环形进度条相关 ******************/
void infoWindow::setCircleProgressBar(int value)
{
    qreal tmpValue = value;
    QString text = QString::number(tmpValue,'f',0).append("%");
    QString text3 = QString::number(tmpValue,'f',1);

}
/************************ END ************************/



void infoWindow::initPlot()
{
    setupGradients();
    // ------------------- Vloss 图表设置 -------------------
     // 定义柱状图的起始和结束位置

     // 准备数据（5个点）
     QVector<double> xVloss = {1, 2, 3, 4, 5.5};  // X 轴应为离散整数
     QVector<double> yVloss = {0, 0, 0, 0, 0};

     // 创建柱状图组（用于管理柱子的间距）
     // 初始化 barGroup
     barGroup = new QCPBarsGroup(ui->QCustom_Vloss);
     barGroup->setSpacingType(QCPBarsGroup::stPlotCoords);  // ✅ 以 X 轴数据单位计算间距
     barGroup->setSpacing(0.7);  // ✅ 两个柱子相隔 0.5 个 X 轴单位

     // 为每个柱子设置颜色（根据高度调整）
     for (int i = 0; i < 5; ++i) {
         QCPBars *bar = new QCPBars(ui->QCustom_Vloss->xAxis, ui->QCustom_Vloss->yAxis);
         bar->setData(QVector<double>{xVloss[2]}, QVector<double>{yVloss[i]});

         // 根据柱子的高度设定颜色
         if (yVloss[i] >= SEVERE) {
             bar->setBrush(QBrush(RedGradient));
         } else if (yVloss[i] >= MODERATE) {
             bar->setBrush(QBrush(OrangeGradient));
         } else {
             bar->setBrush(QBrush(GreenGradient));
         }

         bar->setWidth(0.3); // 柱子宽度（占X轴单位长度的比例）
         bar->setBarsGroup(barGroup); // 加入柱状图组
         bar->setPen(Qt::NoPen); // 去除边框
     }

     // 将柱状图移动到 "abovemain" 图层，确保在网格之上
     ui->QCustom_Vloss->addLayer("abovemain", ui->QCustom_Vloss->layer("main"), QCustomPlot::limAbove);
     ui->QCustom_Vloss->addLayer("belowmain", ui->QCustom_Vloss->layer("main"), QCustomPlot::limBelow);

     // 显示左侧 y 轴
     ui->QCustom_Vloss->yAxis->setVisible(true);


     ui->QCustom_Vloss->yAxis2->setVisible(true);  // 显示右侧 Y 轴

     // 设置网格线颜色为浅灰色

     ui->QCustom_Vloss->xAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
     ui->QCustom_Vloss->yAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
     ui->QCustom_Vloss->yAxis2->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
     ui->QCustom_Vloss->xAxis->grid()->setSubGridPen(QPen(QColor(150, 150, 150), 1, Qt::DotLine));
     ui->QCustom_Vloss->yAxis->grid()->setSubGridPen(QPen(QColor(150, 150, 150), 1, Qt::DotLine));
     ui->QCustom_Vloss->yAxis2->grid()->setSubGridPen(QPen(QColor(150, 150, 150), 1, Qt::DotLine));
     ui->QCustom_Vloss->xAxis->grid()->setSubGridVisible(false);
     ui->QCustom_Vloss->yAxis->grid()->setSubGridVisible(false);
     ui->QCustom_Vloss->yAxis2->grid()->setSubGridVisible(false);
     ui->QCustom_Vloss->xAxis->grid()->setZeroLinePen(Qt::NoPen);
     ui->QCustom_Vloss->yAxis->grid()->setZeroLinePen(Qt::NoPen);

     QPen axisPen1(QColor(200, 200, 200), 1);
     ui->QCustom_Vloss->yAxis2->setBasePen(axisPen1);  // 设置基线颜色
     ui->QCustom_Vloss->yAxis2->setTickPen(axisPen1);  // 设置刻度线颜色
     ui->QCustom_Vloss->yAxis2->setSubTickPen(axisPen1); // 设置子刻度线颜色

     // 禁用右侧 Y 轴的主刻度、子刻度和刻度标签
     ui->QCustom_Vloss->yAxis2->setTicks(false);          // 禁用主刻度
     ui->QCustom_Vloss->yAxis2->setSubTicks(false);       // 禁用子刻度
     ui->QCustom_Vloss->yAxis2->setTickLabels(false);     // 禁用刻度标签


     // 设置Vloss图表的背景为白色渐变
     QLinearGradient plotGradientVloss;
     plotGradientVloss.setStart(0, 0);
     plotGradientVloss.setFinalStop(0, 350);
     plotGradientVloss.setColorAt(0, QColor("#FFFFFF")); // 白色
     plotGradientVloss.setColorAt(1, QColor("#FDFDFF")); // 浅蓝色
     ui->QCustom_Vloss->setBackground(QBrush(plotGradientVloss));

     // 设置坐标系背景为白色渐变
     QLinearGradient axisRectGradientVloss;
     axisRectGradientVloss.setStart(0, 0);
     axisRectGradientVloss.setFinalStop(0, 350);
     axisRectGradientVloss.setColorAt(0, QColor("#FFFFFF")); // 白色
     axisRectGradientVloss.setColorAt(1, QColor("#FDFDFF")); // 浅蓝色
     ui->QCustom_Vloss->axisRect()->setBackground(QBrush(axisRectGradientVloss));

     // 重新缩放坐标轴并设置Y轴范围
     ui->QCustom_Vloss->rescaleAxes();
     ui->QCustom_Vloss->yAxis->setRange(0, 1);

     // 调整X轴范围，添加两端的间距
     ui->QCustom_Vloss->xAxis->setRange(0.5, 5.5);  // 使 X 轴包含 1~5

     // 隐藏Vloss图表的X轴和Y轴的刻度和标签
//     ui->QCustom_Vloss->xAxis->setTicks(false);
//     ui->QCustom_Vloss->yAxis->setTicks(false);
//     ui->QCustom_Vloss->xAxis->setTickLabels(false);
//     ui->QCustom_Vloss->yAxis->setTickLabels(false);

     // 设置Vloss图表坐标轴为浅灰色
     QPen axisPen(QColor(200, 200, 200), 1); // 浅灰色画笔
     ui->QCustom_Vloss->xAxis->setBasePen(axisPen); // 设置X轴基线为浅灰色
     ui->QCustom_Vloss->yAxis->setBasePen(axisPen); // 设置Y轴基线为浅灰色
     ui->QCustom_Vloss->xAxis->setTickPen(axisPen); // 设置X轴刻度线为浅灰色
     ui->QCustom_Vloss->yAxis->setTickPen(axisPen); // 设置Y轴刻度线为浅灰色
     ui->QCustom_Vloss->xAxis->setSubTickPen(axisPen); // 设置X轴子刻度线为浅灰色
     ui->QCustom_Vloss->yAxis->setSubTickPen(axisPen); // 设置Y轴子刻度线为浅灰色
     ui->QCustom_Vloss->yAxis->setSubTicks(false);  // 禁用 y 轴子刻度

//     ui->QCustom_Vloss->yAxis->ticker()->setTickCount(2); //2个主刻度
//     ui->QCustom_Vloss->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);//可读性优于设置

     // 创建一个固定步长的 ticker
     QSharedPointer<QCPAxisTickerFixed> fixedTicker = QSharedPointer<QCPAxisTickerFixed>::create();
     fixedTicker->setTickStep(0.5); // 设置固定步长为 0.5
     // 设置 X 轴使用固定步长的 ticker
     ui->QCustom_Vloss->yAxis->setTicker(fixedTicker);

     // 创建 QFont 对象并设置字体属性
     QFont font("Arial", 14, QFont::Bold);  // 设置字体为 Arial，大小为 10，粗体
     // 设置 X 轴刻度标签的字体
     ui->QCustom_Vloss->xAxis->setTickLabelFont(font);
     // 设置 Y 轴刻度标签的字体
     ui->QCustom_Vloss->yAxis->setTickLabelFont(font);
     ui->QCustom_Vloss->xAxis->setTickLabelColor(QColor(150, 150, 150)); // 设置X轴刻度标签颜色为浅灰色
     ui->QCustom_Vloss->yAxis->setTickLabelColor(QColor(150, 150, 150)); // 设置Y轴刻度标签颜色为浅灰色



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     // ------------------- Averagepower 图表设置 -------------------
     // 创建Averagepower的柱状图
     QVector<double> xFatigue = {1, 2, 3, 4, 5.5};  // X 轴应为离散整数
     QVector<double> yFatigue = {0, 0, 0, 0, 0};

     FatiguebarGroup = new QCPBarsGroup(ui->QCustom_Averagepower);
     FatiguebarGroup->setSpacingType(QCPBarsGroup::stPlotCoords);  // ✅ 以 X 轴数据单位计算间距
     FatiguebarGroup->setSpacing(0.7);  // ✅ 两个柱子相隔 0.5 个 X 轴单位

     // 为每个柱子设置颜色（根据高度调整）
     for (int i = 0; i < 5; ++i) {
         QCPBars *bar = new QCPBars(ui->QCustom_Averagepower->xAxis, ui->QCustom_Averagepower->yAxis);
         bar->setData(QVector<double>{xFatigue[2]}, QVector<double>{yFatigue[i]});

         bar->setBrush(QBrush(GreenGradient));

         bar->setWidth(0.3); // 柱子宽度（占X轴单位长度的比例）
         bar->setBarsGroup(FatiguebarGroup); // 加入柱状图组
         bar->setPen(Qt::NoPen); // 去除边框
     }


     // 将柱状图移动到 "abovemain" 图层，确保在网格之上
     ui->QCustom_Averagepower->addLayer("abovemain", ui->QCustom_Averagepower->layer("main"), QCustomPlot::limAbove);
     ui->QCustom_Averagepower->addLayer("belowmain", ui->QCustom_Averagepower->layer("main"), QCustomPlot::limBelow);

     ui->QCustom_Averagepower->yAxis2->setVisible(true);

     // 设置网格线颜色为浅灰色
     ui->QCustom_Averagepower->xAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
     ui->QCustom_Averagepower->yAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
     ui->QCustom_Averagepower->xAxis->grid()->setSubGridPen(QPen(QColor(150, 150, 150), 1, Qt::DotLine));
     ui->QCustom_Averagepower->yAxis->grid()->setSubGridPen(QPen(QColor(150, 150, 150), 1, Qt::DotLine));
     ui->QCustom_Averagepower->xAxis->grid()->setSubGridVisible(false);
     ui->QCustom_Averagepower->yAxis->grid()->setSubGridVisible(false);
     ui->QCustom_Averagepower->xAxis->grid()->setZeroLinePen(Qt::NoPen);
     ui->QCustom_Averagepower->yAxis->grid()->setZeroLinePen(Qt::NoPen);

     // 设置Fatigue图表的背景为白色渐变
     QLinearGradient plotGradientFatigue;
     plotGradientFatigue.setStart(0, 0);
     plotGradientFatigue.setFinalStop(0, 350);
     plotGradientFatigue.setColorAt(0, QColor("#FFFFFF")); // 白色
     plotGradientFatigue.setColorAt(1, QColor("#FDFDFF")); // 浅蓝色
     ui->QCustom_Averagepower->setBackground(QBrush(plotGradientFatigue));

     // 设置坐标系背景为白色渐变
     QLinearGradient axisRectGradientFatigue;
     axisRectGradientFatigue.setStart(0, 0);
     axisRectGradientFatigue.setFinalStop(0, 350);
     axisRectGradientFatigue.setColorAt(0, QColor("#FFFFFF")); // 白色
     axisRectGradientFatigue.setColorAt(1, QColor("#FDFDFF")); // 浅蓝色
     ui->QCustom_Averagepower->axisRect()->setBackground(QBrush(axisRectGradientFatigue));

     // 重新缩放坐标轴并设置Y轴范围
     ui->QCustom_Averagepower->rescaleAxes();
     ui->QCustom_Averagepower->yAxis->setRange(0, 100);
     ui->QCustom_Averagepower->yAxis->grid()->setLayer("belowmain");

     // 调整X轴范围，添加两端的间距
     ui->QCustom_Averagepower->xAxis->setRange(0.5, 5.5);  // 使 X 轴包含 1~5
     // 隐藏Fatigue图表的X轴和Y轴的刻度和标签
//     ui->QCustom_Averagepower->xAxis->setTicks(false);
//     ui->QCustom_Averagepower->yAxis->setTicks(false);
//     ui->QCustom_Averagepower->xAxis->setTickLabels(false);
//     ui->QCustom_Averagepower->yAxis->setTickLabels(false);

     // 设置Fatigue图表坐标轴为浅灰色
     ui->QCustom_Averagepower->xAxis->setBasePen(axisPen); // 设置X轴基线为浅灰色
     ui->QCustom_Averagepower->yAxis->setBasePen(axisPen); // 设置Y轴基线为浅灰色
     ui->QCustom_Averagepower->xAxis->setTickPen(axisPen); // 设置X轴刻度线为浅灰色
     ui->QCustom_Averagepower->yAxis->setTickPen(axisPen); // 设置Y轴刻度线为浅灰色
     ui->QCustom_Averagepower->xAxis->setSubTickPen(axisPen); // 设置X轴子刻度线为浅灰色
     ui->QCustom_Averagepower->yAxis->setSubTickPen(axisPen); // 设置Y轴子刻度线为浅灰色

     ui->QCustom_Averagepower->yAxis2->setBasePen(axisPen1);  // 设置基线颜色
     ui->QCustom_Averagepower->yAxis2->setTickPen(axisPen1);  // 设置刻度线颜色
     ui->QCustom_Averagepower->yAxis2->setSubTickPen(axisPen1); // 设置子刻度线颜色
     ui->QCustom_Averagepower->yAxis2->setTickLabelColor(QColor(200, 200, 200));  // 设置刻度标签颜色

     // 禁用右侧 Y 轴的主刻度、子刻度和刻度标签
     ui->QCustom_Averagepower->yAxis2->setTicks(false);          // 禁用主刻度
     ui->QCustom_Averagepower->yAxis2->setSubTicks(false);       // 禁用子刻度
     ui->QCustom_Averagepower->yAxis2->setTickLabels(false);     // 禁用刻度标签

     // 创建一个固定步长的 ticker
     QSharedPointer<QCPAxisTickerFixed> fixedTicker2 = QSharedPointer<QCPAxisTickerFixed>::create();
     fixedTicker2->setTickStep(50); // 设置固定步长为 0.5
     // 设置 X 轴使用固定步长的 ticker
     ui->QCustom_Averagepower->yAxis->setTicker(fixedTicker2);


     // 设置 X 轴刻度标签的字体
     ui->QCustom_Averagepower->xAxis->setTickLabelFont(font);
     // 设置 Y 轴刻度标签的字体
     ui->QCustom_Averagepower->yAxis->setTickLabelFont(font);
     ui->QCustom_Averagepower->xAxis->setTickLabelColor(QColor(150, 150, 150)); // 设置X轴刻度标签颜色为浅灰色
     ui->QCustom_Averagepower->yAxis->setTickLabelColor(QColor(150, 150, 150)); // 设置Y轴刻度标签颜色为浅灰色

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);



}

void infoWindow::setupGradients()
{
    OrangeGradient.setCoordinateMode(QGradient::ObjectBoundingMode); // 使用对象边界坐标模式
    OrangeGradient.setStart(0, 0); // 渐变起点
    OrangeGradient.setFinalStop(0, 1); // 渐变终点（垂直方向）
    OrangeGradient.setColorAt(1, QColor("#FEB052"));   // 开始颜色：浅白色
    OrangeGradient.setColorAt(0, QColor("#FF8A00")); // 结束颜色：橙色

    // 设置红渐变
    RedGradient.setCoordinateMode(QGradient::ObjectBoundingMode); // 使用对象边界坐标模式
    RedGradient.setStart(0, 0); // 渐变起点
    RedGradient.setFinalStop(0, 1); // 渐变终点（垂直方向）
    RedGradient.setColorAt(0, QColor("#FF2619"));   // 开始颜色：大红色
    RedGradient.setColorAt(1, QColor("#F6AD92")); // 结束颜色：橙红色

    // 设置绿渐变
    GreenGradient.setCoordinateMode(QGradient::ObjectBoundingMode); // 使用对象边界坐标模式
    GreenGradient.setStart(0, 0); // 渐变起点
    GreenGradient.setFinalStop(0, 1); // 渐变终点（垂直方向）
    GreenGradient.setColorAt(0, QColor("#2AD2AD")); // 开始颜色：
    GreenGradient.setColorAt(1, QColor("#A9F0E2")); // 结束颜色：
}


void infoWindow::updateBarGroupData(QCPBarsGroup* barGroup, const QVector<float>& newData)
{
    if (!barGroup) return; // 确保 barGroup 存在
    // qDebug() << "新数据" << newData;

    QList<QCPBars*> barsList = barGroup->bars();
    // 确保 newData 至少有 5 个元素，不足的在前面填充 0
    int datasize = newData.size();
    if (datasize < 5)
    {
        QVector<float> Fill_data = newData;
        while(Fill_data.size() < 5)
        {
            Fill_data.prepend(0.0f); // 在前面填充 0
        }

        for (int i = 0; i < barsList.size(); ++i)
        {
            if (i < Fill_data.size()) {
                // 更新数据
                barsList[i]->setData(QVector<double>{3}, QVector<double>{Fill_data[i]});

                // 动态设置颜色
                if (Fill_data[i] >= SEVERE) {
                    barsList[i]->setBrush(QBrush(RedGradient));
                } else if (Fill_data[i] >= MODERATE) {
                    barsList[i]->setBrush(QBrush(OrangeGradient));
                } else {
                    barsList[i]->setBrush(QBrush(GreenGradient));
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < barsList.size(); ++i)
        {
            int index = datasize - 5 + i;
            if (index >= 0 && index < newData.size()) {
                // 更新数据
                barsList[i]->setData(QVector<double>{3}, QVector<double>{newData[index]});

                // 动态设置颜色
                if (newData[index] >= 0.4) {
                    barsList[i]->setBrush(QBrush(RedGradient));
                } else if (newData[index] >= 0.2) {
                    barsList[i]->setBrush(QBrush(OrangeGradient));
                } else {
                    barsList[i]->setBrush(QBrush(GreenGradient));
                }
            }
        }
    }

    // 重新绘制图表
    ui->QCustom_Vloss->replot();
}

void infoWindow::updateFatigueBarGroupData(QCPBarsGroup* barGroup, const QVector<float>& newData)
{
    if (!barGroup) return; // 确保 barGroup 存在
    //    qDebug() << "新数据" << newData;

    QList<QCPBars*> barsList = barGroup->bars();
    //确保 newData 至少有 5 个元素，不足的在前面填充 0
    int datasize = newData.size();
    if (datasize < 5)
    {
        QVector<float> Fill_data = newData;
        while(Fill_data.size() < 5)
        {
            Fill_data.prepend(0.0f); // 在前面填充 0
        }
        QVector<double> xVloss(5);

        for (int i = 0; i < barsList.size(); ++i)
        {
            // 更新数据
            barsList[i]->setData(QVector<double>{3}, QVector<double>{Fill_data[i]});
            barsList[i]->setBrush(QBrush(GreenGradient));
        }
    }
    else{
        QVector<double> xVloss(5);

        for (int i = 0; i < barsList.size(); ++i)
        {
            // 更新数据
            barsList[i]->setData(QVector<double>{3}, QVector<double>{newData[datasize - 5 + i]});  // 选择最后5个Y轴数据});
            barsList[i]->setBrush(QBrush(GreenGradient));

        }
    }

// 重新绘制图表
ui->QCustom_Vloss->replot();
}


//自建队列，自动修改指针指向位置的数据为当前串口接收的数据
//用于实时数据显示，不用于数据分析
void infoWindow::updateVlossData(float newData)
{
    VlossBuffer_Current_Location += 1;
    Buffer_Position = (VlossBuffer_Current_Location % BufferLength);
//    qDebug() << "the position is"<< PositionforCalibration;
    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    if (VlossBuffer_Vector.size() >= BufferLength) {
        // 添加新的 ECG 数据到容器指定位置
        VlossBuffer_Vector[Buffer_Position] = newData;
    }
    else {
        // 如果数据还未填满，先将数据填满
        VlossBuffer_Vector.append(newData);
    }
}

//自建队列，自动修改指针指向位置的数据为当前串口接收的数据
//用于实时数据显示，不用于数据分析
void infoWindow::updateAveragepowerData(float newData)
{
    AveragepowerBuffer_Current_Location += 1;
    Buffer_Position = (AveragepowerBuffer_Current_Location % BufferLength);
//    qDebug() << "the position is"<< PositionforCalibration;
    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    if (AveragepowerBuffer_Vector.size() >= BufferLength) {
        // 添加新的 ECG 数据到容器指定位置
        AveragepowerBuffer_Vector[Buffer_Position] = newData;
    }
    else {
        // 如果数据还未填满，先将数据填满
        AveragepowerBuffer_Vector.append(newData);
    }
}

/**
*****************************************************************************
*  Copyright (C), 仅供实验室内部使用，未经许可请勿外传
*
*  @file    dataprocessor.cpp
*  @brief   数据分包解析类
*           1. 按协议分包并解析数据,并实现数据的基本调用
*           2. 完成基础的数据滤波,ECG、Resp采用中值滤波
*               Resp除中值滤波外还有RC低通滤波
*           3. (todo)
*
*  @author  liu yizheng
*  @date    2024-03-20
*  @version V1.1.0 2024-05-20
*  @advice  尽量不要将各个功能都在同一文件中实现
*           文件解耦会极大提高工程可扩展性、可测试性,保证软件效率和质量
*----------------------------------------------------------------------------
*  @note 历史版本     修改人员        修改日期        修改内容
*  @note v1.0.0      kdh           2024-03-20     创建
*  @note v1.0.1      kdh           2024-04-08     改造成类
*  @note v1.0.2      kdh           2024-04-20     滤波实现
*****************************************************************************
**/
#include "dataprocessor.h"

void DataProcessor::enqueueData(const QByteArray &data)
{
    m_dataQueue.enqueue(data);
}


void DataProcessor::processQueue()
{
    if (!m_dataQueue.isEmpty()) {
        QByteArray allData = m_dataQueue.dequeue();
        processData(allData);

    }
}

bool DataProcessor::processData(const QByteArray &allData)
{

    if(allData.size() >= 6) // 检查数据长度，其实可以不用了
    {
        QList<QByteArray> parts = allData.split(',');
        QString firstPart = parts.value(1);  // 获取第一个子字符串 这里为什么用1,因为还有一个索引为#
        QString secondPart = parts.value(2);  // 获取第一个子字符串

        bool ok;
        int intValue = firstPart.toInt(&ok);
        float floatValue = secondPart.toFloat(&ok);

        Ele_qua_Data = intValue;
        Res_Data = floatValue;

        return true;
    }
    else
    {
        return false;
    }
}

bool DataProcessor::BleprocessData(const QString &allData)
{
    static uint16_t Filter_cnt = 0;
    static uint16_t Resp_cnt = 0;
    static uint16_t ACC_cnt = 0;
    if(allData.size() == 32) // 检查数据长度，其实可以不用了
    {
        int RESP_ADC =  allData.mid(4,6).toInt(nullptr,16);
        int ECG_ADC =  allData.mid(10,6).toInt(nullptr,16);
        short AX_ADC = allData.mid(16,4).toInt(nullptr,16);
        short AY_ADC = allData.mid(20,4).toInt(nullptr,16);
        short AZ_ADC = allData.mid(24,4).toInt(nullptr,16);

        RESP_Data = ADS1292R_ResptoData(RESP_ADC);
        ECG_Data = ADS1292R_ADCtoData(ECG_ADC);
        AX_Data = MPU6050_ADCtoData(AX_ADC);
        AY_Data = MPU6050_ADCtoData(AY_ADC);
        AZ_Data = MPU6050_ADCtoData(AZ_ADC);

        addMidFilterData(ECG_Data);
        addRespFilterData(RESP_Data);

        addFilterData(AXMidFilter_floatVector,AX_Data,200);
        addFilterData(AYMidFilter_floatVector,AY_Data,200);
        addFilterData(AZMidFilter_floatVector,AZ_Data,200);

        Filter_cnt ++;
        Resp_cnt ++ ;
        ACC_cnt ++;

        if(Filter_cnt >= (500 * 0.8))
        {
            ecg_avg_reg = median(ecgMidFilter_intVector);
            Filter_cnt = 0;

        }
        if(Resp_cnt >= RespFilterLength)
        {
            Resp_avg_reg = median(RespMidFilter_intVector);
            Resp_cnt = 0;
        }

        AX_avg_reg = medianfloat(AXMidFilter_floatVector);
        AY_avg_reg = medianfloat(AYMidFilter_floatVector);
        AZ_avg_reg = medianfloat(AZMidFilter_floatVector);

        ECG_Data = ECG_Data - ecg_avg_reg;
        RESP_Data = RESP_Data - Resp_avg_reg;

        AX_Filter =AX_Data - AX_avg_reg;
        AY_Filter =AY_Data - AY_avg_reg;
        AZ_Filter =AZ_Data - AZ_avg_reg;

        addFilterData(AXArgFilter_floatVector,AX_Filter,8);
        addFilterData(AYArgFilter_floatVector,AY_Filter,8);
        addFilterData(AZArgFilter_floatVector,AZ_Filter,8);

        AX_Data =Average(AXArgFilter_floatVector);
        AY_Data =Average(AYArgFilter_floatVector);
        AZ_Data =Average(AZArgFilter_floatVector);

        RESP_Data = Resp_filter.filter(RESP_Data);

        return true;
    }
    else
    {
        return false;
    }
}


int DataProcessor::ADS1292R_ResptoData(int Type_ADC)
{
    int result;
    float result_float;
    int CHX_data;

    if (Type_ADC > 0x800000)
    {
        result = Type_ADC - 0x1000000;
    }
    else
    {
        result = Type_ADC;
    }
    CHX_data = result;
    result_float = result *2.42f / 12 / (8388607);
    return CHX_data;
}

float DataProcessor::MPU6050_ADCtoData(short Ax_ADC)
{
    float Ax_Data;
    Ax_Data = Ax_ADC *9.8f/ 2048;
    return Ax_Data;
}

int DataProcessor::ADS1292R_ADCtoData(int Type_ADC)
{
    int result;
    float result_float;
    int CHX_data;

    if (Type_ADC > 0x800000)
    {
        result = Type_ADC - 0x1000000;
    }
    else
    {
        result = Type_ADC;
    }
    CHX_data = result>>8;
    result_float = result *2.42f / 12 / (8388607);
    return CHX_data;
}


int16_t DataProcessor::averageDCEstimator(int32_t *p, int x)
{
    *p += ((((int64_t)x * 32768) - *p) / 16);
    return (*p >> 15);
}



int DataProcessor::median(const QVector<int>& data) {
    QVector<int> sortedData = data; // 复制输入数据，以免改变原始数据
    std::sort(sortedData.begin(), sortedData.end()); // 对数据进行排序

    // 计算中位数
    int size = sortedData.size();
    if (size % 2 == 0) {
        return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2;
    } else {
        return sortedData[size / 2];
    }
}



float DataProcessor::medianfloat(const QVector<float>& data) {
    QVector<float> filteredData  = data; // 复制输入数据，以免改变原始数据
    std::sort(filteredData.begin(), filteredData.end()); // 对数据进行排序

    // 计算中位数
    int size = filteredData.size();
    if (size % 2 == 0) {
        return (filteredData[size / 2 - 1] + filteredData[size / 2]) / 2;
    } else {
        return filteredData[size / 2];
    }
}
/************************************************************
 * 均值滤波
 *
 *
 */
float DataProcessor::Average(const QVector<float>& vec) {
    if (vec.isEmpty())
        return 0.0;

    float sum = 0.0;
    foreach (float value, vec) {
        sum += value;
    }
    return sum / vec.size();
}

void DataProcessor::addMidFilterData(int newData)
{
    // 添加新的 ECG 数据到容器尾部
    ecgMidFilter_intVector.append(newData);

    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    while (ecgMidFilter_intVector.size() > 500) {
        ecgMidFilter_intVector.removeFirst();
    }
}

void DataProcessor::addRespFilterData(int newData)
{
    // 添加新的 ECG 数据到容器尾部
    RespMidFilter_intVector.append(newData);

    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    while (RespMidFilter_intVector.size() > RespFilterLength)
    {
        RespMidFilter_intVector.removeFirst();
    }
}


void DataProcessor::addFilterData(QVector<float>& ArgFilter_floatVector,float newData,int AccLength)
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

void DataProcessor::setRespFilterLength(uint32_t length)
{
    RespFilterLength = length;
}


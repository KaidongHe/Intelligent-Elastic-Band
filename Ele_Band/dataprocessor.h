#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QByteArray>
#include <QQueue>
#include <QTimer>
#include <cmath>
#include <QVector>
#include <Resp_filter.h>

class DataProcessor: public QObject
{
    Q_OBJECT


public:
    DataProcessor(QObject *parent = nullptr) : Resp_filter(0.43, 500.0) {
        Q_UNUSED(parent);
        RespFilterLength = 500;
    }
    QVector<float> ecgBuffer;
    QVector<float> respBuffer;
    std::vector<int> rPeaks;

    int32_t ecg_avg_reg; //用于存储ECG的基线
    int32_t Resp_avg_reg;
    int RespFilterLength;
    float AX_avg_reg,AY_avg_reg,AZ_avg_reg;
    float AX_Filter,AY_Filter,AZ_Filter;

    float RESP_Data,AX_Data,AY_Data,AZ_Data;
    int ECG_Data;

    float Res_Data;
    int Ele_qua_Data;


    QVector<int> ecgMidFilter_intVector; //add by antis ecgCacheData,ecgCache
    QVector<int> RespMidFilter_intVector;
    QVector<float> AXMidFilter_floatVector;
    QVector<float> AYMidFilter_floatVector;
    QVector<float> AZMidFilter_floatVector;

    QVector<float> AXArgFilter_floatVector;
    QVector<float> AYArgFilter_floatVector;
    QVector<float> AZArgFilter_floatVector;



    void setRespFilterLength(uint32_t length);

//    explicit DataProcessor(QObject *parent = nullptr);

    void enqueueData(const QByteArray &data);
    void processQueue();
    bool processData(const QByteArray &allData);
    bool BleprocessData(const QString &allData);

    float calculateAverageSlope(const QQueue<float> &dataQueue);
    void calculateSlope(const QQueue<float> &axQueue,const QQueue<float> &ayQueue,const QQueue<float> &azQueue);
    void storeDataForTwoSeconds(float ECG_Data,float RESP_Data);

    void findR();
    double calculateHeartRate();

    int16_t averageDCEstimator(int32_t *p, int x);

    void addMidFilterData(int newData);
    void addRespFilterData(int newData);

    void addFilterData(QVector<float>& ArgFilter_floatVector,float newData,int ACCLength);

    int median(const QVector<int>& data);
    float medianfloat(const QVector<float>& data);
    float Average(const QVector<float>& vec);

    int ADS1292R_ResptoData(int Type_ADC);


signals:
    void dataProcessed(int ECG_Data, float RESP_Data, float AX_Data, float AY_Data, float AZ_Data);
    void accelProcessor(QQueue<float> axQueue,QQueue<float> ayQueue,QQueue<float> azQueue);
    void ecg_respProcessed(float ECG_Data,float RESP_Data);
    void trans_ecgBuff();
    void trans_respBuff();
    void trans_HR(double heartRate);
    void fallDetected();

public slots:

    int ADS1292R_ADCtoData(int Type_ADC);
    float MPU6050_ADCtoData(short Ax_ADC);


private:

    QQueue<QByteArray> m_dataQueue;
    QQueue<float> axQueue,ayQueue,azQueue;
    LowPassFilter Resp_filter; // 1.Fs采样频率（Hz） 2.Fc截止频率（Hz）
};

#endif // DATAPROCESSOR_H

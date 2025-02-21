#ifndef COMMON_WAVE_H
#define COMMON_WAVE_H

#include <QWidget>
#include <QPaintEvent>
#include <QJsonDocument>
#include <QPainter>
#include <QMenu>
#include <QtPrintSupport/QPrinter>
#include "dataprocessor.h"

class CommonWave : public QWidget
{
    Q_OBJECT
public:
    explicit CommonWave(QWidget *parent = nullptr);
    ~CommonWave();

    QVector<int> WaveData_intVector; //add by antis ShowData,for show
    QVector<int> WaveCache_intVector; //add by antis CacheData

    QVector<float> WaveData_floatVector; //add by antis ShowData,for show
    QVector<float> ACCXData_floatVector;
    QVector<float> ACCYData_floatVector;
    QVector<float> ACCZData_floatVector;

    int DrawPenColor;

    uint32_t Wave_Current_Location; //the point now
    uint16_t PositionforCalibration;//校准位置

    int32_t DisplayWaveformLength;


    void ReadEcgData();
    void SetEcgDataShow(int isNext);
    void saveVectorToFile_float();
    void addWaveShowData(int newData);
    void updateWaveData(int newData);
    void updateWaveData_float(float newData);
    void SetdrawColor(int Color);
    void updateDisplayWaveformLength(int w);
    uint32_t returnDisplayWaveformLength(void);



private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawGrid(QPainter &painter, int w, int h, double dDotsPerMM);
    void drawWave(QPainter &painter, int width, int height, double dotsPerMM, double scale = 1.0);
    void mydrawWave(QPainter &painter, int width, int height, double dotsPerMM, double scale = 1.0);
    void DynamicdrawsingleWave(QPainter &painter, int width, int height, double dotsPerMM,int color);
    void StaticdrawsingleWave(QPainter &painter, int width, int height, double dotsPerMM);
    void DynamicdrawWave_float(QPainter &painter, int width, int height,
                                        double dotsPerMM, const QVector<float>& waveData,QColor Wave_color);
    void DynamicdrawMultiWave(QPainter &painter, int width, int height,
                              double dotsPerMM);




    QString Arrcode2Label(int arrcode);

private:
    int m_leadNums; //lead num count: 12 15 18
    int m_sampleRate;   //sample rate: 1000
    QJsonDocument m_waveDoc;
    QMenu *m_pMenu;
    float m_fGain;
    int m_iSpeed;
    bool m_bAntialiasing;
    bool m_bOptimize;//draw ecg graphic more perfect
    bool m_bDrawGrid;
    bool m_bDrawPoint;
    uint32_t SumWaveLen;

signals:



public slots:
    void ongainplusTriggered();
    void ongainsubTriggered();
    void onGain20Triggered();
    void onSpeed25Triggered();
    void onSpeed50Triggered();
    void onSpeed100Triggered();
    void onAntialiasingTriggered();
    void onOptimizeTriggered();
    void onDrawGridTriggered();
    void onDrawPointTriggered();
    void onPrintPreviewTriggered();
    void printPreviewSlot(QPrinter *printer);

};

#endif

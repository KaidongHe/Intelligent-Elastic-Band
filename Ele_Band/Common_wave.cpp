/**
*****************************************************************************
*  Copyright (C), 仅供实验室内部使用，未经许可禁止外传
*
*  @file    Common_wave.cpp
*  @brief   基本绘图窗口
*           1. commonwave窗口，用于三轴加速度以及呼吸波形绘制
*           2. (todo) 将三轴加速度以及呼吸分为两个类进行实现，
*              (better) 更好的办法是实现一个基础的绘图类，然后ecg，resp，imu
*               等绘图类继承自基础绘图类，再基于此实现更高级的功能。
*           3. (todo)波形窗口内,右键菜单功能已经基本实现,在开发过程
*               中修改了相关参数,现无法正常使用，需要调整逻辑及参数后
*               才能正常使用
*           4. 整体架构修改，不仅仅只作为一个普通的波形显示函数，还要具备以下功能：
*               波形长度可设置
*               波形数量可设置
*               波形颜色可设置
*           5. 绘图窗口整体绘图逻辑梳理： (绘图本质是什么？)
*               1- 本质通过改写paintEvent函数，进行绘图实现
*               2- 需要调用绘图函数时，使用update()函数
*               3- 如何调整绘图内容数量(同时显示多少内容，刷新率是多少)？
*
*
*  @author  kdh
*  @date    2024-05-20
*  @version V1.1.1 2024-05-20
*  @advice  尽量不要将各个功能都在同一文件中实现
*           文件解耦会极大提高工程可扩展性、可测试性,保证软件效率和质量
*----------------------------------------------------------------------------
*  @note 历史版本     修改人员        修改日期        修改内容
*  @note v1.0.0      kdh           2023-12-20     创建
*  @note v1.1.0      kdh           2024-05-08     完成功能实现
*  @note v1.1.1      kdh           2024-05-22     修复呼吸波形显示bug(竖线)
*****************************************************************************
**/
#include "Common_wave.h"
#include "common.h"

#define numdots 1

#define TimeZoomRatio 2.1

#define dynamic_mode 0
#define static_mode 1


// 类的构造函数
CommonWave::CommonWave(QWidget *parent) : QWidget(parent)
{
    // 设置一些初始属性和样式
    setAttribute(Qt::WA_DeleteOnClose);
    setStyleSheet("background-color:rgba(0,0,0,1);");


    DrawPenColor = GREEN;
    DisplayWaveformLength = 3000;

    // 初始化一些参数
    m_sampleRate = 500;
    m_fGain = 800.0;
    m_iSpeed = 50;
    m_bAntialiasing = false;
    m_bOptimize = true;
    m_bDrawGrid = false;
    m_bDrawPoint = false;

    // add by antis , ECG Display Related Code
    Wave_Current_Location = 0;//当前数据指针
    PositionforCalibration = 0;


    // 创建右键菜单
    m_pMenu = new QMenu();
    m_pMenu->setStyleSheet("QMenu{\
                           background:rgba(255,255,255,1);\
                           border:none;\
                         }\
                         QMenu::item{\
                           padding:4px 16px;\
                           color:rgba(51,51,51,1);\
                           font-size:12px;\
                         }\
                         QMenu::item:hover{\
                           background-color:#409CE1;\
                         }\
                         QMenu::item:selected{\
                           background-color:#409CE1;\
                         }");
    // 添加Gain子菜单及选项
    QMenu *gain = m_pMenu->addMenu("Gain");
    QAction *gainplus = gain->addAction("5");
    QAction *gainsub = gain->addAction("10");
    QAction *gain20 = gain->addAction("20");
    QActionGroup *gainGroup = new QActionGroup(this);
    gainGroup->addAction(gainplus);
    gainGroup->addAction(gainsub);
    gainGroup->addAction(gain20);
    gainGroup->setExclusive(true);
    gainplus->setCheckable(true);
    gainplus->setChecked(false);
    gainsub->setCheckable(true);
    gainsub->setChecked(true);
    gain20->setCheckable(true);
    gain20->setChecked(false);
    connect(gainplus, SIGNAL(triggered()), this, SLOT(ongainplusTriggered()));
    connect(gainsub, SIGNAL(triggered()), this, SLOT(ongainsubTriggered()));
    connect(gain20, SIGNAL(triggered()), this, SLOT(onGain20Triggered()));

    // 添加其它菜单项，类似处理
    m_pMenu->addSeparator();

    QMenu *speed = m_pMenu->addMenu("Speed");
    QAction *speed25 = speed->addAction("25");
    QAction *speed50 = speed->addAction("50");
    QAction *speed100 = speed->addAction("100");
    QActionGroup *speedGroup = new QActionGroup(this);
    speedGroup->addAction(speed25);
    speedGroup->addAction(speed50);
    speedGroup->addAction(speed100);
    speedGroup->setExclusive(true);
    speed25->setCheckable(true);
    speed25->setChecked(false);
    speed50->setCheckable(true);
    speed50->setChecked(true);
    speed100->setCheckable(true);
    speed100->setChecked(false);

    // 连接右键菜单的信号槽
    connect(speed25, SIGNAL(triggered()), this, SLOT(onSpeed25Triggered()));
    connect(speed50, SIGNAL(triggered()), this, SLOT(onSpeed50Triggered()));
    connect(speed100, SIGNAL(triggered()), this, SLOT(onSpeed100Triggered()));

    m_pMenu->addSeparator();

    QAction *gridAction = m_pMenu->addAction("DrawGrid");
    gridAction->setCheckable(true);
    gridAction->setChecked(true);
    connect(gridAction, SIGNAL(triggered()), this, SLOT(onDrawGridTriggered()));

    m_pMenu->addSeparator();

    QAction *pointAction = m_pMenu->addAction("DrawPoint");
    pointAction->setCheckable(true);
    pointAction->setChecked(true);
    connect(pointAction, SIGNAL(triggered()), this, SLOT(onDrawPointTriggered()));

    m_pMenu->addSeparator();

    QAction *smoothAct = m_pMenu->addAction("Smooth");
    smoothAct->setCheckable(true);
    smoothAct->setChecked(false);
    connect(smoothAct, SIGNAL(triggered()), this, SLOT(onAntialiasingTriggered()));

    m_pMenu->addSeparator();

    QAction *promptEcg = m_pMenu->addAction("Optimize");
    promptEcg->setCheckable(true);
    promptEcg->setChecked(false);
    connect(promptEcg, SIGNAL(triggered()), this, SLOT(onOptimizeTriggered()));

    m_pMenu->addSeparator();

    // 创建右键菜单项 "Print Preview" 的动作
    QAction *printAction = m_pMenu->addAction("Print Preview");
    connect(printAction, SIGNAL(triggered()), this, SLOT(onPrintPreviewTriggered()));

    qDebug()<<"CommonWindow hight" << this->height();

    //清空数据
    ACCXData_floatVector.clear();
    ACCYData_floatVector.clear();
    ACCZData_floatVector.clear();
}

// 类的析构函数
CommonWave::~CommonWave() {
    // 析构函数，释放资源
    delete m_pMenu;
    m_pMenu = nullptr;
}

// 获取鼠标点击位置坐标(想和实际位置对应，但暂时还有一些误差)
void CommonWave::mousePressEvent(QMouseEvent *event) {
    // 获取鼠标点击的坐标
    QPoint mousePos = event->pos();
    mousePos.setX(mousePos.x() * numdots);
    mousePos.setY(mousePos.y() * numdots);
    qDebug() << "Mouse Clicked at: " << mousePos;
    event->accept();
}

// 鼠标右键菜单功能实现
void CommonWave::mouseReleaseEvent(QMouseEvent *event) {
    // 处理鼠标右键释放事件，显示右键菜单
    if (event->button() == Qt::RightButton) {
        m_pMenu->exec(event->globalPos());
    }
    event->accept();
}

// 主要绘制逻辑实现*
void CommonWave::paintEvent(QPaintEvent *event) {
    // 绘制事件处理函数

    QPainter painter(this);
//    painter.fillRect(event->rect(), QBrush(QColor(0, 0, 0, 255))); // 这里设置背景色为黑色
    painter.fillRect(event->rect(), QBrush(QColor(255, 255, 255, 255))); // 这里设置背景色为白色


    int w = this->width(), h = this->height();
    int bigGrid = (5.0 * DOTS_PER_MM);
    int w_processed = w - w % bigGrid;
    int h_processed = h - h % bigGrid;
    updateDisplayWaveformLength(w_processed);

    drawGrid(painter, w_processed, h_processed, DOTS_PER_MM);  //1.绘制网格背景函数 2.DOTS_PER_MM定义在common中 3.在该类中暂时不需要？

    if(DrawPenColor == YELLOW)// 加速度模块为黄色主题 呼吸信号为蓝色主题 ；todo ： 分成两个类来写会不会好点？
    {
        DynamicdrawWave_float(painter, w_processed, h_processed, DOTS_PER_MM,WaveData_floatVector,Qt::yellow);
        //DynamicdrawAccWave(painter, width, height, dotsPerMM,ACCXData_floatVector,Qt::green);
        painter.save();
        QPen pen(Qt::yellow);
        QFont f("Consolas");
        f.setBold(true);
        painter.setPen(pen);
        painter.setFont(f);
//        QString text = QString("F");
//        painter.drawText(10, 20, text);
        painter.restore();
    }
    else if(DrawPenColor == BLUE){
        QColor customColor("#5055EB"); // 使用十六进制值
        DynamicdrawWave_float(painter, w_processed, h_processed, DOTS_PER_MM,WaveData_floatVector,customColor);

        painter.save();
        QPen pen(customColor);
        QFont f("Consolas");
        f.setBold(true);
        painter.setPen(pen);
        painter.setFont(f);
//        QString text = QString("V");
//        painter.drawText(10, 20, text);
        painter.restore();
    }
    else if(DrawPenColor == GREEN){
        QColor customColor("#01DD03"); // 使用十六进制值
        DynamicdrawWave_float(painter, w_processed, h_processed, DOTS_PER_MM,WaveData_floatVector,customColor);

        painter.save();
        QPen pen(customColor);
        QFont f("Consolas");
        f.setBold(true);
        painter.setPen(pen);
        painter.setFont(f);
//        QString text = QString("R");
//        painter.drawText(10, 20, text);
        painter.restore();
    }


//    QString text = QString("Lead:%1 Gain:%2 Speed:%3").arg(m_leadNums).arg(m_fGain).arg(m_iSpeed);
//    painter.drawText(10, 20, text);
    event->accept();
}

// 绘制网格背景函数
void CommonWave::drawGrid(QPainter &painter, int w, int h, double dDotsPerMM) {
    // 绘制背景网格
    painter.save();
    painter.setPen(QColor(253, 180, 218));
    int bigGrid = (5.0 * dDotsPerMM);
    if (m_bDrawGrid) {
        for (int i = 0; i <= w / bigGrid; ++i) {
            painter.drawLine(0, i * bigGrid, w, i * bigGrid);
            painter.drawLine(i * bigGrid, 0, i * bigGrid, h-h%bigGrid);
        }
    }
    if (m_bDrawPoint) {
        for (int x = 0; x <= (w / bigGrid)-1; ++x) {
            for (int y = 0; y <= (h / bigGrid)-1; ++y) { //这里由y <= (h / bigGrid)加上-1，防止点画出格子外
                for (int i = 1; i < 5; ++i) {
                    for (int j = 1; j < 5; ++j) {
                        QPointF p((qreal)(1.0 * x * bigGrid + 1.0 * i * dDotsPerMM), (qreal)(1.0 * y * bigGrid + 1.0 * j * dDotsPerMM));
                        painter.drawPoint(p);
                    }
                }
            }
        }
    }
    painter.restore();
}

// 绘制波形函数实现1（基础波形绘制）
void CommonWave::drawWave(QPainter &painter, int width, int height, double dotsPerMM, double scale) {
    // 绘制心电波形
    double scale_in = scale;

    // 保存当前画家状态
    painter.save();

    // 设置抗锯齿效果
    painter.setRenderHint(QPainter::Antialiasing, m_bAntialiasing);

    // 计算每个像素代表的时间
    float fNumPerPixel = m_sampleRate * 1.0 / (m_iSpeed * dotsPerMM);

    // 计算每个像素代表的电压
    float fPixelPerMv = m_fGain * dotsPerMM;
    float fPixelPerUv = 0.001 * fPixelPerMv;

    // 初始化绘图参数
    int rectWidth = width / 2, rowHeight = height / 6, middleHeight = rowHeight / 2;
    int cols = 0, rows = 0;

    // 根据导联数确定列数和行数
    if (m_leadNums == 12) {
        cols = 2;
        rows = 6;
        rectWidth = width / cols;
        rowHeight = height / rows;
        middleHeight = rowHeight / 2;
    } else if (m_leadNums == 15 || m_leadNums == 18) {
        cols = 3;
        rows = (m_leadNums == 15 ? 5 : 6);
        rectWidth = width / cols;
        rowHeight = height / rows;
        middleHeight = rowHeight / 2;
    }

    // 绘制心电波形
    QJsonArray waveArrs = m_waveDoc.array();
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            // 获取单个导联的波形数据
            QJsonObject singleWaveItem = waveArrs.at(col * rows + row).toObject();
            QString leadName = singleWaveItem["code"].toString();
            QJsonArray waveArr = singleWaveItem["value"].toArray();
            int waveLen = waveArr.size();
            QVector<QPointF> vecPoints;

            // 根据是否优化绘制，计算波形点的坐标
            if (!m_bOptimize) {
                for (int i = 0; i < waveLen; ++i) {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }
                    QPointF p((qreal)(col * rectWidth + i / fNumPerPixel),
                              (qreal)(row * rowHeight + middleHeight - (waveArr[i].toInt() * fPixelPerUv)));
                    vecPoints.append(p);
                }
            } else {
                int numPerPixel = fNumPerPixel + 0.5;
                for (int i = 0; i < waveLen; i += numPerPixel) {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }
                    // 寻找每个小段中的最小和最大值
                    int minIndex = i, maxIndex = i;
                    int minValue = waveArr[i].toInt(), maxValue = waveArr[i].toInt();
                    for (int j = 0; j < numPerPixel; ++j) {
                        if (i + j >= waveLen) {
                            break;
                        }
                        if (minValue > waveArr[i + j].toInt()) {
                            minValue = waveArr[i + j].toInt();
                            minIndex = i + j;
                        }
                        if (maxValue < waveArr[i + j].toInt()) {
                            maxValue = waveArr[i + j].toInt();
                            maxIndex = i + j;
                        }
                    }
                    // 根据最小和最大值确定绘制点的坐标
                    QPointF minPoint((qreal)(col * rectWidth + minIndex / fNumPerPixel),
                                      (qreal)(row * rowHeight + middleHeight - (minValue * fPixelPerUv)));
                    QPointF maxPoint((qreal)(col * rectWidth + maxIndex / fNumPerPixel),
                                      (qreal)(row * rowHeight + middleHeight - (maxValue * fPixelPerUv)));
                    minIndex >= maxIndex ? vecPoints.append(maxPoint) : vecPoints.append(minPoint);
                }
            }

            // 绘制文字标签
            painter.save();
            painter.setPen(QPen(Qt::red));
            painter.setFont(QFont("Helvetica [Cronyx]", 12, 30));
            painter.drawText(col * rectWidth, row * rowHeight + middleHeight, leadName);
            painter.restore();

            // 连接每个绘制点以绘制波形线条
            for (int i = 0; i < vecPoints.size() - 1; ++i) {
                painter.drawLine(vecPoints[i], vecPoints[i + 1]);
            }
        }
    }

    // 恢复画家状态
    painter.restore();
}

// 绘制波形实现2()
void CommonWave::mydrawWave(QPainter &painter, int width, int height, double dotsPerMM, double scale) {
    // 绘制心电波形

    // 保存当前画家状态
    painter.save();

    // 设置抗锯齿效果
    painter.setRenderHint(QPainter::Antialiasing, m_bAntialiasing);

    // 计算每个像素代表的时间
    float fNumPerPixel = m_sampleRate * 1.0 / (m_iSpeed * dotsPerMM);

    // 计算每个像素代表的电压
    float fPixelPerMv = m_fGain * dotsPerMM;
    float fPixelPerUv = 0.001 * fPixelPerMv;

    // 初始化绘图参数
    int rectWidth = width / 2, rowHeight = height / 6, middleHeight = rowHeight / 2;
    int cols = 0, rows = 0;

    // 根据导联数确定列数和行数
    cols = 1;  //列
    rows = 1;  //行
    rectWidth = width / cols;
    rowHeight = height / rows;
    middleHeight = rowHeight / 2;

    // 绘制心电波形
    QJsonArray waveArrs = m_waveDoc.array();
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            // 获取单个导联的波形数据
            QJsonObject singleWaveItem = waveArrs.at(col * rows + row).toObject();
            QString leadName = singleWaveItem["code"].toString();
            QJsonArray waveArr = singleWaveItem["value"].toArray();
            int waveLen = waveArr.size();
            QVector<QPointF> vecPoints;

            // 根据是否优化绘制，计算波形点的坐标
            if (!m_bOptimize) {
                for (int i = 0; i < waveLen; ++i) {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }
                    QPointF p((qreal)(col * rectWidth + i / fNumPerPixel),
                              (qreal)(row * rowHeight + middleHeight - (waveArr[i].toInt() * fPixelPerUv)));
                    vecPoints.append(p);
                }
            } else {
                int numPerPixel = fNumPerPixel + 0.5;
                for (int i = 0; i < waveLen; i += numPerPixel) {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }
                    // 寻找每个小段中的最小和最大值
                    int minIndex = i, maxIndex = i;
                    int minValue = waveArr[i].toInt(), maxValue = waveArr[i].toInt();
                    for (int j = 0; j < numPerPixel; ++j) {
                        if (i + j >= waveLen) {
                            break;
                        }
                        if (minValue > waveArr[i + j].toInt()) {
                            minValue = waveArr[i + j].toInt();
                            minIndex = i + j;
                        }
                        if (maxValue < waveArr[i + j].toInt()) {
                            maxValue = waveArr[i + j].toInt();
                            maxIndex = i + j;
                        }
                    }
                    // 根据最小和最大值确定绘制点的坐标
                    QPointF minPoint((qreal)(col * rectWidth + minIndex / fNumPerPixel),
                                     (qreal)(row * rowHeight + middleHeight - (minValue * fPixelPerUv)));
                    QPointF maxPoint((qreal)(col * rectWidth + maxIndex / fNumPerPixel),
                                     (qreal)(row * rowHeight + middleHeight - (maxValue * fPixelPerUv)));
                    minIndex >= maxIndex ? vecPoints.append(maxPoint) : vecPoints.append(minPoint);
                }
            }

            // 绘制文字标签
            painter.save();
            painter.setPen(QPen(Qt::red));
            painter.setFont(QFont("Helvetica [Cronyx]", 12, 30));
            painter.drawText(col * rectWidth, row * rowHeight + middleHeight, leadName);
            painter.restore();

            // 连接每个绘制点以绘制波形线条
            for (int i = 0; i < vecPoints.size() - 1; ++i) {
                painter.drawLine(vecPoints[i], vecPoints[i + 1]);
            }
        }
    }

    // 恢复画家状态
    painter.restore();
}

// 动态绘制函数(实时波形绘制实现) 呼吸波形实现
void CommonWave::DynamicdrawsingleWave(QPainter &painter, int width, int height, double dotsPerMM,int color) {
    // 绘制心电波形

    // 保存当前画家状态
    painter.save();

    // 设置抗锯齿效果
    painter.setRenderHint(QPainter::Antialiasing, m_bAntialiasing);

    // 计算每个像素代表的时间
    float fNumPerPixel = numdots; // m_sampleRate * 1.0 / (m_iSpeed * dotsPerMM);

    // 计算每个像素代表的电压
    float fPixelPerMv = m_fGain * dotsPerMM;
    float fPixelPerUv = 0.0005 * fPixelPerMv;

    // 初始化绘图参数
    int rectWidth = width / 2, rowHeight = height / 6, middleHeight = rowHeight / 2;
    int cols = 0, rows = 0;

    // 追踪擦除的点位
    uint16_t ErasePos = 0;

    // 根据导联数确定列数和行数
    cols = 1;  //列
    rows = 1;  //行
    rectWidth = width / cols;
    rowHeight = height / rows;
    middleHeight = rowHeight / 2;

    // Ecg waveform was drawn
    for (int col = 0; col < cols; ++col)
    {
        for (int row = 0; row < rows; ++row)
        {
            int waveLen = WaveData_intVector.size();
//            qDebug() << "the wavelen is"<< waveLen;
            QVector<QPointF> vecPoints;
            // 根据是否优化绘制，计算波形点的坐标
            if (!m_bOptimize)
            {
                for (int i = 0; i < waveLen; ++i)
                {
                    if (i / fNumPerPixel > (rectWidth+7) - DOTS_PER_MM * 2)
                    {
                        break;
                    }

                    ErasePos = PositionforCalibration;

                    QPointF p((qreal)(col * rectWidth + i / fNumPerPixel),
                              (qreal)(row * rowHeight + middleHeight - ((WaveData_intVector.value(i)) * fPixelPerUv))); //Subtract the median here by 2048
                    vecPoints.append(p);
                }
            }
            else
            {
                int numPerPixel = fNumPerPixel + 0.5; // 四舍五入
                for (int i = 0; i < waveLen; i += numPerPixel)
                {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }
                    // 寻找每个小段中的最小和最大值
                    int minIndex = i, maxIndex = i;
                    int minValue = WaveData_intVector[i], maxValue = WaveData_intVector[i];
                    // 遍历这一小段的最小值和最大值，这一小段的长度由 numdots 决定
                    for (int j = 0; j < numPerPixel; ++j)
                    {
                        if (i + j >= waveLen) {
                            break;
                        }
                        if (minValue > WaveData_intVector[i + j]) {
                            minValue = WaveData_intVector[i + j];
                            minIndex = i + j;
                        }
                        if (maxValue < WaveData_intVector[i + j]) {
                            maxValue = WaveData_intVector[i + j];
                            maxIndex = i + j;
                        }
                    }
                    // 根据最小和最大值确定绘制点的坐标
                    QPointF minPoint((qreal)(col * rectWidth + minIndex / fNumPerPixel),
                                     (qreal)(row * rowHeight + middleHeight - (minValue * fPixelPerUv)));
                    QPointF maxPoint((qreal)(col * rectWidth + maxIndex / fNumPerPixel),
                                     (qreal)(row * rowHeight + middleHeight - (maxValue * fPixelPerUv)));


                        ErasePos = PositionforCalibration;

                    //continue;
                    minIndex >= maxIndex ? vecPoints.append(maxPoint) : vecPoints.append(minPoint);

                }
            }
            painter.save();
            QPen pen(Qt::blue);// 创建一个QPen
            if(DrawPenColor == BLUE)// 加速度模块为黄色主题 呼吸信号为蓝色主题 ；todo ： 分成两个类来写会不会好点？
            {
            pen.setColor(Qt::blue);  // 将颜色修改为红色
            }
            else if(DrawPenColor == YELLOW)// 加速度模块为黄色主题 呼吸信号为蓝色主题 ；todo ： 分成两个类来写会不会好点？
            {
            pen.setColor(Qt::yellow);// 创建一个QPen
            }
            else if(DrawPenColor == GREEN)// 加速度模块为黄色主题 呼吸信号为蓝色主题 ；todo ： 分成两个类来写会不会好点？
            {
            pen.setColor(Qt::green);// 创建一个QPen
            }
            pen.setWidth(2);// 设置线宽为2像素
            // 使用QPen对象绘制线条
            painter.setRenderHint(QPainter::HighQualityAntialiasing);
            painter.setPen(pen);
//             连接每个绘制点以绘制波形线条
            for (int i = 1; i < vecPoints.size() - 1; ++i) //从1开始避免出现显示bug(出现竖线)
            {
                if (i >= ErasePos && i <= ErasePos+121 ) //跳过分界点达到擦除效果
                {
                    continue;
                }
                painter.drawLine(vecPoints[i], vecPoints[i + 1]);
            }
            painter.restore();
        }
    }

    // 恢复画家状态
    painter.restore();
}


void CommonWave::DynamicdrawWave_float(QPainter &painter, int width, int height,
                                    double dotsPerMM, const QVector<float>& waveData, QColor Wave_color) {
    // 保存当前画家状态
    painter.save();

    // 设置抗锯齿效果
    painter.setRenderHint(QPainter::Antialiasing, m_bAntialiasing);

    // 计算每个像素代表的时间
    float fNumPerPixel = numdots; // 每个像素的时间


    // 计算每个像素代表的电压（初始单位）
    float fPixelPerMv = m_fGain * dotsPerMM;

    // 初始化绘图参数
    int rectWidth, rowHeight, middleHeight;
    int cols = 1, rows = 1;
    rectWidth = width / cols;
    rowHeight = height / rows;
    middleHeight = rowHeight / 2;

    // 计算当前波形数据的最小值和最大值 -----> 数据缩放的关键
    float minValue = *std::min_element(waveData.begin(), waveData.end());
    float maxValue = *std::max_element(waveData.begin(), waveData.end());

    // 追踪擦除的点位
    uint16_t ErasePos = 0;


    // 计算缩放因子，将波形数据映射到屏幕高度
    float verticalScale = (rowHeight) / ((maxValue - minValue) *  2.1); // 0.8 是缩放系数，避免波形接触上下边缘

    // Ecg waveform was drawn
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            int waveLen = waveData.size();
            QVector<QPointF> vecPoints;

            // 根据是否优化绘制，计算波形点的坐标
            if (!m_bOptimize) { //默认跳过
                for (int i = 0; i < waveLen; ++i) {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) { // 超过了屏幕边界
                        break;
                    }
                        ErasePos = PositionforCalibration;

                    QPointF p(
                        (qreal)(col * rectWidth + i / fNumPerPixel), // 横坐标 其实只有i / fNumPerPixel起效果
                        (qreal)(row * rowHeight + middleHeight - ((waveData.value(i)) * verticalScale)) // 纵坐标进行缩放
                    );
                    vecPoints.append(p);
                }
            } else { //默认进入
                int numPerPixel = fNumPerPixel + 0.5;
                for (int i = 0; i < waveLen; i += numPerPixel) {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }

                    // 寻找每个小段中的最小和最大值
                    int minIndex = i, maxIndex = i;
                    float minValueInSegment = waveData[i], maxValueInSegment = waveData[i];
                    for (int j = 0; j < numPerPixel; ++j) {
                        if (i + j >= waveLen) break;
                        if (minValueInSegment > waveData[i + j]) {
                            minValueInSegment = waveData[i + j];
                            minIndex = i + j;
                        }
                        if (maxValueInSegment < waveData[i + j]) {
                            maxValueInSegment = waveData[i + j];
                            maxIndex = i + j;
                        }
                    }

                    QPointF minPoint(
                        (qreal)(col * rectWidth + minIndex / fNumPerPixel * TimeZoomRatio),
                        (qreal)(row * rowHeight + middleHeight - ((minValueInSegment - minValue) * verticalScale))
                    );
                    QPointF maxPoint(
                        (qreal)(col * rectWidth + maxIndex / fNumPerPixel * TimeZoomRatio),
                        (qreal)(row * rowHeight + middleHeight - ((maxValueInSegment - minValue) * verticalScale))
                    );

                        ErasePos = PositionforCalibration;

                    minIndex >= maxIndex ? vecPoints.append(maxPoint) : vecPoints.append(minPoint);
                }
            }


            // 绘制波形线条
            painter.save();
            QPen pen;
            pen.setWidth(4);
            pen.setColor(Wave_color);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);
            painter.setPen(pen);

            for (int i = 1; i < vecPoints.size() - 1; ++i) //从1开始避免出现显示bug(出现竖线) by antis 20240522
            {
                if (i >= ErasePos && i <= ErasePos+ (121/TimeZoomRatio) ) //跳过分界点达到擦除效果
                {
                    continue;
                }
                painter.drawLine(vecPoints[i], vecPoints[i + 1]);
            }
            painter.restore();
        }
    }

    // 恢复画家状态
    painter.restore();
}


//数据库绘制函数
void CommonWave::StaticdrawsingleWave(QPainter &painter, int width, int height, double dotsPerMM) {
    // 保存当前画家状态
    painter.save();

    // 设置抗锯齿效果
    painter.setRenderHint(QPainter::Antialiasing, m_bAntialiasing);

    // 计算每个像素代表的时间
    float fNumPerPixel = numdots;//m_sampleRate * 1.0 / (m_iSpeed * dotsPerMM);

    // 计算每个像素代表的电压
    float fPixelPerMv = m_fGain * dotsPerMM;
    float fPixelPerUv = 0.001 * fPixelPerMv;

    // 初始化绘图参数
    int rectWidth = width / 2, rowHeight = height / 6, middleHeight = rowHeight / 2;
    int cols = 0, rows = 0;
    int midValue = 0;

    // 根据导联数确定列数和行数
    cols = 1;  //列
    rows = 1;  //行
    rectWidth = width / cols;
    rowHeight = height / rows;
    middleHeight = rowHeight / 2;

    // Ecg waveform was drawn
    for (int col = 0; col < cols; ++col)
    {
        for (int row = 0; row < rows; ++row)
        {
            int waveLen = WaveData_intVector.size();
            QVector<QPointF> vecPoints;
            // 根据是否优化绘制，计算波形点的坐标
            if (!m_bOptimize)
            {
                for (int i = 0; i < waveLen; ++i)
                {
                    if (i / fNumPerPixel > (rectWidth+7) - DOTS_PER_MM * 2)
                    {
//                        qDebug() << "the wavelen is"<< i;
                        break;
                    }
                    QPointF p((qreal)(col * rectWidth + i / fNumPerPixel),
                              (qreal)(row * rowHeight + middleHeight - ((WaveData_intVector.value(i)-2048) * fPixelPerUv))); //Subtract the median here by 2048
                    vecPoints.append(p);
                }
            }
            else
            {
                int numPerPixel = fNumPerPixel + 0.5;
                for (int i = 0; i < waveLen; i += numPerPixel)
                {
                    if (i / fNumPerPixel > rectWidth - DOTS_PER_MM * 2) {
                        break;
                    }
                    // 寻找每个小段中的最小和最大值
                    int minIndex = i, maxIndex = i;
                    int minValue = WaveData_intVector[i], maxValue = WaveData_intVector[i];
                    for (int j = 0; j < numPerPixel; ++j)
                    {
                        if (i + j >= waveLen) {
                            break;
                        }
                        if (minValue > WaveData_intVector[i + j]) {
                            minValue = WaveData_intVector[i + j];
                            minIndex = i + j;
                        }
                        if (maxValue < WaveData_intVector[i + j]) {
                            maxValue = WaveData_intVector[i + j];
                            maxIndex = i + j;
                        }
                    }
                    // 根据最小和最大值确定绘制点的坐标
                    QPointF minPoint((qreal)(col * rectWidth + minIndex / fNumPerPixel),
                                     (qreal)(row * rowHeight + middleHeight - (minValue * fPixelPerUv)));
                    QPointF maxPoint((qreal)(col * rectWidth + maxIndex / fNumPerPixel),
                                     (qreal)(row * rowHeight + middleHeight - (maxValue * fPixelPerUv)));
                    minIndex >= maxIndex ? vecPoints.append(maxPoint) : vecPoints.append(minPoint);
                }
            }

            // 绘制文字标签
            painter.save();
            painter.setPen(QPen(Qt::red));
            painter.setFont(QFont("Helvetica [Cronyx]", 12, 30));
            //painter.drawText(col * rectWidth, row * rowHeight + middleHeight, leadName);
            painter.restore();

            // 连接每个绘制点以绘制波形线条
            for (int i = 0; i < vecPoints.size() - 1; ++i)
            {
                painter.drawLine(vecPoints[i], vecPoints[i + 1]);
            }
        }
    }

    // 恢复画家状态
    painter.restore();
}

void CommonWave::ongainplusTriggered() {
    // 处理 Gain 为 5 的动作触发事件
    m_fGain *= 2.0;
    update();
}

void CommonWave::ongainsubTriggered() {
    // 处理 Gain 为 10 的动作触发事件
    m_fGain /= 2.0;
    update();
}

void CommonWave::onGain20Triggered() {
    // 处理 Gain 为 20 的动作触发事件
    m_fGain = 20.0;
    update();
}

void CommonWave::onSpeed25Triggered() {
    // 处理 speed 为 25 的动作触发事件
    m_iSpeed = 25;
    update();
}

void CommonWave::onSpeed50Triggered() {
    // 处理 speed 为 50 的动作触发事件
    m_iSpeed = 50;
    update();
}

void CommonWave::onSpeed100Triggered() {
    // 处理 speed 为 100 的动作触发事件
    m_iSpeed = 100;
    update();
}

void CommonWave::onAntialiasingTriggered() {
    m_bAntialiasing = !m_bAntialiasing;
    update();
}

void CommonWave::onOptimizeTriggered() {
    m_bOptimize = !m_bOptimize;
    update();
}

void CommonWave::onDrawGridTriggered() {
    m_bDrawGrid = !m_bDrawGrid;
    update();
}

void CommonWave::onDrawPointTriggered() {
    m_bDrawPoint = !m_bDrawPoint;
    update();
}

void CommonWave::onPrintPreviewTriggered() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    printer.setPageSize(QPrinter::Custom);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPaperSize(QPagedPaintDevice::A4);
    QPrintPreviewDialog preview(&printer);
    preview.setWindowFlags(preview.windowFlags() & Qt::WindowCloseButtonHint);
    preview.setWindowTitle("Print Preview");
    QScreen *screen = QGuiApplication::screens()[0];
    int availableWidth = screen->availableGeometry().width();
    int availableHeight = screen->availableGeometry().height();
    preview.setMinimumSize(availableWidth, availableHeight);
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreviewSlot(QPrinter *)));
    preview.exec();
}

void CommonWave::printPreviewSlot(QPrinter *printer) {
    double dDotsPerMMForPrinter = printer->pageRect().width() / 297.0;  //A4纸的尺寸是297mm*210mm 如果是横着打印 则297为宽度
    double dScale = dDotsPerMMForPrinter / DOTS_PER_MM; //打印机的窗口和桌面窗口的尺寸相比 放大倍数 用于调整文字
    int w = printer->pageRect().width() - 10 * dDotsPerMMForPrinter,    //边框有1cm左右 减去1cm的像素宽度防止绘制时显示不完整
                h = printer->pageRect().height();

    QPainter painter;
    painter.begin(printer);

    drawGrid(painter, w, h, dDotsPerMMForPrinter);
    drawWave(painter, w, h, dDotsPerMMForPrinter, dScale);

    painter.save();
    QPen pen(Qt::blue);
    QFont f("Consolas");
    f.setBold(true);
    painter.setPen(pen);
    painter.setFont(f);
    QString text = QString("Lead:%1 Gain:%2 Speed:%3").arg(m_leadNums).arg(m_fGain).arg(m_iSpeed);
    painter.drawText(10 * dScale, 20 * dScale, text);
    painter.restore();

    painter.end();
}

//自建队列，自动添加数据到容器尾部，同时去除队列前部分数据
//暂时仅仅用于数据库分析显示，因为实时分析的显示逻辑不一样！！！
void CommonWave::addWaveShowData(int newData)
{
    // 添加新的 ECG 数据到容器尾部
    WaveData_intVector.append(newData);

    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    while (WaveData_intVector.size() > DisplayWaveformLength) {
        WaveData_intVector.removeFirst();
    }

    // 发送信号通知数据更新（如果需要的话）
    //emit ecgDataUpdated();
}


//自建队列，自动修改指针指向位置的数据为当前串口接收的数据
//用于实时数据显示，不用于数据分析
void CommonWave::updateWaveData(int newData)
{
    Wave_Current_Location += 1;
    PositionforCalibration = (Wave_Current_Location % DisplayWaveformLength);
//    qDebug() << "the position is"<< PositionforCalibration;
    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    if (WaveData_intVector.size() >= DisplayWaveformLength) {
        // 添加新的 ECG 数据到容器指定位置
        WaveData_intVector[PositionforCalibration] = newData;
    }
    else {
        // 如果数据还未填满，先将数据填满
        WaveData_intVector.append(newData);
    }

    // 发送信号通知数据更新（如果需要的话）
    //emit ecgDataUpdated();
    update();
}

//自建队列，自动修改指针指向位置的数据为当前串口接收的数据
//用于实时数据显示，不用于数据分析
void CommonWave::updateWaveData_float(float newData)
{
    Wave_Current_Location += 1;
    PositionforCalibration = (Wave_Current_Location % DisplayWaveformLength);
//    qDebug() << "the position is"<< PositionforCalibration;
    // 如果需要限制容器大小，可以在此添加逻辑
    // 例如，保持容器大小不超过某个值
    if (WaveData_floatVector.size() >= DisplayWaveformLength) {
        // 添加新的 ECG 数据到容器指定位置
        WaveData_floatVector[PositionforCalibration] = newData;
    }
    else {
        // 如果数据还未填满，先将数据填满
        WaveData_floatVector.append(newData);
    }

    // 发送信号通知数据更新（如果需要的话）
    //emit ecgDataUpdated();
    update();
}


//存入数据到txt文件中        存一个文件
void CommonWave::saveVectorToFile_float()
{
    // 获取当前系统时间
    QDateTime currentTime = QDateTime::currentDateTime();

    // 将时间转换为字符串格式作为文件名
    QString filename = currentTime.toString("yyyyMMdd_hhmmss") + ".txt";

    // 创建文件对象
    QFile file(filename);

    // 打开文件，如果文件不存在则创建它，如果文件已存在则将其覆盖
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return;
    }

    // 创建文本流对象
    QTextStream out(&file);

    // 将数据写入文件
    /*for (int i = 0; i < data.size(); ++i) {
        out << data.at(i) << "\n"; // 将每个整数写入文件并换行
    }*/
    for (int i = 0; i < WaveData_floatVector.size(); ++i) {
        out << WaveData_floatVector.at(i) << "\n"; // 将每个整数写入文件并换行
    }

    // 关闭文件
    file.close();
}


void CommonWave::SetdrawColor(int Color)
{
    DrawPenColor = Color;
}


// 根据当前窗口宽度更新波形长度
void CommonWave::updateDisplayWaveformLength(int w)
{
    DisplayWaveformLength =  w / TimeZoomRatio; // 假设此处/3，会导致波形仅仅只占用整个屏幕宽度的1/3
//    qDebug() << "this windows width: " << this->width() << "WaveformLength:" << DisplayWaveformLength;
}

uint32_t CommonWave::returnDisplayWaveformLength(void)
{
    return DisplayWaveformLength;
}






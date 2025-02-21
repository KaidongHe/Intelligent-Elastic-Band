#ifndef RESP_FILTER_H
#define RESP_FILTER_H

#include <iostream>
#include <cmath>
#include <vector>

#define PI_LowPass 3.14159265358979323846

// 定义一个数字低通滤波器类
class LowPassFilter {
public:
    // 构造函数，传入截止频率和采样频率
    LowPassFilter(double fc, double fs) : fc_(fc), fs_(fs) {
        // 计算滤波器系数
        double wc = 2 * PI_LowPass * fc_;
        double T = 1.0 / fs_;
        alpha_ = T / (T + 1.0 / wc);
        yPrev_ = 0.0;
    }

    // 滤波函数，输入一个样本，输出滤波后的样本
    double filter(double x) {
        // 应用低通滤波器
        double y = alpha_ * x + (1.0 - alpha_) * yPrev_;
        yPrev_ = y;
        return y;
    }

private:
    double fc_;     // 截止频率
    double fs_;     // 采样频率
    double alpha_;  // 滤波器系数
    double yPrev_;  // 上一个输出样本
};

#endif

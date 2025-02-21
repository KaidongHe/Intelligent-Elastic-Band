#ifndef SIMPLECIRCULARBUFFER_H
#define SIMPLECIRCULARBUFFER_H

//该函数只能在主函数中使用，不能在类的头文件中使用！！！！

#include <vector>
#include <stdexcept>

template <typename T>
class SimpleCircularBuffer {
private:
    std::vector<T> buffer;  // 用于存储数据
    size_t capacity;        // 缓冲区的最大容量
    size_t head;            // 写入位置
    size_t tail;            // 读取位置
    bool full;              // 缓冲区是否已满

public:
    // 构造函数，初始化缓冲区大小
    explicit SimpleCircularBuffer(size_t size);

    // 写入数据
    void write(const T& item);

    // 读取数据
    T read();

    // 检查缓冲区是否为空
    bool isEmpty() const;

    // 检查缓冲区是否已满
    bool isFull() const;

    // 获取当前缓冲区大小
    size_t size() const;

    // 获取缓冲区的最大容量
    size_t getCapacity() const;

    // 初始化缓冲区，填充默认值（如 0）
    void initialize(const T& value);
};

#include "SimpleCircularBuffer.cpp"  // 模板实现包含在头文件中

#endif // SIMPLECIRCULARBUFFER_H

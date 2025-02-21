#include "SimpleCircularBuffer.h"

// 构造函数
template <typename T>
SimpleCircularBuffer<T>::SimpleCircularBuffer(size_t size)
    : buffer(size), capacity(size), head(0), tail(0), full(false) {
    if (size == 0) {
        throw std::invalid_argument("Buffer size must be greater than 0");
    }
}

// 写入数据
template <typename T>
void SimpleCircularBuffer<T>::write(const T& item) {
    buffer[head] = item;  // 写入数据到当前位置
    head = (head + 1) % capacity;  // 移动写入指针

    if (full) {
        tail = (tail + 1) % capacity;  // 如果缓冲区已满，则覆盖最旧数据
    }

    full = head == tail;  // 检查缓冲区是否已满
}

// 读取数据
template <typename T>
T SimpleCircularBuffer<T>::read() {
    if (isEmpty()) {
        throw std::out_of_range("Buffer is empty");
    }

    T item = buffer[tail];  // 读取当前位置的数据
    tail = (tail + 1) % capacity;  // 移动读取指针
    full = false;  // 缓冲区读取后不再满
    return item;
}

// 检查缓冲区是否为空
template <typename T>
bool SimpleCircularBuffer<T>::isEmpty() const {
    return (!full && (head == tail));
}

// 检查缓冲区是否已满
template <typename T>
bool SimpleCircularBuffer<T>::isFull() const {
    return full;
}

// 获取当前缓冲区大小
template <typename T>
size_t SimpleCircularBuffer<T>::size() const {
    if (full) {
        return capacity;
    }

    if (head >= tail) {
        return head - tail;
    }

    return capacity - (tail - head);
}

// 获取缓冲区的最大容量
template <typename T>
size_t SimpleCircularBuffer<T>::getCapacity() const {
    return capacity;
}

// 初始化缓冲区，填充默认值
template <typename T>
void SimpleCircularBuffer<T>::initialize(const T& value) {
    std::fill(buffer.begin(), buffer.end(), value);  // 使用指定值填充缓冲区
    head = 0;                                       // 重置写入指针
    tail = 0;                                       // 重置读取指针
    full = false;                                   // 缓冲区状态重置为非满
}

// 显式实例化（只在需要时使用）
// template class SimpleCircularBuffer<int>;
// template class SimpleCircularBuffer<float>;

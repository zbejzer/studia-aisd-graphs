#pragma once

#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>

using std::cout;

// Dynamic array based implementation of queue
// T defines the type of data stored
// Warning: Insecure for types that are not Plain Old Data
template <typename T> class Queue
{
  private:
    T *data;
    unsigned long long int real_size, used_size;
    unsigned long long int rear_i, front_i;

    void adjustSize();

  public:
    Queue();
    ~Queue();

    void push(const T &val);
    void pop();
    const T &back() const;
    T &back();
    const T &front() const;
    T &front();
    bool empty() const;
    unsigned long long int size() const;
    void print() const;
};

template <typename T> void Queue<T>::adjustSize()
{
    if (real_size > used_size * 3 && real_size > 1)
    {
        memcpy(data, data + front_i, sizeof(T) * real_size);
        real_size = real_size >> 1;
        #pragma warning(suppress : 6308)
        data = static_cast<T *>(realloc(data, sizeof(T) * real_size));
        front_i = 0;
        rear_i = used_size - 1;
    }
    else if (rear_i + 1 > real_size)
    {
        real_size = real_size << 1;
        #pragma warning(suppress : 6308)
        data = static_cast<T *>(realloc(data, sizeof(T) * real_size));
    }
}

template <typename T> Queue<T>::Queue() : real_size(2), used_size(0), front_i(0), rear_i(ULLONG_MAX)
{
    data = static_cast<T *>(malloc(sizeof(T) * real_size));
}

template <typename T> Queue<T>::~Queue()
{
    free(data);
}

template <typename T> void Queue<T>::push(const T &val)
{
    ++used_size;
    ++rear_i;
    adjustSize();

    data[rear_i] = val;
}

template <typename T> void Queue<T>::pop()
{
    ++front_i;
    --used_size;
    adjustSize();
}

template <typename T> const T &Queue<T>::back() const
{
    return data[rear_i];
}

template <typename T> T &Queue<T>::back()
{
    return data[rear_i];
}

template <typename T> const T &Queue<T>::front() const
{
    return data[front_i];
}

template <typename T> T &Queue<T>::front()
{
    return data[front_i];
}

template <typename T> inline bool Queue<T>::empty() const
{
    return used_size == 0;
}

template <typename T> inline unsigned long long int Queue<T>::size() const
{
    return used_size;
}

template <typename T> void Queue<T>::print() const
{
    for (unsigned long long int i = front_i; i <= rear_i; i++)
    {
        cout << data[i] << " ";
    }
    cout << "\n";

    return;
}
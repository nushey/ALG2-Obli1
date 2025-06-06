#pragma once

template <class T>
class Vector
{
private:
    T *data;
    size_t capacity;
    size_t count;

    void resize(size_t newCapacity)
    {
        T *newData = new T[newCapacity];
        for (size_t i = 0; i < count; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), capacity(0), count(0) {}
    void push(const T &value)
    {
        if (count == capacity)
        {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[count++] = value;
    }

    void pop()
    {
        if (count == 0)
        {
            throw std::underflow_error("Vector is empty");
        }
        count--;
    }

    T &operator[](size_t index)
    {
        if (index >= count)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const
    {
        return count;
    }

    void clear()
    {
        delete[] data;
        data = nullptr;
        capacity = 0;
        count = 0;
    }
};
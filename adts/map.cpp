#pragma once
template <class K, class V>

class Map{
    virtual V get(K key) = 0;
    virtual void set(K key, V value) = 0;
    virtual int size() = 0;
    virtual void remove(K key) = 0;
    virtual int capacity() = 0;
    virtual bool exists(K key) = 0;
};
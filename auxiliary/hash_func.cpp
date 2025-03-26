#pragma once

template <class T>
class HashFunc{
    virtual int hash (T data) = 0;
};
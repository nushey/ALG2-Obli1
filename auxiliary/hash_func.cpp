#pragma once

template <class T>
class HashFunc{
    public:
        virtual int hash (T data) = 0;
};
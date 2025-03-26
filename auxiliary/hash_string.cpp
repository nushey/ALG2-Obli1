#pragma once
#include "./hash_func.cpp"
#include <string>
using namespace std;

class HashString : public HashFunc<string>{
    public:
        virtual int hash(string key) override {
            const int p = 31; 
            long long p_pow = 1;
            long long res = 0;
            for (char c : key) {
                res = res + (c * p_pow);
                p_pow = (p_pow * p);
            }
            return res;
        }
};
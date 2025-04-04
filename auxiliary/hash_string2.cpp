#pragma once
#include "./hash_func.cpp"
#include <string>
using namespace std;

class HashString2 : public HashFunc<string>{
    public:
        // DJB2 hash
        virtual int hash(string key) override {
            unsigned long hash = 5381;
            for (char c : key) {
                hash = ((hash << 5) + hash) + c; 
            }
            return hash;
        }
        
};
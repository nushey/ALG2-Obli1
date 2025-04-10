#pragma once
#include "./map.cpp"
#include "./pair.cpp"
#include "./linked_list.cpp"
#include "../auxiliary/hash_string.cpp"
#include <assert.h>


template <class K, class V>
class ClosedMap : public Map<K,V>{
    private:
        struct Entry{
            Pair<K,V> values;
            bool isDeleted;
            bool isAvailable;
        };

        Entry* arr;
        int length;
        int count = 0;
        HashFunc<K> *h1;
        HashFunc<K> *h2;

        int ABS(int x){
            if(x <  0) return -x;
            return x;
        };

        bool isPrime(int n) {
            if (n <= 1) return false;
            if (n == 2) return true;
            if (n % 2 == 0) return false;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) return false;
            }
            return true;
        }
        
        int nextPrime(int n) {
            while (!isPrime(n)) {
                n++;
            }
            return n;
        }

        void rehash() {
            int oldLength = this->length;
            Entry* oldArr = this->arr;
        
            this->length = nextPrime(this->length * 2);
            this->arr = new Entry[this->length];
            this->count = 0; 
        
            for (int i = 0; i < this->length; i++) {
                this->arr[i].isAvailable = true;
                this->arr[i].isDeleted = false;
            }
        
            for (int i = 0; i < oldLength; i++) {
                if (!oldArr[i].isAvailable && !oldArr[i].isDeleted) {
                    this->set(oldArr[i].values.fst, oldArr[i].values.snd);
                }
            }
        
            delete[] oldArr;
        }
        
        

    public:
        ClosedMap(HashFunc<K> *h1, HashFunc<K> *h2, int expectedSize){
            this->length = nextPrime(expectedSize*3/2);
            this->arr = new Entry[this->length];
            for(int i = 0; i < this->length; i++){
                this->arr[i].isDeleted = false;
                this->arr[i].isAvailable = true;
            }
            this->h1 = h1;
            this->h2 = h2;
        }

        virtual V get(K key) override {
            int hash1 = ABS(this->h1->hash(key)) % this->length;
            int hash2 = ABS(this->h2->hash(key)) % this->length;
            if (hash2 == 0) hash2 = 1;

        
            for (int i = 0; i < this->length; i++) {
                int pos = (hash1 + i*hash2) % this->length;
        
                if (arr[pos].isAvailable && !arr[pos].isDeleted) break;

        
                if (!arr[pos].isAvailable && !arr[pos].isDeleted && arr[pos].values.fst == key) {
                    return arr[pos].values.snd;
                }
        
            }
        
            return V();
        }

        virtual void set(K key, V val) override{
            this->remove(key);
            int hash1 = ABS(this->h1->hash(key)) % this->length;
            int hash2 = ABS(this->h2->hash(key)) % this->length;
            if (hash2 == 0) hash2 = 1;

            for (int i = 0; i < this->length; i++) {
                int pos = (hash1 + i*hash2) % this->length;
        
                if (!arr[pos].isAvailable && !arr[pos].isDeleted) continue;
        
                if (arr[pos].isAvailable || (!arr[pos].isAvailable && arr[pos].isDeleted)) {
                    Pair<K,V> pair(key, val);
                    this->arr[pos].values = pair;
                    this->arr[pos].isAvailable = false;
                    this->arr[pos].isDeleted = false;
                    this->count++;
                    return;
                }
        
            }

        }
        virtual int size() override {
            return this->count;
        }

        virtual bool exists(K key) override {
            int hash1 = ABS(this->h1->hash(key)) % this->length;
            int hash2 = ABS(this->h2->hash(key)) % this->length;
            if (hash2 == 0) hash2 = 1;

        
            for (int i = 0; i < this->length; i++) {
                int pos = (hash1 + i*hash2) % this->length;
    
                if (arr[pos].isAvailable && !arr[pos].isDeleted) return false;
        
                if (!arr[pos].isAvailable && !arr[pos].isDeleted && arr[pos].values.fst == key) {
                    return true;
                }
            }
            return false;
        }

        virtual void remove(K key) override {
            int hash1 = ABS(this->h1->hash(key)) % this->length;
            int hash2 = ABS(this->h2->hash(key)) % this->length;
            if (hash2 == 0) hash2 = 1;

            for(int i = 0; i < this->length; i++){
                int pos = (hash1 + i*hash2) % this->length;
                
                if (arr[pos].isAvailable && !arr[pos].isDeleted) return;
                if (!arr[pos].isAvailable && !arr[pos].isDeleted && arr[pos].values.fst == key) {
                    arr[pos].isDeleted = true;
                    this->count--;
                    return;
                }
            }
        }

        virtual int capacity() override{
            return this->length;
        }
        

};
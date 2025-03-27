#pragma once
#include "./map.cpp"
#include "./pair.cpp"
#include "./linked_list.cpp"
#include "../auxiliary/hash_string.cpp"
#include <assert.h>




template <class K, class V>
class OpenMap : public Map<K,V>
{
    private:
        LinkedList<Pair<K,V>>** arr;
        int length;
        int count = 0;
        HashFunc<K> *h;



        int ABS(int x){
            if(x <  0) return -x;
            return x;
        };


    public:
        OpenMap(HashFunc<K> *h, int expectedSize){
            // charge factor 1.5
            this->length = expectedSize * 2 / 3;
            this->arr = new LinkedList<Pair<K,V>> *[this->length];
            for (int i = 0; i < this->length; i++) {
                this->arr[i] = nullptr; 
            }
            this->h = h;
        }
        virtual V get(K key) override{
            int pos = abs(this->h->hash(key) % this->length);
            LinkedList<Pair<K,V>> *it = this->arr[pos];
            for(int i = 0; i < it->size(); i++){
                Pair<K,V> pair = it->get(i);
                if(pair.fst == key) return pair.snd;
            }
            return V();
        }
        virtual void set(K key, V val) override{
            this->remove(key);
            int pos = abs(this->h->hash(key) % this->length);
            if(!this->arr[pos]){
                this->arr[pos] = new LinkedList<Pair<K,V>>();
            }
            this->arr[pos]->add(Pair<K,V>(key, val));
            this->count++;
        }
        virtual int size() override {
            return this->count;
        }
        virtual bool exists(K key) override {
            int pos = abs(this->h->hash(key) % this->length);
            if(this->arr[pos] == nullptr) return false;
            LinkedList<Pair<K,V>> *it = this->arr[pos];
            if(it == nullptr) return false;
            for(int i = 0; i < it->size(); i++){
                Pair<K,V> pair = it->get(i);
                if(pair.fst == key) return true;
            }
            return false;
        }
        virtual void remove(K key) override{
            int pos = abs(this->h->hash(key) % this->length);
            if(this->arr[pos] == nullptr) return;
            int preSize = this->arr[pos]->size();
            this->arr[pos]->remove(Pair<K,V>(key,key));
            if (preSize != this->arr[pos]->size())
            {
                this->count--;
            }

        }
        virtual int capacity() override{
            return this->length;
        }

};


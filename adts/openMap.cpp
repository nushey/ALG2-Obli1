#pragma once
#include "./map.cpp"
#include "./linked_list.cpp"
#include "../auxiliary/hash_string.cpp"



int ABS(int x){
    if(x <  0) return -x;
    return x;
};


template <class K, class V>
class OpenMap : public Map<K,V>
{
    private:
        List<Pair<K,V>>** arr;
        int size;
        int count = 0;
        HashFunc<K> *h;


    public:

        OpenHashMap(HashFunc<K> *h, int expectedSize){
            // charge factor 1.5
            this->size = expectedSize * 2 / 3;
            this->arr = new List<Pair<K,V>> *[this->size];
            this->h = h;
        }

        virtual V get(K key) override{
            // TODO
        }
        virtual V set(K key, V val) override{
            this->remove(key);
            int pos = abs(this->h->hash(key) % this->size);
            if(!this->arr[pos]){
                this->arr[pos] = new LinkedList<Pair<K,V>>();
            }
            this->arr[pos]->add(Pair<K,V>(key, val));
        }

        virtual int size() override {
            return this->count;
        }

        virtual bool exists() override {

        }

        virtual void remove(K key) override{

        }

        virtual int capacity() override{
            return this->size;
        }

};


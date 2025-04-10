#pragma once
#include "./priorityQueue.cpp"
#include "./pair.cpp"
#include <assert.h>

template <class E, class P>
class MinHeap : public PriorityQueue<E,P>{

    private:
        Pair<E,P> *arr;
        int arrSize;
        int count = 0;

        void swap(int x, int y){
            Pair<E,P> temp = this->arr[x];
            this->arr[x] = this->arr[y];
            this->arr[y] = temp;
        }

        void siftUp(int pos){
            if(pos <= 1) return;
            int father = pos/2;
            if(this->arr[father].snd > this->arr[pos].snd){
                swap(pos, father);
                siftUp(father);
            }
        }

        void siftDown(int pos){
            if(pos > this->count) return;
            int leftChild = pos * 2;
            int rightChild = pos * 2 + 1;
            int swapPos = pos;

            if(leftChild <= this->count && this->arr[leftChild].snd < this->arr[swapPos].snd){
                swapPos = leftChild;
            }
            if(rightChild <= this->count && this->arr[rightChild].snd < this->arr[swapPos].snd){
                swapPos = rightChild;
            }
            if(swapPos != pos){
                swap(swapPos, pos);
                siftDown(swapPos);
            }
        }


    public:
        MinHeap(int expectedSize){
            arr = new Pair<E,P>[expectedSize+1];
            arrSize = expectedSize+1;
        }

        virtual E dequeue() {
            assert(this->count > 0); 
            Pair<E,P> res = this->arr[1]; 
            swap(1, this->count); 
            this->count--; 
            siftDown(1); 
            return res.fst; 
        };
        virtual E top() {
            assert(this->count > 0);
            return this->arr[1].fst;
        };
        virtual void enqueue(E item, P priority) {
            this->count++;
            if(this->count >= this->arrSize){
                Pair<E,P> *newArr = new Pair<E,P>[this->arrSize * 2];
                for(int i = 1; i < this->arrSize; i++){
                    newArr[i] = arr[i];
                }
                this->arrSize *= 2;
                delete[] this->arr;
                this->arr = newArr;
            }
            this->arr[count] = Pair<E,P>(item, priority);
            siftUp(count);


        };
        virtual bool isEmpty() {
            return this->count == 0;
        };
        virtual int size() {
            return this->count;
        };
};
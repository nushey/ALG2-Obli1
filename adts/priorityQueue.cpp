#pragma once
template<class E, class P>
class PriorityQueue{
    public:
        virtual E dequeue() = 0;
        virtual E top() = 0;
        virtual void enqueue(E item, P priority) = 0;
        virtual bool isEmpty() = 0;
        virtual int size() = 0;
};
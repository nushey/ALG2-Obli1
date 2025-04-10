#pragma once

#include "./list.cpp"

template<class T>

class LinkedList: public List<T>{
    private:
        struct Node{
            T data;
            Node* next;
        };
        Node *head;
        int length;

        class LinkedListIterator : public Iterator<T>{
            Node* curr;

            public:
                LinkedListIterator(Node* start){
                    this->curr = start;
                }
                virtual bool hasNext() override{
                    return this->curr != nullptr;
                }
                virtual T next() override {
                    assert(hasNext());
                    T ret = this->curr->data;
                    this->curr= this->curr->next;
                    return ret;
                }
        };
        

    public:

        LinkedList(){
            this->head = nullptr;
            this->length = 0;
        };

        virtual Iterator<T>* iterator() override{
            return new LinkedListIterator(this->head);
        };

        virtual void add(T data) override{
            if(isEmpty()){
                head = new Node;
                head->data = data;
                head->next = nullptr;
                length++;
                return;
            }
            Node * ins = new Node;
            ins->data = data;
            ins->next = head;
            head = ins;
            
            length++;

        };

        virtual T get(int pos) override{
            assert(pos < this->length);
            Node * curr = head;
            while(pos > 0){
                curr = curr->next;
                pos--;
            }
            return curr->data;
        };
        virtual bool contains(T data) override{
            Node * curr = this->head;
            while(curr != nullptr){
                if(curr->data == data){
                    return true;
                }
                curr = curr->next;
            }
            return false;
        };
        virtual bool isEmpty() override{
            return this->length == 0;
        };
        virtual int size() override{
            return this->length;
        };

        void nRemove(Node*& head, T data){
            if(!head) return;
            if(data == head->data){
                Node* tmp = head;
                head = head->next;
                this->length--;
                delete tmp;
                return;
            }
            nRemove(head->next, data);
        }

        virtual void remove(T data) override {
            nRemove(this->head, data);
        }
};
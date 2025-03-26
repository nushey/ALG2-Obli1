#pragma once

#include "./list.cpp"

template<class T>

class LinkedList: public List<T>{
    private:
        struct Node{
            T data;
            Node* next;
        };
        Node *head = nullptr;
        int length = 0;

    // LinkedList(){
        
    // }

    public:
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
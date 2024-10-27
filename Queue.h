#pragma once
#include "DLL.h"  

class Queue
{
public:
    Queue();
    ~Queue();

    void enqueue(double value);  
    bool dequeue(double& value); 
    bool isEmpty() const;        
    size_t size() const;         
    void print() const;          

private:
    DoublyLinkedList _list;  
};

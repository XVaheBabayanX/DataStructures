#pragma once
#include "SLL.h"
#include <iostream>

class Stack
{
public:
    Stack();
    ~Stack();
    void Push(const double value);
    bool Pop(double& value);
    bool Top(double& value);
    bool isEmpty() const;
    size_t size() const;

private:
    List _list;
};




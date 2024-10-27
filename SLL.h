#pragma once

#include <iostream>

using namespace std;

class ListNode
{
public:
    ListNode(const double data, ListNode* next = nullptr) : _data(data), _nextPtr(next) {}
    double _data = 0;
    ListNode* _nextPtr = nullptr;
};

class List
{
public:
    List() : _firstPtr(nullptr), _lastPtr(nullptr), _count(0) {}
    ~List()
    {
        double value;
        while (removeFromFront(value))
            ;
    }
    void insertAtFront(const double);
    void insertAtBack(const double);
    bool insertAtIndex(const size_t, const double);
    bool removeFromFront(double&);
    bool removeFromBack(double&);
    bool removeAtIndex(const size_t, double&);
    bool isEmpty() const { return _firstPtr == nullptr; }
    bool hasCycleSLL();
    void print() const;
    double getFirstValue() const;
    size_t getElementCount() const;

private:
    ListNode* createNode(const double data) const { return new ListNode(data); }

private:
    ListNode* _firstPtr;
    ListNode* _lastPtr;
    size_t _count;
};

#pragma once

#include <iostream>

using namespace std;

class ListNode
{
public:
    ListNode(const double data, ListNode* prev = nullptr, ListNode* next = nullptr)
        : _data(data), _prevPtr(prev), _nextPtr(next) {}

    double _data;
    ListNode* _prevPtr;
    ListNode* _nextPtr;
};

class DoublyLinkedList
{
public:
    DoublyLinkedList() : _firstPtr(nullptr), _lastPtr(nullptr), _count(0) {}
    ~DoublyLinkedList();

    void insertAtFront(const double value);
    void insertAtBack(const double value);
    bool insertAtIndex(const size_t index, const double value);

    bool removeFromFront(double& value);
    bool removeFromBack(double& value);
    bool removeAtIndex(const size_t index, double& value);

    bool isEmpty() const { return _firstPtr == nullptr; }
    bool hasCycleDLL();
    void print() const;
    size_t getElementCount() const { return _count; }

private:
    ListNode* createNode(const double data, ListNode* prev = nullptr, ListNode* next = nullptr) const
    {
        return new ListNode(data, prev, next);
    }

private:
    ListNode* _firstPtr;
    ListNode* _lastPtr;
    size_t _count;
};


#pragma once

#include <iostream>
#include <string>

using namespace std;

class ListNode
{
public:
    ListNode(size_t vertex, int weight, ListNode* prev = nullptr, ListNode* next = nullptr)
        : _vertex(vertex), _weight(weight), _prevPtr(prev), _nextPtr(next) {}
    size_t _vertex;
    int _weight;
    ListNode* _prevPtr;
    ListNode* _nextPtr;  
};

class DoublyLinkedList
{
public:
    DoublyLinkedList() : _firstPtr(nullptr), _lastPtr(nullptr), _count(0) {}
    ~DoublyLinkedList();

    void insertAtFront(const size_t vertex, const int weight);
    void insertAtBack(const size_t vertex, const int weight);
    bool insertAtIndex(const size_t index, const size_t vertex, const int weight);

    bool removeFromFront(size_t& vertex);
    bool removeFromBack(size_t& vertex);
    bool removeAtIndex(const size_t index, size_t& vertex);

    bool isEmpty() const { return _firstPtr == nullptr; }
    bool hasCycleDLL();
    void print() const;
    size_t getElementCount() const { return _count; }
    ListNode* getFirstPtr() const { return _firstPtr; }

private:
    ListNode* createNode(const size_t vertex, const int weight, ListNode* prev = nullptr, ListNode* next = nullptr) const
    {
        return new ListNode(vertex, weight, prev, next);
    }

private:
    ListNode* _firstPtr;
    ListNode* _lastPtr;
    size_t _count;
};


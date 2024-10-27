#pragma once

#include <iostream>

using namespace std;

class ListNode
{
public:
    ListNode(const std::string name ,const double data, ListNode* next = nullptr) : _key(name), _data(data), _nextPtr(next) {}
    std::string _key = "default";
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
        while (removeFromFront(value));      
    }
    ListNode* getFirstPtr() const {
        return _firstPtr;
    }
    void insertAtFront(const std::string name, const double value);
    void insertAtBack(const std::string name, const double value);
    bool insertAtIndex(const std::string name, const size_t index, const double value);
    bool removeFromFront(double&);
    bool removeFromBack(double&);
    bool removeAtIndex(const size_t, double&);
    bool isEmpty() const { return _firstPtr == nullptr; }
    bool hasCycleSLL();
    void print() const;
    double getFirstValue() const;
    size_t getElementCount() const;

private:
    ListNode* createNode(const std::string& name, const double data) const { return new ListNode(name, data); }

private:
    ListNode* _firstPtr;
    ListNode* _lastPtr;
    size_t _count;
};

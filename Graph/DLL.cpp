#include "DLL.h"

DoublyLinkedList::~DoublyLinkedList()
{
    size_t vertex;
    while (removeFromFront(vertex))
        ;
}

void DoublyLinkedList::insertAtFront(const size_t vertex, const int weight)
{
    ListNode* newNode = createNode(vertex, weight, nullptr, _firstPtr);

    if (isEmpty())
        _firstPtr = _lastPtr = newNode;
    else
    {
        _firstPtr->_prevPtr = newNode;
        _firstPtr = newNode;
    }
    _count++;
}

void DoublyLinkedList::insertAtBack(const size_t vertex, const int weight)
{
    ListNode* newNode = createNode(vertex, weight, _lastPtr, nullptr);

    if (isEmpty())
        _firstPtr = _lastPtr = newNode;
    else
    {
        _lastPtr->_nextPtr = newNode;
        _lastPtr = newNode;
    }
    _count++;
}

bool DoublyLinkedList::insertAtIndex(const size_t index, const size_t vertex, const int weight)
{
    if (index < 0 || index > _count)
        return false;

    if (index == 0)
    {
        insertAtFront(vertex, weight);
        return true;
    }

    if (index == _count)
    {
        insertAtBack(vertex, weight);
        return true;
    }

    ListNode* currentPtr = _firstPtr;
    for (size_t i = 0; i < index; ++i)
    {
        currentPtr = currentPtr->_nextPtr;
    }

    ListNode* newNode = createNode(vertex, weight, currentPtr->_prevPtr, currentPtr);
    currentPtr->_prevPtr->_nextPtr = newNode;
    currentPtr->_prevPtr = newNode;

    _count++;
    return true;
}

bool DoublyLinkedList::removeFromFront(size_t& vertex)
{
    if (isEmpty())
        return false;

    ListNode* tempPtr = _firstPtr;
    vertex = tempPtr->_vertex;

    if (_firstPtr == _lastPtr)
        _firstPtr = _lastPtr = nullptr;
    else
    {
        _firstPtr = _firstPtr->_nextPtr;
        _firstPtr->_prevPtr = nullptr;
    }

    delete tempPtr;
    _count--;
    return true;
}

bool DoublyLinkedList::removeFromBack(size_t& vertex)
{
    if (isEmpty())
        return false;

    ListNode* tempPtr = _lastPtr;
    vertex = tempPtr->_vertex;

    if (_firstPtr == _lastPtr)
        _firstPtr = _lastPtr = nullptr;
    else
    {
        _lastPtr = _lastPtr->_prevPtr;
        _lastPtr->_nextPtr = nullptr;
    }

    delete tempPtr;
    _count--;
    return true;
}

bool DoublyLinkedList::removeAtIndex(const size_t index, size_t& vertex)
{
    if (index < 0 || index >= _count || isEmpty())
        return false;

    if (index == 0)
        return removeFromFront(vertex);

    if (index == _count - 1)
        return removeFromBack(vertex);

    ListNode* currentPtr = _firstPtr;
    for (size_t i = 0; i < index; ++i)
    {
        currentPtr = currentPtr->_nextPtr;
    }

    vertex = currentPtr->_vertex;
    currentPtr->_prevPtr->_nextPtr = currentPtr->_nextPtr;
    currentPtr->_nextPtr->_prevPtr = currentPtr->_prevPtr;

    delete currentPtr;
    _count--;
    return true;
}

bool DoublyLinkedList::hasCycleDLL()
{
    if (_firstPtr == nullptr)
        return false;

    ListNode* slowPtr = _firstPtr;
    ListNode* fastPtr = _firstPtr;

    while (fastPtr != nullptr && fastPtr->_nextPtr != nullptr)
    {
        slowPtr = slowPtr->_nextPtr;
        fastPtr = fastPtr->_nextPtr->_nextPtr;
        if (slowPtr == fastPtr)
            return true;
    }

    return false;
}

void DoublyLinkedList::print() const
{
    if (isEmpty())
    {
        cout << "List is empty." << endl;
        return;
    }

    cout << "List content: ";
    ListNode* currentPtr = _firstPtr;
    while (currentPtr != nullptr)
    {
        cout << currentPtr->_vertex << " ";
        currentPtr = currentPtr->_nextPtr;
    }
    cout << endl;
}

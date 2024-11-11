#include "DLL.h"

DoublyLinkedList::~DoublyLinkedList()
{
    size_t vertex;
    while (removeFromFront(vertex));
}

void DoublyLinkedList::clear() {
    ListNode* current = _firstPtr;

    while (current != nullptr) {
        ListNode* temp = current;
        current = current->_nextPtr;
        delete temp;  
    }

    _firstPtr = nullptr;
    _lastPtr = nullptr;
    _count = 0;  
}

void DoublyLinkedList::insertAtFront(const size_t vertex, const double weight)
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

void DoublyLinkedList::insertAtBack(const size_t vertex, const double weight)
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

bool DoublyLinkedList::insertAtIndex(const size_t index, const size_t vertex, const double weight)
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

bool DoublyLinkedList::removeElement(const size_t vertex) {
    ListNode* current = _firstPtr;

    while (current != nullptr) {
        if (current->_vertex == vertex) {
            if (current->_prevPtr != nullptr) {
                current->_prevPtr->_nextPtr = current->_nextPtr;
            }
            else {
                _firstPtr = current->_nextPtr; 
            }

            if (current->_nextPtr != nullptr) {
                current->_nextPtr->_prevPtr = current->_prevPtr;
            }
            else {
                _lastPtr = current->_prevPtr;  
            }

            delete current;
            _count--;  
            return true;  
        }
        current = current->_nextPtr;
    }
    return false;  
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

double DoublyLinkedList::getWeightAtIndex(const size_t index) const
{
    if (index >= _count)
        throw out_of_range("Index out of range");

    ListNode* current = _firstPtr;
    for (size_t i = 0; i < index; ++i)
    {
        current = current->_nextPtr;
    }

    return current->_weight;
}

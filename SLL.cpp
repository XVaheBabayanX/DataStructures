#include "SLL.h"

using namespace std;

void List::insertAtFront(const double value)
{
    ListNode* newNode = createNode(value);
    if (isEmpty())
        _firstPtr = _lastPtr = newNode;

    else
    {
        newNode->_nextPtr = _firstPtr;
        _firstPtr = newNode;
    }
    _count++;
}

void List::insertAtBack(const double value)
{
    ListNode* newNode = createNode(value);
    if (isEmpty())
        _firstPtr = _lastPtr = newNode;
    else
    {
        _lastPtr->_nextPtr = newNode;
        _lastPtr = newNode;
    }
    _count++;
}

bool List::insertAtIndex(const size_t index, const double value)
{

    if (index < 0 || index > _count)
        return false;

    if (isEmpty() || index == 0)
    {
        insertAtFront(value);
        return true;
    }

    else if (index == _count)
    {
        insertAtBack(value);
        return true;
    }
    else
    {
        ListNode* currentPtr = _firstPtr;
        for (size_t i = 0; i < index - 1; ++i)
        {
            currentPtr = currentPtr->_nextPtr;
        }
        ListNode* newNode = createNode(value);
        newNode->_nextPtr = currentPtr->_nextPtr;
        currentPtr->_nextPtr = newNode;
        _count++;
        return true;
    }
}

bool List::removeFromFront(double& value)
{
    if (isEmpty())
        return false;

    ListNode* tempPtr = _firstPtr;
    value = _firstPtr->_data;

    if (_firstPtr == _lastPtr)
        _firstPtr = _lastPtr = nullptr;
    else
        _firstPtr = _firstPtr->_nextPtr;

    delete tempPtr;
    _count--;
    return true;
}

bool List::removeFromBack(double& value)
{
    if (isEmpty())
        return false;

    value = _lastPtr->_data;
    ListNode* tempPtr = _firstPtr;

    if (_firstPtr == _lastPtr)
        _firstPtr = _lastPtr = nullptr;
    else
    {
        while (tempPtr->_nextPtr != _lastPtr)
            tempPtr = tempPtr->_nextPtr;

        tempPtr->_nextPtr = nullptr;
        delete _lastPtr;
        _lastPtr = tempPtr;
    }
    _count--;
    return true;
}

bool List::removeAtIndex(const size_t index, double& value)
{
    if (index < 0)
    {
        cout << "Invalid index. Index should be greater or equal to 0." << endl;
        return false;
    }

    if (isEmpty())
    {
        cout << "List is empty. Element not removed." << endl;
        return false;
    }

    if (index == 0)
    {
        return removeFromFront(value);
        _count--;
        return true;

    }

    if (index == _count - 1)
    {
        removeFromBack(value);
        _count--;
        return true;
    }

    ListNode* currentPtr = _firstPtr;
    ListNode* previousPtr = nullptr;
    size_t currentIndex = 0;

    while (currentPtr != nullptr && currentIndex < index)
    {
        previousPtr = currentPtr;
        currentPtr = currentPtr->_nextPtr;
        currentIndex++;
    }

    if (currentPtr == nullptr)
    {
        cout << "Index out of range. Element not removed." << endl;
        return false;
    }

    previousPtr->_nextPtr = currentPtr->_nextPtr;
    value = currentPtr->_data;
    delete currentPtr;

    if (previousPtr->_nextPtr == nullptr)
        _lastPtr = previousPtr;

    _count--;
    return true;
}

bool List::hasCycleSLL()
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

void List::print() const
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
        cout << currentPtr->_data << " ";
        currentPtr = currentPtr->_nextPtr;
    }
    cout << endl;
}

double List::getFirstValue() const {
    if (_firstPtr) {
        return _firstPtr->_data;
    }
    throw std::out_of_range("List is empty"); 
}

size_t List::getElementCount() const
{
    return _count;
}
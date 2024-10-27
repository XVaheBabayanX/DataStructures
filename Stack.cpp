#include "Stack.h"

Stack::Stack() : _list() {}

Stack::~Stack() {}

void Stack::Push(const double value)
{
    _list.insertAtFront(value);
}

bool Stack::Pop(double& value)
{
    return _list.removeFromFront(value);
}

bool Stack::Top(double& value)
{
    if (_list.isEmpty())
        return false;

    value = _list.getFirstValue();
    return true;
}

bool Stack::isEmpty() const
{
    return _list.isEmpty();
}

size_t Stack::size() const
{
    return _list.getElementCount();
}
#include "Queue.h"

Queue::Queue() {}

Queue::~Queue() {}

void Queue::enqueue(double value)
{
    _list.insertAtBack(value);  
}

bool Queue::dequeue(double& value)
{
    return _list.removeFromFront(value);  
}

bool Queue::isEmpty() const
{
    return _list.isEmpty();  
}

size_t Queue::size() const
{
    return _list.getElementCount();  
}

void Queue::print() const
{
    _list.print();  
}

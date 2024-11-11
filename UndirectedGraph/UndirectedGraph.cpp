#include "UndirectedGraph.h"
#include <iostream>

BidirectionalGraph::BidirectionalGraph(size_t vertices) : _vertices(vertices), _edges(0), adjList(vertices) {}

BidirectionalGraph::~BidirectionalGraph() {}

void BidirectionalGraph::addVertex()
{
    adjList.push_back(DoublyLinkedList());
    _vertices++;
}

void BidirectionalGraph::removeVertex(size_t v)
{
    if (v >= _vertices)
        return;

    adjList[v].clear();

    for (size_t i = 0; i < _vertices; ++i) {
        if (i != v) {
            adjList[i].removeElement(v); 
        }
    }

    adjList.erase(adjList.begin() + v);
    _vertices--;

    for (size_t i = 0; i < _vertices; ++i) {
        ListNode* current = adjList[i].getFirstPtr();
        while (current != nullptr) {
            if (current->_vertex > v) {
                current->_vertex--;  
            }
            current = current->_nextPtr;
        }
    }
}

void BidirectionalGraph::addEdge(size_t u, size_t v, double weight)
{
    if (u < _vertices && v < _vertices)
    {
        if (hasEdge(u, v)) {
            std::cout << "Edge already exists between vertex " << u << " and vertex " << v << ".\n";
        }
        else {
            adjList[u].insertAtBack(v, weight);
            adjList[v].insertAtBack(u, weight);  
            _edges++;
        }
    }
}

bool BidirectionalGraph::removeEdge(size_t u, size_t v)
{
    if (u >= _vertices || v >= _vertices)
        return false;

    bool removedFromU = adjList[u].removeElement(v);
    bool removedFromV = adjList[v].removeElement(u);

    if (removedFromU && removedFromV) {
        _edges--;  
        return true;
    }
    return false;
}

bool BidirectionalGraph::changeEdge(size_t u, size_t v, double newWeight)
{
    if (u >= _vertices || v >= _vertices)
        return false;  

    ListNode* current = adjList[u].getFirstPtr();
    while (current != nullptr)
    {
        if (current->_vertex == v)
        {
            current->_weight = newWeight;  
            break;
        }
        current = current->_nextPtr;
    }

    current = adjList[v].getFirstPtr();
    while (current != nullptr)
    {
        if (current->_vertex == u)
        {
            current->_weight = newWeight;  
            return true;
        }
        current = current->_nextPtr;
    }

    return false;  
}

bool BidirectionalGraph::hasEdge(size_t u, size_t v) const
{
    if (u >= _vertices)
        return false;

    ListNode* current = adjList[u].getFirstPtr();
    while (current != nullptr)
    {
        if (current->_vertex == v)
            return true;
        current = current->_nextPtr;
    }

    return false;
}

std::vector<size_t> BidirectionalGraph::getConnectedVertices(size_t v) const {
    std::vector<size_t> connectedVertices;

    if (v < _vertices) {
        ListNode* current = adjList[v].getFirstPtr();
        while (current != nullptr) {
            connectedVertices.push_back(current->_vertex);
            current = current->_nextPtr;
        }
    }

    return connectedVertices;
}

size_t BidirectionalGraph::getConnectedVerticesCount(size_t v) const {
    size_t count = 0;

    if (v < _vertices) {
        ListNode* current = adjList[v].getFirstPtr();
        while (current != nullptr) {
            ++count;
            current = current->_nextPtr;
        }
    }

    return count;
}

double BidirectionalGraph::getWeight(size_t u, size_t v) const
{
    if (u >= _vertices)
        throw out_of_range("Vertex 'u' is out of range");

    ListNode* current = adjList[u].getFirstPtr();
    while (current != nullptr)
    {
        if (current->_vertex == v)
            return current->_weight;

        current = current->_nextPtr;
    }

    throw runtime_error("Edge does not exist");
}


void BidirectionalGraph::printGraph() {
    std::cout << "\nGraph representation:\n";

    for (size_t i = 0; i < adjList.size(); ++i) {
        std::cout << "V" << i;

        if (!adjList[i].isEmpty()) {
            std::cout << " -> ";

            ListNode* current = adjList[i].getFirstPtr();

            while (current != nullptr) {
                std::cout << "[V" << current->_vertex << "|W" << current->_weight << "] ";
                current = current->_nextPtr;
            }
        }

        std::cout << "\n";
    }
    std::cout << "\n";
}

bool BidirectionalGraph::detectCycleUtil(size_t v, std::vector<bool>& visited, double parent) {
    visited[v] = true;

    ListNode* current = adjList[v].getFirstPtr();
    while (current != nullptr) {
        size_t adjacent = current->_vertex;
        if (!visited[adjacent]) {
            if (detectCycleUtil(adjacent, visited, static_cast<double>(v))) {
                return true;
            }
        }
        else if (static_cast<double>(adjacent) != parent) {
            return true;
        }
        current = current->_nextPtr;
    }
    return false;
}

bool BidirectionalGraph::detectCycle() {
    std::vector<bool> visited(_vertices, false);

    for (size_t i = 0; i < _vertices; ++i) {
        if (!visited[i]) {  
            if (detectCycleUtil(i, visited, -1)) { 
                return true;
            }
        }
    }
    return false;
}

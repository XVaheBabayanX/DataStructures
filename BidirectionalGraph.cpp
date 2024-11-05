#include "BidirectionalGraph.h"
#include <iostream>

BidirectionalGraph::BidirectionalGraph(size_t vertices) : vertices(vertices), adjList(vertices) {}

BidirectionalGraph::~BidirectionalGraph() {}

void BidirectionalGraph::addEdge(size_t u, size_t v, int weight)
{
    if (u < vertices && v < vertices)
    {
        if (hasEdge(u, v)) {
            std::cout << "Edge already exists between vertex " << u << " and vertex " << v << ".\n";
        }
        else {
            adjList[u].insertAtBack(v, weight);
            adjList[v].insertAtBack(u, weight);  
        }
    }
}

bool BidirectionalGraph::removeEdge(size_t u, size_t v)
{
    if (u >= vertices || v >= vertices)
        return false;

    bool removedFromU = adjList[u].removeElement(v);
    bool removedFromV = adjList[v].removeElement(u); 

    return removedFromU && removedFromV;
}

bool BidirectionalGraph::hasEdge(size_t u, size_t v) const
{
    if (u >= vertices)
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

bool BidirectionalGraph::detectCycleUtil(size_t v, std::vector<bool>& visited, int parent) {
    visited[v] = true;

    ListNode* current = adjList[v].getFirstPtr();
    while (current != nullptr) {
        size_t adjacent = current->_vertex;
        if (!visited[adjacent]) {
            if (detectCycleUtil(adjacent, visited, static_cast<int>(v))) {
                return true;
            }
        }
        else if (static_cast<int>(adjacent) != parent) {
            return true;
        }
        current = current->_nextPtr;
    }
    return false;
}

bool BidirectionalGraph::detectCycle() {
    std::vector<bool> visited(vertices, false);

    for (size_t i = 0; i < vertices; ++i) {
        if (!visited[i]) {  
            if (detectCycleUtil(i, visited, -1)) { 
                return true;
            }
        }
    }
    return false;
}

void BidirectionalGraph::addVertex()
{
    adjList.push_back(DoublyLinkedList());
    vertices++;
}

void BidirectionalGraph::removeVertex(size_t v)
{
    if (v >= vertices)
        return;

    adjList[v].clear();

    for (size_t i = 0; i < vertices; ++i) {
        if (i != v) {
            adjList[i].removeElement(v);
        }
    }

    adjList.erase(adjList.begin() + v);
    vertices--;

    for (size_t i = 0; i < vertices; ++i) {
        ListNode* current = adjList[i].getFirstPtr();
        while (current != nullptr) {
            if (current->_vertex > v) {
                current->_vertex--; 
            }
            current = current->_nextPtr;
        }
    }
}

#include "Graph.h"
#include <iostream>

Graph::Graph(size_t vertices) : vertices(vertices), adjList(vertices)
{
}

Graph::~Graph()
{
}

void Graph::addEdge(size_t u, size_t v, int weight)
{
    if (u < vertices && v < vertices)
    {
        if (hasEdge(u, v)) {
            cout << "Edge already exists between vertex " << u << " and vertex " << v << ".\n";
        }
        else {
            adjList[u].insertAtBack(v, weight);
        }
    }
}

bool Graph::removeEdge(size_t u, size_t v)
{
    if (u >= vertices)
        return false;

    size_t vertex;
    for (size_t i = 0; i < adjList[u].getElementCount(); ++i)
    {
        if (adjList[u].removeAtIndex(i, vertex) && vertex == v)
        {
            return true;
        }
    }
    return false;
}

bool Graph::hasEdge(size_t u, size_t v) const
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

void Graph::printGraph() {
    cout << "\nGraph representation:\n";

    for (size_t i = 0; i < adjList.size(); ++i) {
        cout << "V" << i;  

        if (!adjList[i].isEmpty()) {
            cout << " -> ";

            ListNode* current = adjList[i].getFirstPtr();  

            while (current != nullptr) {
                cout << "[V" << current->_vertex << "|W" << current->_weight << "] ";
                current = current->_nextPtr;  
            }
        }

        cout << "\n";  
    }
}


bool Graph::detectCycleUtil(size_t v, std::vector<bool>& visited, std::vector<bool>& recursionStack) {
    if (!visited[v]) {
        visited[v] = true;
        recursionStack[v] = true;

        ListNode* current = adjList[v].getFirstPtr();
        while (current != nullptr) {
            if (!visited[current->_vertex] && detectCycleUtil(current->_vertex, visited, recursionStack)) {
                return true;
            }
            else if (recursionStack[current->_vertex]) {
                return true;  
            }
            current = current->_nextPtr;
        }
    }
    recursionStack[v] = false;  
    return false;
}

bool Graph::detectCycle() {
    std::vector<bool> visited(vertices, false);
    std::vector<bool> recursionStack(vertices, false);

    for (size_t i = 0; i < vertices; ++i) {
        if (detectCycleUtil(i, visited, recursionStack)) {
            return true;  
        }
    }
    return false;  
}

void Graph::addVertex()
{
    adjList.push_back(DoublyLinkedList());
    vertices++;
}

void Graph::removeVertex(size_t v)
{
    if (v >= vertices)
        return;

    adjList[v] = DoublyLinkedList();

    for (size_t i = 0; i < vertices; ++i)
    {
        size_t vertex;
        for (size_t j = 0; j < adjList[i].getElementCount(); ++j)
        {
            if (adjList[i].removeAtIndex(j, vertex) && vertex == v)
            {
                j--;  
            }
        }
    }
}

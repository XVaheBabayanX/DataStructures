#include "DirectionalGraph.h"

DirectionalGraph::DirectionalGraph(size_t vertices) : vertices(vertices), adjList(vertices) {}

DirectionalGraph::~DirectionalGraph() {}

void DirectionalGraph::addEdge(size_t u, size_t v, int weight)
{
    if (u < vertices && v < vertices)
    {
        if (hasEdge(u, v)) {
            std::cout << "Edge already exists from vertex " << u << " to vertex " << v << ".\n";
        }
        else {
            adjList[u].insertAtBack(v, weight);  
        }
    }
}

bool DirectionalGraph::removeEdge(size_t u, size_t v)
{
    if (u >= vertices || v >= vertices)
        return false;

    return adjList[u].removeElement(v); 
}

bool DirectionalGraph::hasEdge(size_t u, size_t v) const
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

void DirectionalGraph::printGraph() {
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

bool DirectionalGraph::detectCycleUtil(size_t v, std::vector<bool>& visited, std::vector<bool>& recursionStack) {
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

bool DirectionalGraph::detectCycle() {
    std::vector<bool> visited(vertices, false);
    std::vector<bool> recursionStack(vertices, false);

    for (size_t i = 0; i < vertices; ++i) {
        if (detectCycleUtil(i, visited, recursionStack)) {
            return true;
        }
    }
    return false;
}

void DirectionalGraph::addVertex()
{
    adjList.push_back(DoublyLinkedList());
    vertices++;
}

void DirectionalGraph::removeVertex(size_t v)
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

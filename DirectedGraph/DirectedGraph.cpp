#include "DirectionalGraph.h"

DirectionalGraph::DirectionalGraph(size_t vertices) : _vertices(vertices), _edges(0), adjList(vertices) {}

DirectionalGraph::~DirectionalGraph() {}

void DirectionalGraph::addVertex()
{
    adjList.push_back(DoublyLinkedList());
    _vertices++;
}

void DirectionalGraph::removeVertex(size_t v)
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

void DirectionalGraph::addEdge(size_t u, size_t v, double weight)
{
    if (u < _vertices && v < _vertices)
    {
        if (hasEdge(u, v)) {
            std::cout << "Edge already exists from vertex " << u << " to vertex " << v << ".\n";
        }
        else {
            adjList[u].insertAtBack(v, weight);
            _edges++;
        }
    }
}

bool DirectionalGraph::removeEdge(size_t u, size_t v)
{
    if (u >= _vertices || v >= _vertices)
        return false;

    bool removedFromU = adjList[u].removeElement(v);

    if (removedFromU) {
        _edges--;
        return true;
    }
    return false;
}

bool DirectionalGraph::changeEdge(size_t u, size_t v, double newWeight)
{
    if (u >= _vertices || v >= _vertices)
        return false;  

    ListNode* current = adjList[u].getFirstPtr();
    while (current != nullptr)
    {
        if (current->_vertex == v)
        {
            current->_weight = newWeight;  
            return true;
        }
        current = current->_nextPtr;
    }

    return false;  
}

bool DirectionalGraph::hasEdge(size_t u, size_t v) const
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

std::vector<size_t> DirectionalGraph::getOutgoingEdges(size_t v) const {
    std::vector<size_t> outgoingVertices;

    if (v < _vertices) {
        ListNode* current = adjList[v].getFirstPtr();
        while (current != nullptr) {
            outgoingVertices.push_back(current->_vertex);
            current = current->_nextPtr;
        }
    }

    return outgoingVertices;
}

size_t DirectionalGraph::getOutgoingEdgesCount(size_t v) const {
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

std::vector<size_t> DirectionalGraph::getIncomingEdges(size_t v) const {
    std::vector<size_t> incomingVertices;

    if (v < _vertices) {
        for (size_t i = 0; i < _vertices; ++i) {
            if (hasEdge(i, v)) {
                incomingVertices.push_back(i);
            }
        }
    }

    return incomingVertices;
}

size_t DirectionalGraph::getIncomingEdgesCount(size_t v) const {
    size_t count = 0;

    if (v < _vertices) {
        for (size_t i = 0; i < _vertices; ++i) {
            if (hasEdge(i, v)) {
                ++count;
            }
        }
    }

    return count;
}

double DirectionalGraph::getWeight(size_t u, size_t v) const
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
    std::vector<bool> visited(_vertices, false);
    std::vector<bool> recursionStack(_vertices, false);

    for (size_t i = 0; i < _vertices; ++i) {
        if (detectCycleUtil(i, visited, recursionStack)) {
            return true;
        }
    }
    return false;
}

#pragma once
#include "DLL.h"
#include <vector>
#include <iostream>

class DirectionalGraph
{
public:
    DirectionalGraph(size_t vertices);
    ~DirectionalGraph();

    void addVertex();
    void removeVertex(size_t v);
    size_t getVerticesCount() const { return _vertices; }

    void addEdge(size_t u, size_t v, double weight);
    bool removeEdge(size_t u, size_t v);
    bool changeEdge(size_t u, size_t v, double newWeight);
    bool hasEdge(size_t u, size_t v) const;
    double getWeight(size_t u, size_t v) const;
    size_t getEdgesCount() const { return _edges; }

    void printGraph();
    bool isEmpty() const { return _vertices == 0; }
    bool isConnected() const { return _edges > 0; }

    bool detectCycle();
    bool detectCycleUtil(size_t v, std::vector<bool>& visited, std::vector<bool>& recursionStack);
private:
    std::vector<DoublyLinkedList> adjList;
    size_t _vertices;
    size_t _edges;
};

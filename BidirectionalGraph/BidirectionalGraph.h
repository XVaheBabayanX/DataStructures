#pragma once
#include "DLL.h"
#include <vector>
#include <iostream>

class BidirectionalGraph
{
public:
    BidirectionalGraph(size_t vertices);
    ~BidirectionalGraph();

    void addEdge(size_t u, size_t v, int weight);
    bool removeEdge(size_t u, size_t v);
    bool hasEdge(size_t u, size_t v) const;
    void printGraph();

    bool detectCycle();
    bool detectCycleUtil(size_t v, std::vector<bool>& visited, int parent);

    void addVertex();
    void removeVertex(size_t v);
    size_t getVertexCount() const { return vertices; }

private:
    std::vector<DoublyLinkedList> adjList;
    size_t vertices;
};

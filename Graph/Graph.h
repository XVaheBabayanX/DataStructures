#pragma once

#include<vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

class Graph
{
public:
	Graph();
	Graph(const size_t&);
	Graph(const vector<vector<double>>&);
	~Graph();

	void addVertex();
	bool removeVertex(size_t v);
	bool hasVertex(size_t v) const;
	size_t getVerticesCount() const { return _vertices; }

	bool addEdge(size_t, size_t, double);
	bool removeEdge(size_t, size_t);
	bool changeEdge(size_t, size_t, double);
	bool hasEdge(size_t, size_t) const;
	double getWeight(size_t, size_t) const;
	size_t getEdgesCount() const { return _edges; }

	bool detectCycle() const;
	bool detectLoop();
	bool hasLoop(size_t) const;
	vector<size_t> getLoops();
	bool detectСontour() const;

	bool isEmpty() const { return _vertices == 0; }
	bool isConnected() const { return _edges > 0; }
	void PrintMatrix() const;
	void PrintGraph() const;
private:
	vector<vector<double>> _adjacency;
	size_t _vertices;
	size_t _edges;

	void Initialization();
	bool Copy(const vector<vector<double>>&);
	void setVertices(const size_t&);
	size_t maxDoubleLength() const;
	size_t maxVertexLength() const;

	bool dfsCycle(size_t, vector<bool>&, vector<bool>&) const;
	vector<vector<double>> MatrixMultiplication(const vector<vector<double>>&) const;
	double Trace(const vector<vector<double>>&) const;
	bool isZeroMatrix(const vector<vector<double>>&) const;

	const size_t DEFAUALT_VERTICES = 5;
	const size_t DEFAUALT_EDGES = 0;
	const double DEFAUALT_VALUE = 0;
	const size_t TERMINAL_VISIBLE_VERTICES = 17;
	const size_t  ACCURACY = 0;
};

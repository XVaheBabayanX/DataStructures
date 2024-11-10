#include "Graph.h"

Graph::Graph() : Graph(DEFAUALT_VERTICES) {}

Graph::Graph(const size_t &Vertices) : _edges(DEFAUALT_EDGES)
{
	setVertices(Vertices);
	Initialization();
}

Graph::Graph(const vector<vector<double>>& Other) : _edges(DEFAUALT_EDGES)
{
	if(Copy(Other))
		setVertices(Other.size());
	else {
		setVertices(DEFAUALT_VERTICES);
		Initialization();
	}
}

Graph::~Graph()
{
	_adjacency.clear();
}

void Graph::setVertices(const size_t& Vertices)
{
	_vertices = (Vertices >= 0) ? Vertices : DEFAUALT_VERTICES;
}

void Graph::Initialization()
{
	_adjacency = vector<vector<double>>(_vertices, vector<double>(_vertices, DEFAUALT_VALUE));
}

bool Graph::Copy(const vector<vector<double>>& Other)
{
	if (Other.empty()) {
		return false;
	}

	size_t cols = Other[0].size();

	if (cols != Other.size())
		return false;

	for (const auto& row : Other) {
		if (row.size() != cols) {
			return false;
		}
	}

	_adjacency = Other;

	return true;
}

size_t Graph::maxDoubleLength() const {
	if (_vertices == 0)
		return 0;

	size_t maxLength = 0;

	for (const auto& row : _adjacency) {
		for (double value : row) {
			ostringstream oss;
			oss << fixed << value;
			size_t length = oss.str().length();

			if (length > maxLength) {
				maxLength = length;
			}
		}
	}

	return maxLength;
}

size_t Graph::maxVertexLength() const {
	if (_vertices == 0)
		return 0;
	ostringstream oss;
	oss << fixed << _vertices - 1;
	return oss.str().length();
}

void Graph::PrintMatrix() const
{
	if (_vertices == 0)
		return;

	size_t space = maxDoubleLength();  
	size_t padding = maxVertexLength();
	cout << setw(space - padding) << " ";
	for (size_t column = 0; column < _vertices; column++) {
		cout << setw(space) << left << column << " ";
	}
	cout << endl;

	for (size_t row = 0; row < _vertices; row++) {
		cout << setw(padding) << right << row;
		for (size_t column = 0; column < _vertices; column++) {
			cout << setw(space) << fixed << setprecision(ACCURACY) << _adjacency[row][column] << " ";
		}
		cout << endl;
	}
}

void Graph::PrintGraph() const {
	std::cout << "\nGraph representation\n";

	for (size_t i = 0; i < _adjacency.size(); ++i) {
		std::cout << "V" << i;

		bool hasEdges = false;

		for (size_t j = 0; j < _adjacency[i].size(); ++j) {
			if (_adjacency[i][j] != DEFAUALT_VALUE) {
				if (!hasEdges) {
					std::cout << " -> ";
					hasEdges = true;
				}
				std::cout << "[V" << j << "|W" << _adjacency[i][j] << "] ";
			}
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}


void Graph::addVertex()
{
	for (auto& row : _adjacency)
	{
		row.push_back(DEFAUALT_VALUE);
	}
	_vertices++;
	_adjacency.push_back(vector<double>(_vertices, DEFAUALT_VALUE));
}

bool Graph::removeVertex(size_t v)
{
	if (!hasVertex(v))
		return false;

	_adjacency.erase(_adjacency.begin() + v);
	for (auto& row : _adjacency)
	{
		row.erase(row.begin() + v);
	}
	_vertices--;
	return true;
}

bool Graph::hasVertex(size_t v) const
{
	if (v < 0 || v >(_vertices - 1))
		return false;
	return true;
}

bool Graph::addEdge(size_t u, size_t v, double weight)
{
	if (hasEdge(u, v))
		return false;

	_adjacency[u][v] = weight;
	_edges++;
	return true;
}

bool Graph::removeEdge(size_t u, size_t v)
{
	if (!hasEdge(u,v))
		return false;

	_adjacency[u][v] = DEFAUALT_VALUE;
	_edges--;
	return true;
}

bool Graph::changeEdge(size_t u, size_t v, double weight)
{
	if (!hasEdge(u, v))
		return false;

	_adjacency[u][v] = weight;
	return true;
}

bool Graph::hasEdge(size_t u, size_t v) const
{
	if (!hasVertex(u) || !hasVertex(v))
		return false;
	if (_adjacency[u][v] == DEFAUALT_VALUE)
		return false;
	return true;
}

std::vector<size_t> Graph::getOutgoingEdges(size_t v) const {
	std::vector<size_t> outgoingVertices;

	if (hasVertex(v)) {
		for (size_t j = 0; j < _vertices; ++j) {
			if (_adjacency[v][j] != DEFAUALT_VALUE) {  
				outgoingVertices.push_back(j);
			}
		}
	}

	return outgoingVertices;
}

size_t Graph::getOutgoingEdgesCount(size_t v) const {
	size_t count = 0;

	if (hasVertex(v)) {
		for (size_t j = 0; j < _vertices; ++j) {
			if (_adjacency[v][j] != DEFAUALT_VALUE) {  
				++count;
			}
		}
	}

	return count;
}

std::vector<size_t> Graph::getIncomingEdges(size_t v) const {
	std::vector<size_t> incomingVertices;

	if (hasVertex(v)) {
		for (size_t i = 0; i < _vertices; ++i) {
			if (_adjacency[i][v] != DEFAUALT_VALUE) {  
				incomingVertices.push_back(i);
			}
		}
	}

	return incomingVertices;
}

size_t Graph::getIncomingEdgesCount(size_t v) const {
	size_t count = 0;

	if (hasVertex(v)) {
		for (size_t i = 0; i < _vertices; ++i) {
			if (_adjacency[i][v] != DEFAUALT_VALUE) {  
				++count;
			}
		}
	}

	return count;
}

double Graph::getWeight(size_t u, size_t v) const
{
	if (!hasEdge(u, v))
		return false;
	return _adjacency[u][v];
}

bool Graph::detectCycle() const {
	if (_vertices == 0 || _edges == 0)
		return false;

	vector<bool> visited(_vertices, false);
	vector<bool> recStack(_vertices, false); 

	for (size_t vertex = 0; vertex < _vertices; ++vertex) {
		if (!visited[vertex]) {
			if (dfsCycle(vertex, visited, recStack)) {
				return true;
			}
		}
	}
	return false;
}

bool Graph::dfsCycle(size_t vertex, vector<bool>& visited, vector<bool>& recStack) const {
	visited[vertex] = true;
	recStack[vertex] = true; 

	for (int adjVertex = 0; adjVertex < _vertices; ++adjVertex) {
		if (_adjacency[vertex][adjVertex] != DEFAUALT_VALUE) {
			if (!visited[adjVertex]) {
				if (dfsCycle(adjVertex, visited, recStack)) {
					return true;
				}
			}
			else if (recStack[adjVertex]) {
				return true; 
			}
		}
	}

	recStack[vertex] = false; 
	return false;
}


bool Graph::detectLoop()
{
	if (_vertices == 0 || _edges == 0)
		return false;
	for (size_t vertice = 0; vertice < _vertices; vertice++) {
		if (_adjacency[vertice][vertice] != DEFAUALT_VALUE)
			return true;
	}
	return false;
}

bool Graph::hasLoop(size_t v) const
{
	if (!hasVertex(v))
		return false;
	if (_adjacency[v][v] != DEFAUALT_VALUE)
		return true;
	return false;
}

vector<size_t> Graph::getLoops()
{
	vector<size_t> loops;
	if (!detectLoop())
		return loops;

	for (size_t vertice = 0; vertice < _vertices; vertice++) {
		if (_adjacency[vertice][vertice] != DEFAUALT_VALUE)
			loops.push_back(vertice);
	}

	return loops;
}

bool Graph::detectСontour() const
{
	if (_vertices == 0 || _edges == 0)
		return false;

	vector<vector<double>> Matrix = _adjacency;

	while (!isZeroMatrix(Matrix))
	{
		if (Trace(Matrix) != DEFAUALT_VALUE)
			return true;
		Matrix = MatrixMultiplication(Matrix);
	}
	return false;
}

vector<vector<double>> Graph::MatrixMultiplication(const vector<vector<double>>& Matrix) const
{
	vector<vector<double>> AMatrix(_vertices, vector<double>(_vertices, DEFAUALT_VALUE));
	for (int i = 0; i < _vertices; i++)
	{
		for (int j = 0; j < _vertices; j++)
		{
			for (int k = 0; k < _vertices; k++)
			{
				AMatrix[i][j] += Matrix[i][k] * Matrix[k][j];
			}
		}
	}
	return AMatrix;
}

double Graph::Trace(const vector<vector<double>>& Matrix) const
{
	double Trace = 0;
	for (size_t vertice = 0; vertice < _vertices; vertice++) {
		Trace += Matrix[vertice][vertice];
	}
	return Trace;
}

bool Graph::isZeroMatrix(const vector<vector<double>>& Matrix) const
{
	if (Matrix.empty())
		return false;
	return all_of(Matrix.begin(), Matrix.end(), [](const vector<double>& row) {
		return all_of(row.begin(), row.end(), [](double value) {
			return value == 0.0;
		});
	});

}

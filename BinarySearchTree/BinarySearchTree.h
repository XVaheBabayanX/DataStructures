#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

class Node
{
public:
	Node(const int Key, Node* Parent = nullptr , Node* Left = nullptr, Node* Right = nullptr) : _key(Key), _parent(Parent), _leftChild(Left), _rightChild(Right) {}
	int _key = 0;
	Node* _parent = nullptr;
	Node* _leftChild = nullptr;
	Node* _rightChild = nullptr;
};

class BinarySearchTree
{
public:
	BinarySearchTree() : _Root(nullptr), _nodes(0) {}
	BinarySearchTree(const BinarySearchTree&);
	BinarySearchTree(const Node*);
	~BinarySearchTree();
private:
	void copyTree(Node*, const Node*);
public:
	void clearTree(Node*);

	bool Insert(const int);
	bool Delete(const int);
	Node* Search(const int) const;
	int MinimumKey() const;
	int MaximumKey() const;
	Node* Minimum(Node*) const;
	Node* Maximum(Node*) const;
	Node* Successor(Node*) const;
	Node* Predecessor(Node*) const;
	Node* Sibling(Node*) const;

	std::vector<Node*> InorderTraversal() const;
	static std::vector<Node*> InorderTraversal(Node*);
	static void InorderTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> PreorderTraversal() const;
	static std::vector<Node*> PreorderTraversal(Node*);
	static void PreorderTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> PostorderTraversal() const;
	static std::vector<Node*> PostorderTraversal(Node*);
	static void PostorderTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> LevelOrderTraversal() const;
	static std::vector<Node*> LevelOrderTraversal(Node*);
	static void LevelOrderTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> ReverseLevelOrderTraversal() const;
	static std::vector<Node*> ReverseLevelOrderTraversal(Node*);
	static void ReverseLevelOrderTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> BoundaryTraversal() const;
	static std::vector<Node*> BoundaryTraversal(Node*);
	static void BoundaryTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> DiagonalTraversal() const;
	static std::vector<Node*> DiagonalTraversal(Node*);
	static void DiagonalTraversal(Node*, std::vector<Node*>&);

	std::vector<Node*> RangeSearch(int, int) const;
	static std::vector<Node*> RangeSearch(Node*, int, int);
	static void RangeSearch(Node*, int, int, std::vector<Node*>&);

	std::string toString(const std::vector<Node*>&) const;
	static std::string toString(std::vector<Node*>&);
	std::string toStringInorder() const;
	std::string toStringPreorder() const;
	std::string toStringPostorder() const;
	std::string toStringLevelOrder() const;
	std::string toStringReverseLevelOrder() const;
	std::string toStringBoundary() const;
	std::string toStringDiagonal() const;
	std::string toStringRange(int, int) const;

	void balance();
	Node* buildBalancedTree(std::vector<Node*>& , int, int);

	void visualize() const;
	void visualize(Node* node, std::string, bool) const;

	Node* getRoot() { return _Root; }
	static Node* getRoot(Node*);

	size_t getNodeCount() const { return _nodes; }
	static int getNodeCount(Node*);

	int getDepth() const;
	static int getDepth(Node*);

	bool isFull() const;
	static bool isFull(Node*);

	bool isPerfect() const;
	static bool isPerfect(Node*, int, int); 

	bool isBalanced() const;
	static int isBalanced(Node*);

	bool isComplete() const;
	static bool isComplete(Node*);

	bool isDegenerate() const;
	static bool isDegenerate(Node*);

	bool isEmpty() { return _Root == nullptr; }
	static bool isEmpty(Node* node) { return node == nullptr; }
	static bool isLeaf(Node* node) { return (node->_leftChild == nullptr) && (node->_rightChild == nullptr); }

private:
	Node* CreateNode(const int Key) const { return new Node(Key); }
	static void addLeftBoundary(Node* node, std::vector<Node*>& result);
	static void addLeaves(Node* node, std::vector<Node*>& result);
	static void addRightBoundary(Node* node, std::vector<Node*>& result);
private:
	Node* _Root = nullptr;
	size_t _nodes = 0;
};

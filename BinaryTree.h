#pragma once

#include <vector>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

class Node
{
public:
	Node(const size_t Bucket, const std::string Key = "", const double Data = 0, Node* Parent = nullptr, Node* Left = nullptr, Node* Right = nullptr) : _bucket(Bucket), _key(Key), _data(Data), _parent(Parent), _leftChild(Left), _rightChild(Right) {}
	size_t _bucket = 0;
	std::string _key = DefaultKey;
	double _data = DefaultData;
	Node* _parent = nullptr;
	Node* _leftChild = nullptr;
	Node* _rightChild = nullptr;
	bool isDefault() const { return (_key == DefaultKey) && (_data == DefaultData); }
private:
	const std::string DefaultKey = "";
	const double DefaultData = 0;
};

class BinaryTree
{
public:
	BinaryTree() : _Root(nullptr), _nodes(0) {}
	BinaryTree(const BinaryTree&);
	BinaryTree(const Node*);
	~BinaryTree();
private:
	void copyTree(Node*, const Node*);
public:
	void clearTree(Node*);

	bool Insert(const size_t, const std::string, const double);
	bool Delete(const size_t);
	Node* Search(const size_t) const;
	bool Change(const size_t, const std::string, const double) const;
	size_t MinimumBucket() const;
	size_t MaximumBucket() const;
	Node* Minimum(Node*) const;
	Node* Maximum(Node*) const;
	Node* Successor(Node*) const;
	Node* Predecessor(Node*) const;

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

	std::vector<Node*> RangeSearch(size_t, size_t) const;
	static std::vector<Node*> RangeSearch(Node*, size_t, size_t);
	static void RangeSearch(Node*, size_t, size_t, std::vector<Node*>&);

	std::string toString(const std::vector<Node*>&) const;
	static std::string toString(std::vector<Node*>&);
	std::string toStringInorder() const;
	std::string toStringPreorder() const;
	std::string toStringPostorder() const;
	std::string toStringLevelOrder() const;
	std::string toStringRange(size_t, size_t) const;

	void balance();
	static Node* buildBalancedTree(std::vector<Node*>&, int, int);
	Node* buildBalancedTree(const std::vector<size_t>&, int, int);

	void visualize() const;
	void visualize(Node* node, std::string, bool) const;

	void setRoot(Node* newRoot) { _Root = newRoot; }
	Node* getRoot() { return _Root; }
	static Node* getRoot(Node*);

	size_t getNodeCount() const { return _nodes; }
	static size_t getNodeCount(Node*);

	size_t getDepth() const;
	static size_t getDepth(Node*);

	bool isPerfect() const;
	static bool isPerfect(Node*, size_t);
	static bool isPerfect(Node*);


	bool isEmpty() { return _Root == nullptr; }
	static bool isEmpty(Node* node) { return node == nullptr; }
	static bool isLeaf(Node* node) { return (node->_leftChild == nullptr) && (node->_rightChild == nullptr); }

private:
	Node* CreateNode(const size_t Bucket, const std::string Key, const double Data) const { return new Node(Bucket, Key, Data); }

private:
	Node* _Root = nullptr;
	size_t _nodes = 0;
};
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
	Node(const std::string Key = "", const double Data = 0, Node* Parent = nullptr, Node* Left = nullptr, Node* Right = nullptr) : _key(Key), _data(Data), _parent(Parent), _leftChild(Left), _rightChild(Right) {}
	std::string _key = DefaultKey;
	double _data = DefaultData;
	Node* _parent = nullptr;
	Node* _leftChild = nullptr;
	Node* _rightChild = nullptr;
	void Default(Node* node) const { node->_key = DefaultKey; node->_data = DefaultData; }
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

	bool Insert(const std::string, const double);
	bool Delete(const std::string);
	Node* Search(const std::string) const;
	bool Change(const std::string, const double) const;
	std::string MinimumKey() const;
	std::string MaximumKey() const;
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

	std::vector<Node*> RangeSearch(std::string, std::string) const;
	static std::vector<Node*> RangeSearch(Node*, std::string, std::string);
	static void RangeSearch(Node*, std::string, std::string, std::vector<Node*>&);

	std::string toString(const std::vector<Node*>&) const;
	static std::string toString(std::vector<Node*>&);
	std::string toStringInorder() const;
	std::string toStringPreorder() const;
	std::string toStringPostorder() const;
	std::string toStringLevelOrder() const;
	std::string toStringRange(std::string, std::string) const;

	void balance();
	static Node* buildBalancedTree(std::vector<Node*>&, int, int);
	Node* buildBalancedTree(const std::vector<std::string>&, int, int);

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
	Node* CreateNode(const std::string Key, const double Data) const { return new Node(Key, Data); }

private:
	Node* _Root = nullptr;
	size_t _nodes = 0;
	const std::string DefaultKey = "";
	const double DefaultData = 0;
};
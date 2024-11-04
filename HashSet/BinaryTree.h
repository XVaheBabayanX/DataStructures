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
	Node(const std::string& Bucket, const std::string& Key, Node* Parent = nullptr, Node* Left = nullptr, Node* Right = nullptr)
		: _bucket(Bucket), _key(Key), _parent(Parent), _leftChild(Left), _rightChild(Right) {}
	std::string _bucket;
	std::string _key;
	Node* _parent = nullptr;
	Node* _leftChild = nullptr;
	Node* _rightChild = nullptr;

	bool isDefault() const { return (_key == DefaultKey); }
private:
	const std::string DefaultKey = "";
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

	bool Insert(const std::string, const std::string);
	bool Delete(const std::string);
	Node* Search(const std::string) const;
	std::string MinimumBucket() const;
	std::string MaximumBucket() const;
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
	static bool isPerfect(Node*, int, int);

	bool isBalanced() const;
	static int isBalanced(Node* node);

	bool isComplete() const;
	static bool isComplete(Node*);

	bool isEmpty() { return _Root == nullptr; }
	static bool isEmpty(Node* node) { return node == nullptr; }
	static bool isLeaf(Node* node) { return (node->_leftChild == nullptr) && (node->_rightChild == nullptr); }

private:
	Node* CreateNode(const std::string Bucket, const std::string Key) const { return new Node(Bucket, Key); }

private:
	Node* _Root = nullptr;
	size_t _nodes = 0;
	const std::string DefaultKey = "";
};

#include "BinaryTree.h"

BinaryTree::BinaryTree(const BinaryTree& other) : _Root(nullptr), _nodes(0) {
	if (other._Root != nullptr) {
		_Root = new Node(other._Root->_key);
		_nodes++;
		copyTree(_Root, other._Root);
	}
}

BinaryTree::BinaryTree(const Node* root) : _Root(nullptr), _nodes(0) {
	if (root != nullptr) {
		_Root = new Node(root->_key); 
		_nodes++;
		copyTree(_Root, root); 
	}
}

BinaryTree::~BinaryTree() {
	clearTree(_Root);
	_Root = nullptr;
	_nodes = 0;
}

void BinaryTree::copyTree(Node* thisNode,const Node* otherNode) {
	if (otherNode->_leftChild != nullptr) {
		thisNode->_leftChild = new Node(otherNode->_leftChild->_key, thisNode);
		_nodes++;
		copyTree(thisNode->_leftChild, otherNode->_leftChild);
	}
	if (otherNode->_rightChild != nullptr) {
		thisNode->_rightChild = new Node(otherNode->_rightChild->_key, thisNode);
		_nodes++;
		copyTree(thisNode->_rightChild, otherNode->_rightChild);
	}
}

void BinaryTree::clearTree(Node* node) {
	if (node == nullptr) return;
	clearTree(node->_leftChild);
	clearTree(node->_rightChild);
	delete node;
}

Node* BinaryTree::getRoot(Node* node) {
	if (node->_parent == nullptr) return nullptr;
	Node* Root = node->_parent;
	while (Root->_parent != nullptr)
	{
		Root = Root->_parent;
	}
	return Root;
}

bool BinaryTree::Insert(const int Key) {
	if (isEmpty(_Root)) {
		_Root = CreateNode(Key);
		_nodes++;
		return true;
	}
	Node* NewNode = CreateNode(Key);
	Node* Current = _Root;
	Node* Parent = nullptr;
	while (Current != nullptr) {
		Parent = Current;
		if (Key < Current->_key) Current = Current->_leftChild;	
		else if (Key > Current->_key) Current = Current->_rightChild;
		else return false;
	}
	if (Key < Parent->_key) Parent->_leftChild = NewNode;
	else Parent->_rightChild = NewNode;
	NewNode->_parent = Parent;
	_nodes++;
	return true;
}

bool BinaryTree::Delete(const int Key) {
	Node* TargetNode = Search(Key);
	if (TargetNode == nullptr) return false;

	if (isLeaf(TargetNode)) {
		if (TargetNode == _Root) {
			delete _Root;
			_Root = nullptr;
		}
		else {
			if (TargetNode->_parent->_leftChild == TargetNode) {
				TargetNode->_parent->_leftChild = nullptr;
			}
			else {
				TargetNode->_parent->_rightChild = nullptr;
			}
			delete TargetNode;
		}
	}
	else if (TargetNode->_leftChild == nullptr || TargetNode->_rightChild == nullptr) {
		Node* Child = (TargetNode->_leftChild != nullptr) ? TargetNode->_leftChild : TargetNode->_rightChild;
		if (TargetNode == _Root) {
			_Root = Child;
			_Root->_parent = nullptr;
		}
		else {
			if (TargetNode->_parent->_leftChild == TargetNode) {
				TargetNode->_parent->_leftChild = Child;
			}
			else {
				TargetNode->_parent->_rightChild = Child;
			}
			Child->_parent = TargetNode->_parent;
			delete TargetNode;
		}
	}
	else {
		Node* SuccessorNode = Minimum(TargetNode->_rightChild);
		TargetNode->_key = SuccessorNode->_key;

		if (SuccessorNode->_parent->_leftChild == SuccessorNode) {
			SuccessorNode->_parent->_leftChild = SuccessorNode->_rightChild;
		}
		else {
			SuccessorNode->_parent->_rightChild = SuccessorNode->_rightChild;
		}
		if (SuccessorNode->_rightChild != nullptr) {
			SuccessorNode->_rightChild->_parent = SuccessorNode->_parent;
		}
		delete SuccessorNode;
	}
	_nodes--;
	return true;
}


Node* BinaryTree::Search(const int Key) const {
	if (isEmpty(_Root)) return nullptr;
	Node* Current = _Root;
	while (Current != nullptr) {
		if (Current->_key == Key) return Current;
		else if (Key < Current->_key) Current = Current->_leftChild;
		else Current = Current->_rightChild;
	}
	return nullptr;
}

int BinaryTree::MinimumKey() const {
	if (isEmpty(_Root)) return 0;
	return Minimum(_Root)->_key;
}

int BinaryTree::MaximumKey() const {
	if (isEmpty(_Root)) return 0;
	return Maximum(_Root)->_key;
}

Node* BinaryTree::Minimum(Node* node) const {
	if (isEmpty(node)) return nullptr;
	Node* Minimum = node;
	while (Minimum->_leftChild != nullptr)
	{
		Minimum = Minimum->_leftChild;
	}
	return Minimum;
}

Node* BinaryTree::Maximum(Node* node) const {
	if (isEmpty(node)) return nullptr;
	Node* Maximum = node;
	while (Maximum->_rightChild != nullptr)
	{
		Maximum = Maximum->_rightChild;
	}
	return Maximum;
}

Node* BinaryTree::Successor(Node* node) const {
	if (node == nullptr) return nullptr;
	if (node->_rightChild != nullptr)
		return Minimum(node->_rightChild);
	Node* Parent = node->_parent;
	while (Parent != nullptr && node == Parent->_rightChild) {
		node = Parent;
		Parent = Parent->_parent;
	}
	return Parent;
}

Node* BinaryTree::Predecessor(Node* node) const {
	if (node == nullptr) return nullptr;
	if (node->_leftChild != nullptr)
		return Maximum(node->_leftChild);
	Node* Parent = node->_parent;
	while (Parent != nullptr && node == Parent->_leftChild) {
		node = Parent;
		Parent = Parent->_parent;
	}
	return Parent;
}

void BinaryTree::InorderTraversal(Node* node, std::vector<Node*>& result) {
	if (node != nullptr) {
		InorderTraversal(node->_leftChild, result);
		result.push_back(node);
		InorderTraversal(node->_rightChild, result);
	}
}

std::vector<Node*> BinaryTree::InorderTraversal() const {
	std::vector<Node*> result;
	InorderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinaryTree::InorderTraversal(Node* node) {
	std::vector<Node*> result;
	InorderTraversal(node, result);
	return result;
}

void BinaryTree::PreorderTraversal(Node* node, std::vector<Node*>& result) {
	if (node != nullptr) {
		result.push_back(node);                          
		PreorderTraversal(node->_leftChild, result);     
		PreorderTraversal(node->_rightChild, result);    
	}
}

std::vector<Node*> BinaryTree::PreorderTraversal() const {
	std::vector<Node*> result;
	PreorderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinaryTree::PreorderTraversal(Node* node) {
	std::vector<Node*> result;
	PreorderTraversal(node, result);
	return result;
}

void BinaryTree::PostorderTraversal(Node* node, std::vector<Node*>& result) {
	if (node != nullptr) {
		PostorderTraversal(node->_leftChild, result);    
		PostorderTraversal(node->_rightChild, result);   
		result.push_back(node);                          
	}
}

std::vector<Node*> BinaryTree::PostorderTraversal() const {
	std::vector<Node*> result;
	PostorderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinaryTree::PostorderTraversal(Node* node) {
	std::vector<Node*> result;
	PostorderTraversal(node, result);
	return result;
}

void BinaryTree::LevelOrderTraversal(Node* node, std::vector<Node*>& result) {
	if (node == nullptr) return; 

	std::queue<Node*> queue; 
	queue.push(node); 

	while (!queue.empty()) {
		Node* currentNode = queue.front(); 
		queue.pop(); 
		result.push_back(currentNode); 

		if (currentNode->_leftChild != nullptr) {
			queue.push(currentNode->_leftChild);
		}
		if (currentNode->_rightChild != nullptr) {
			queue.push(currentNode->_rightChild);
		}
	}
}

std::vector<Node*> BinaryTree::LevelOrderTraversal() const {
	std::vector<Node*> result;
	LevelOrderTraversal(_Root, result); 
	return result;
}

std::vector<Node*> BinaryTree::LevelOrderTraversal(Node* node) {
	std::vector<Node*> result;
	LevelOrderTraversal(node, result);
	return result;
}

void BinaryTree::RangeSearch(Node* node, int low, int high, std::vector<Node*>& result) {
	if (node == nullptr) return;
	BinaryTree tree(node);

	int minValue = tree.Minimum(node)->_key;
	int maxValue = tree.Maximum(node)->_key;

	if (high < minValue || low > maxValue) return;

	if (node->_key > low) {
		RangeSearch(node->_leftChild, low, high, result);
	}
	if (node->_key >= low && node->_key <= high) {
		result.push_back(node);
	}
	if (node->_key < high) {
		RangeSearch(node->_rightChild, low, high, result);
	}
}

std::vector<Node*> BinaryTree::RangeSearch(int low, int high) const {
	std::vector<Node*> result;
	RangeSearch(_Root, low, high, result);
	return result;
}

std::vector<Node*> BinaryTree::RangeSearch(Node* node, int low, int high) {
	std::vector<Node*> result;
	RangeSearch(node, low, high, result);
	return result;
}

std::string BinaryTree::toString(const std::vector<Node*>& nodes) const {
	std::stringstream ss;

	for (size_t i = 0; i < nodes.size(); ++i) {
		ss << nodes[i]->_key;
		if (i < nodes.size() - 1) {
			ss << ", ";
		}
	}

	return ss.str();
}

std::string BinaryTree::toString(std::vector<Node*>& nodes) {
	std::stringstream ss;

	for (size_t i = 0; i < nodes.size(); ++i) {
		ss << nodes[i]->_key;
		if (i < nodes.size() - 1) {
			ss << ", ";
		}
	}

	return ss.str();
}

std::string BinaryTree::toStringInorder() const {
	std::vector<Node*> nodes = InorderTraversal();
	return toString(nodes);
}

std::string BinaryTree::toStringPreorder() const {
	std::vector<Node*> nodes = PreorderTraversal();
	return toString(nodes);
}

std::string BinaryTree::toStringPostorder() const {
	std::vector<Node*> nodes = PostorderTraversal();
	return toString(nodes);
}

std::string BinaryTree::toStringLevelOrder() const {
	std::vector<Node*> nodes = LevelOrderTraversal();
	return toString(nodes);
}

std::string BinaryTree::toStringRange(int low, int high) const {
	std::vector<Node*> nodes = RangeSearch(low, high);
	return toString(nodes);
}

Node* BinaryTree::buildBalancedTree(std::vector<Node*>& nodes, int start, int end) {
	if (start > end) {
		return nullptr;
	}

	int mid = (start + end) / 2;
	Node* node = nodes[mid];

	node->_leftChild = buildBalancedTree(nodes, start, mid - 1);
	node->_rightChild = buildBalancedTree(nodes, mid + 1, end);

	if (node->_leftChild) node->_leftChild->_parent = node;
	if (node->_rightChild) node->_rightChild->_parent = node;

	return node;
}

void BinaryTree::balance() {
	std::vector<Node*> nodes;
	InorderTraversal(_Root, nodes);
	_Root = buildBalancedTree(nodes, 0, static_cast<int>(nodes.size()) - 1);
}

void BinaryTree::visualize(Node* node, std::string prefix, bool isLeft) const {
	if (node != nullptr) {
		std::cout << prefix;

		std::cout << (isLeft ? "|-- " : "\\-- ");
		std::cout << node->_key << std::endl;

		visualize(node->_leftChild, prefix + (isLeft ? "|   " : "    "), true);
		visualize(node->_rightChild, prefix + (isLeft ? "|   " : "    "), false);
	}
}

void BinaryTree::visualize() const {
	visualize(_Root, "", false);
}

int BinaryTree::getNodeCount(Node* node) {
	if (node == nullptr)
		return 0;
	return 1 + getNodeCount(node->_leftChild) + getNodeCount(node->_rightChild);
}

int BinaryTree::getDepth(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	int leftDepth = getDepth(node->_leftChild);
	int rightDepth = getDepth(node->_rightChild);
	return 1 + std::max(leftDepth, rightDepth);
}

int BinaryTree::getDepth() const {
	return getDepth(_Root);
}

bool BinaryTree::isPerfect() const
{
	return isPerfect(_Root, _nodes);
}

bool BinaryTree::isPerfect(Node* node, size_t nodes)
{
	if (node == nullptr)
		return true;
	else if (isLeaf(node))
		return true;
	else
		return nodes == (pow(2, (getDepth(node)))) - 1;
	return false;
}

bool BinaryTree::isPerfect(Node* node)
{
	if (node == nullptr)
		return true;
	else if (isLeaf(node))
		return true;
	else {
		size_t nodes = getNodeCount(node);
		return nodes == (pow(2, (getDepth(node)))) - 1;
	}
	return false;
}



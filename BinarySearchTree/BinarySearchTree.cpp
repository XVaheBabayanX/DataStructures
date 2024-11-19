#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : _Root(nullptr), _nodes(0) {
	if (other._Root != nullptr) {
		_Root = new Node(other._Root->_key);
		_nodes++;
		copyTree(_Root, other._Root);
	}
}

BinarySearchTree::BinarySearchTree(const Node* root) : _Root(nullptr), _nodes(0) {
	if (root != nullptr) {
		_Root = new Node(root->_key);
		_nodes++;
		copyTree(_Root, root);
	}
}

BinarySearchTree::~BinarySearchTree() {
	clearTree(_Root);
	_Root = nullptr;
	_nodes = 0;
}

void BinarySearchTree::copyTree(Node* thisNode, const Node* otherNode) {
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

void BinarySearchTree::clearTree(Node* node) {
	if (node == nullptr) return;
	clearTree(node->_leftChild);
	clearTree(node->_rightChild);
	delete node;
	node = nullptr;
}

Node* BinarySearchTree::getRoot(Node* node) {
	if (node->_parent == nullptr) return nullptr;
	Node* Root = node->_parent;
	while (Root->_parent != nullptr)
	{
		Root = Root->_parent;
	}
	return Root;
}

bool BinarySearchTree::Insert(const int Key) {
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

bool BinarySearchTree::Delete(const int Key) {
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


Node* BinarySearchTree::Search(const int Key) const {
	if (isEmpty(_Root)) return nullptr;
	Node* Current = _Root;
	while (Current != nullptr) {
		if (Current->_key == Key) return Current;
		else if (Key < Current->_key) Current = Current->_leftChild;
		else Current = Current->_rightChild;
	}
	return nullptr;
}

int BinarySearchTree::MinimumKey() const {
	if (isEmpty(_Root)) return 0;
	return Minimum(_Root)->_key;
}

int BinarySearchTree::MaximumKey() const {
	if (isEmpty(_Root)) return 0;
	return Maximum(_Root)->_key;
}

Node* BinarySearchTree::Minimum(Node* node) const {
	if (isEmpty(node)) return nullptr;
	Node* Minimum = node;
	while (Minimum->_leftChild != nullptr)
	{
		Minimum = Minimum->_leftChild;
	}
	return Minimum;
}

Node* BinarySearchTree::Maximum(Node* node) const {
	if (isEmpty(node)) return nullptr;
	Node* Maximum = node;
	while (Maximum->_rightChild != nullptr)
	{
		Maximum = Maximum->_rightChild;
	}
	return Maximum;
}

Node* BinarySearchTree::Successor(Node* node) const {
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

Node* BinarySearchTree::Predecessor(Node* node) const {
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

Node* BinarySearchTree::Sibling(Node* node) const {
	if (node == nullptr) return nullptr;
	if (node == node->_parent->_leftChild)
		return node->_parent->_rightChild;
	else
		return node->_parent->_leftChild;
}

void BinarySearchTree::InorderTraversal(Node* node, std::vector<Node*>& result) {
	if (node != nullptr) {
		InorderTraversal(node->_leftChild, result);
		result.push_back(node);
		InorderTraversal(node->_rightChild, result);
	}
}

std::vector<Node*> BinarySearchTree::InorderTraversal() const {
	std::vector<Node*> result;
	InorderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::InorderTraversal(Node* node) {
	std::vector<Node*> result;
	InorderTraversal(node, result);
	return result;
}

void BinarySearchTree::PreorderTraversal(Node* node, std::vector<Node*>& result) {
	if (node != nullptr) {
		result.push_back(node);
		PreorderTraversal(node->_leftChild, result);
		PreorderTraversal(node->_rightChild, result);
	}
}

std::vector<Node*> BinarySearchTree::PreorderTraversal() const {
	std::vector<Node*> result;
	PreorderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::PreorderTraversal(Node* node) {
	std::vector<Node*> result;
	PreorderTraversal(node, result);
	return result;
}

void BinarySearchTree::PostorderTraversal(Node* node, std::vector<Node*>& result) {
	if (node != nullptr) {
		PostorderTraversal(node->_leftChild, result);
		PostorderTraversal(node->_rightChild, result);
		result.push_back(node);
	}
}

std::vector<Node*> BinarySearchTree::PostorderTraversal() const {
	std::vector<Node*> result;
	PostorderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::PostorderTraversal(Node* node) {
	std::vector<Node*> result;
	PostorderTraversal(node, result);
	return result;
}

void BinarySearchTree::LevelOrderTraversal(Node* node, std::vector<Node*>& result) {
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

std::vector<Node*> BinarySearchTree::LevelOrderTraversal() const {
	std::vector<Node*> result;
	LevelOrderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::LevelOrderTraversal(Node* node) {
	std::vector<Node*> result;
	LevelOrderTraversal(node, result);
	return result;
}

void BinarySearchTree::ReverseLevelOrderTraversal(Node* node, std::vector<Node*>& result) {
	if (node == nullptr) return;

	std::queue<Node*> queue;
	std::stack<Node*> stack;
	queue.push(node);

	while (!queue.empty()) {
		Node* currentNode = queue.front();
		queue.pop();
		stack.push(currentNode);

		if (currentNode->_rightChild != nullptr) {
			queue.push(currentNode->_rightChild);
		}
		if (currentNode->_leftChild != nullptr) {
			queue.push(currentNode->_leftChild);
		}
	}

	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}
}

std::vector<Node*> BinarySearchTree::ReverseLevelOrderTraversal() const {
	std::vector<Node*> result;
	ReverseLevelOrderTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::ReverseLevelOrderTraversal(Node* node) {
	std::vector<Node*> result;
	ReverseLevelOrderTraversal(node, result);
	return result;
}

void BinarySearchTree::BoundaryTraversal(Node* node, std::vector<Node*>& result) {
	if (node == nullptr) return;

	if (!isLeaf(node)) result.push_back(node);

	addLeftBoundary(node, result);
	addLeaves(node, result);
	addRightBoundary(node, result);
}

void BinarySearchTree::addLeftBoundary(Node* node, std::vector<Node*>& result) {
	Node* current = node->_leftChild;
	while (current) {
		if (!isLeaf(current)) result.push_back(current);
		current = current->_leftChild ? current->_leftChild : current->_rightChild;
	}
}

void BinarySearchTree::addLeaves(Node* node, std::vector<Node*>& result) {
	if (node == nullptr) return;
	if (isLeaf(node)) result.push_back(node);
	addLeaves(node->_leftChild, result);
	addLeaves(node->_rightChild, result);
}

void BinarySearchTree::addRightBoundary(Node* node, std::vector<Node*>& result) {
	std::stack<Node*> stack;
	Node* current = node->_rightChild;
	while (current) {
		if (!isLeaf(current)) stack.push(current);
		current = current->_rightChild ? current->_rightChild : current->_leftChild;
	}
	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}
}

std::vector<Node*> BinarySearchTree::BoundaryTraversal() const {
	std::vector<Node*> result;
	BoundaryTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::BoundaryTraversal(Node* node) {
	std::vector<Node*> result;
	BoundaryTraversal(node, result);
	return result;
}

void BinarySearchTree::DiagonalTraversal(Node* node, std::vector<Node*>& result) {
	if (node == nullptr) return;

	std::queue<Node*> queue;
	queue.push(node);

	while (!queue.empty()) {
		Node* current = queue.front();
		queue.pop();

		while (current) {
			result.push_back(current);
			if (current->_leftChild) {
				queue.push(current->_leftChild);
			}
			current = current->_rightChild;
		}
	}
}

std::vector<Node*> BinarySearchTree::DiagonalTraversal() const {
	std::vector<Node*> result;
	DiagonalTraversal(_Root, result);
	return result;
}

std::vector<Node*> BinarySearchTree::DiagonalTraversal(Node* node) {
	std::vector<Node*> result;
	DiagonalTraversal(node, result);
	return result;
}

void BinarySearchTree::RangeSearch(Node* node, int low, int high, std::vector<Node*>& result) {
	if (node == nullptr) return;
	BinarySearchTree tree(node);

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

std::vector<Node*> BinarySearchTree::RangeSearch(int low, int high) const {
	std::vector<Node*> result;
	RangeSearch(_Root, low, high, result);
	return result;
}

std::vector<Node*> BinarySearchTree::RangeSearch(Node* node, int low, int high) {
	std::vector<Node*> result;
	RangeSearch(node, low, high, result);
	return result;
}

std::string BinarySearchTree::toString(const std::vector<Node*>& nodes) const {
	std::stringstream ss;

	for (size_t i = 0; i < nodes.size(); ++i) {
		ss << nodes[i]->_key;
		if (i < nodes.size() - 1) {
			ss << ", ";
		}
	}

	return ss.str();
}

std::string BinarySearchTree::toString(std::vector<Node*>& nodes) {
	std::stringstream ss;

	for (size_t i = 0; i < nodes.size(); ++i) {
		ss << nodes[i]->_key;
		if (i < nodes.size() - 1) {
			ss << ", ";
		}
	}

	return ss.str();
}

std::string BinarySearchTree::toStringInorder() const {
	std::vector<Node*> nodes = InorderTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringPreorder() const {
	std::vector<Node*> nodes = PreorderTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringPostorder() const {
	std::vector<Node*> nodes = PostorderTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringLevelOrder() const {
	std::vector<Node*> nodes = LevelOrderTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringReverseLevelOrder() const {
	std::vector<Node*> nodes = ReverseLevelOrderTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringBoundary() const {
	std::vector<Node*> nodes = BoundaryTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringDiagonal() const {
	std::vector<Node*> nodes = DiagonalTraversal();
	return toString(nodes);
}

std::string BinarySearchTree::toStringRange(int low, int high) const {
	std::vector<Node*> nodes = RangeSearch(low, high);
	return toString(nodes);
}

Node* BinarySearchTree::buildBalancedTree(std::vector<Node*>& nodes, int start, int end) {
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

void BinarySearchTree::balance() {
	std::vector<Node*> nodes;
	InorderTraversal(_Root, nodes);
	_Root = buildBalancedTree(nodes, 0, static_cast<int>(nodes.size()) - 1);
}

void BinarySearchTree::visualize(Node* node, std::string prefix, bool isLeft) const {
	if (node != nullptr) {
		std::cout << prefix;

		std::cout << (isLeft ? "|-- " : "\\-- ");
		std::cout << node->_key << std::endl;

		visualize(node->_leftChild, prefix + (isLeft ? "|   " : "    "), true);
		visualize(node->_rightChild, prefix + (isLeft ? "|   " : "    "), false);
	}
}

void BinarySearchTree::visualize() const {
	visualize(_Root, "", false);
}

int BinarySearchTree::getNodeCount(Node* node) {
	if (node == nullptr)
		return 0;
	return 1 + getNodeCount(node->_leftChild) + getNodeCount(node->_rightChild);
}

int BinarySearchTree::getDepth(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	int leftDepth = getDepth(node->_leftChild);
	int rightDepth = getDepth(node->_rightChild);
	return 1 + std::max(leftDepth, rightDepth);
}

int BinarySearchTree::getDepth() const {
	return getDepth(_Root);
}

bool BinarySearchTree::isFull() const {
	return isFull(_Root);
}

bool BinarySearchTree::isFull(Node* node) {
	if (node == nullptr)
		return true;
	if (isLeaf(node))
		return true;
	if ((node->_leftChild != nullptr) && (node->_rightChild != nullptr))
		return isFull(node->_leftChild) && isFull(node->_rightChild);

	return false;
}

bool BinarySearchTree::isPerfect() const {
	return isPerfect(_Root, getDepth(_Root), 0);
}

bool BinarySearchTree::isPerfect(Node* node, int depth, int level) {
	if (node == nullptr)
		return true;
	if (isLeaf(node))
		return (level == depth - 1);
	if (node->_leftChild == nullptr || node->_rightChild == nullptr)
		return false;
	return isPerfect(node->_leftChild, depth, level + 1) && isPerfect(node->_rightChild, depth, level + 1);
}

bool BinarySearchTree::isBalanced() const {
	return isBalanced(_Root) != -1;
}

int BinarySearchTree::isBalanced(Node* node) {
	if (node == nullptr)
		return 0;

	int leftHeight = isBalanced(node->_leftChild);
	if (leftHeight == -1) return -1;

	int rightHeight = isBalanced(node->_rightChild);
	if (rightHeight == -1) return -1;
	if (abs(leftHeight - rightHeight) > 1)
		return -1;
	return std::max(leftHeight, rightHeight) + 1;
}

bool BinarySearchTree::isDegenerate() const {
	return isDegenerate(_Root);
}

bool BinarySearchTree::isDegenerate(Node* node) {
	if (node == nullptr)
		return true;

	if ((node->_leftChild != nullptr) && (node->_rightChild != nullptr))
		return false;

	return isDegenerate(node->_leftChild) || isDegenerate(node->_rightChild);;
}

bool BinarySearchTree::isComplete() const {
	return isComplete(_Root);
}

bool BinarySearchTree::isComplete(Node* node) {
	if (node == nullptr)
		return true;

	std::queue<Node*> queue;
	queue.push(node);
	bool reachedEnd = false;

	while (!queue.empty()) {
		Node* current = queue.front();
		queue.pop();

		if (current == nullptr) {
			reachedEnd = true;
		}
		else {
			if (reachedEnd) return false;

			queue.push(current->_leftChild);
			queue.push(current->_rightChild);
		}
	}

	return true;
}

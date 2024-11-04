#include "UniqueHashTable.h"

HashTable::HashTable() : HashTable(DEFAULT_TABLE_SIZE) {}

HashTable::HashTable(size_t table_size, HashFunction& hashfunction) : _HashPtr(new HashFunction(hashfunction))
{
	setSize(table_size);
	TableInitialization();
}

HashTable::HashTable(size_t table_size) : HashTable(table_size, DEFAULT_PRIME) {}

HashTable::HashTable(size_t table_size, size_t prime) 
{
	_HashPtr = new HashFunction(prime);
	setSize(table_size);
	TableInitialization();
}

HashTable::~HashTable() {
	for (size_t i = 0; i < TableSize; ++i) {
		delete Table[i];
	}
}

void HashTable::setSize(size_t table_size)
{
	TableSize = (table_size > 0) ? table_size : DEFAULT_TABLE_SIZE;
}

void HashTable::TableInitialization() {
	Table.resize(TableSize);
	for (size_t i = 0; i < TableSize; ++i) {
		Table[i] = new BinaryTree();
	}
}

void HashTable::NewTableInitialization(std::vector<BinaryTree*> &newTable, size_t newSize) {
	newTable.resize(newSize);
	for (size_t i = 0; i < newSize; ++i) {
		newTable[i] = new BinaryTree();
	}
}

bool HashTable::Insert(const std::string& key, const double& value)
{
	size_t index = (_HashPtr->RollingHash(key)) % TableSize;
	if (Table[index]->Insert(key, value)) {
		_elements++;
		return true;
	}
	return false;
}

Node* HashTable::Search(const std::string& key) const
{
	size_t index = (_HashPtr->RollingHash(key)) % TableSize;
	Node* Target = Table[index]->Search(key);
	if (Target) {
		return Target;
	}
	return nullptr;
}

bool HashTable::Delete(const std::string& key)
{
	size_t index = (_HashPtr->RollingHash(key)) % TableSize;
	if (Table[index]->Delete(key))
	{
		_elements--;
		return true;
	}
	return false;
}

bool HashTable::Change(const std::string& key, const double& value) const
{
	size_t index = (_HashPtr->RollingHash(key)) % TableSize;
	if (Table[index]->Change(key, value))
	{
		return true;
	}
	return false;
}

void HashTable::Optimize()
{
	for (BinaryTree* tree : Table)
	{
		if (!(tree->isEmpty()))
		{
			Node* root = tree->getRoot();
			if (!(BinaryTree::isLeaf(root)))
			{
				tree->balance();
			}

		}
	}
}

void HashTable::Visualize()
{
	for (BinaryTree* tree : Table)
	{
		if (!(tree->isEmpty()))
		{
			tree->visualize();
		}
	}
}

double HashTable::getTableLoadFactor() const {
	return static_cast<double>(getElementsCount()) / TableSize * 100;
}

void HashTable::ReHash() {
	std::vector<BinaryTree*> newTable;
	size_t newSize = static_cast<size_t>(TableSize * RESIZE_FACTOR);
	NewTableInitialization(newTable, newSize);
	for (BinaryTree* tree : Table)
	{
		if (!(tree->isEmpty()))
		{
			Node* root = tree->getRoot();
			if (BinaryTree::isLeaf(root))
			{
				size_t index = (_HashPtr->RollingHash(root->_key)) % newSize;
				newTable[index]->Insert(root->_key, root->_data);
			}
			else {
				std::vector<Node*> nodes = tree->InorderTraversal();
				for (Node* node : nodes)
				{
					size_t index = (_HashPtr->RollingHash(node->_key)) % newSize;
					newTable[index]->Insert(node->_key, node->_data);
				}
			}
		}
	}
	for (size_t i = 0; i < TableSize; i++)
	{
		delete Table[i];
	}
	Table = std::move(newTable);
	TableSize = newSize;
}

void HashTable::Print()
{
	for (BinaryTree* tree : Table)
	{
		if (!(tree->isEmpty()))
		{
			Node* root = tree->getRoot();
			if (BinaryTree::isLeaf(root))
			{
				std::cout << root->_key << " : " << root->_data << std::endl;
			}
			else {
				std::vector<Node*> nodes = tree->InorderTraversal();
				for (Node* node : nodes)
				{
					std::cout << node->_key << " : " << node->_data << std::endl;
				}
			}
		}
	}
}
#include "HashSet.h"

HashSet::HashSet() : HashSet(DEFAULT_TABLE_SIZE) {}

HashSet::HashSet(size_t table_size, HashFunction& hashfunction) : _HashPtr(new HashFunction(hashfunction)), Table(new BinaryTree())
{
	setSize(table_size);
	TableInitialization();
}

HashSet::HashSet(size_t table_size) : HashSet(table_size, DEFAULT_PRIME) {}

HashSet::HashSet(size_t table_size, size_t prime) : Table(new BinaryTree())
{
	_HashPtr = new HashFunction(prime);
	setSize(table_size);
	TableInitialization();
}

HashSet::~HashSet() {
	delete Table;
}

void HashSet::setSize(size_t table_size)
{
	TableSize = (table_size > 0) ? table_size : DEFAULT_TABLE_SIZE;
}

void HashSet::TableInitialization() {
	std::vector<size_t> buckets;
	for (size_t i = 0; i < TableSize; i++) {
		buckets.push_back(i);
	}
	Table->setRoot(Table->buildBalancedTree(buckets, 0, static_cast<int>(TableSize - 1)));
}

void HashSet::TableInitialization(BinaryTree* newTable, size_t newSize) {
	std::vector<size_t> buckets;
	for (size_t i = 0; i < newSize; i++) {
		buckets.push_back(i);
	}
	newTable->setRoot(newTable->buildBalancedTree(buckets, 0, static_cast<int>(newSize - 1)));
}

bool HashSet::Insert(const std::string& key, const double& value)
{
	size_t bucket = _HashPtr->RollingHash(key, TableSize);
	if (!(Table->Search(bucket)->isDefault())) return false;
	if (Table->Change(bucket, key, value))
	{
		_elements++;
		return true;
	}
	return false;
}

Node* HashSet::Search(const std::string& key) const
{
	size_t bucket = _HashPtr->RollingHash(key, TableSize);
	if(Table->Search(bucket)->_key == key) 
		return Table->Search(bucket);
	return nullptr;
}

bool HashSet::Delete(const std::string& key)
{
	size_t bucket = _HashPtr->RollingHash(key, TableSize);
	if (Table->Search(bucket))
	{
		(Table->Search(bucket))->_key = DefaultKey;
		(Table->Search(bucket))->_data = DefaultData;
		_elements--;
		return true;
	}
	return false;
}

bool HashSet::Change(const std::string& key, const double& value)
{
	size_t bucket = _HashPtr->RollingHash(key, TableSize);
	if (Table->Change(bucket, key, value)) return true;
	return false;
}

double HashSet::getTableLoadFactor() const {
	return static_cast<double>(getElementsCount()) / TableSize * 100;
}

void HashSet::ReHash() {
	size_t newSize = static_cast<size_t>(TableSize * RESIZE_FACTOR);
	BinaryTree* newTable = new BinaryTree;
	TableInitialization(newTable, newSize);

	std::vector<Node*> buckets = Table->InorderTraversal();
	for (Node* current : buckets) {  
		if (current && !current->isDefault()) {
			size_t newBucket = _HashPtr->RollingHash(current->_key, newSize);
			newTable->Change(newBucket, current->_key, current->_data);
		}
	}

	delete Table;  
	Table = newTable;  
	TableSize = newSize;  
}


void HashSet::Print()
{
	std::vector<Node*> buckets = Table->InorderTraversal();
	for (size_t i = 0; i < TableSize; i++)
	{
		std::cout << buckets[i]->_key << " : " << buckets[i]->_data << std::endl;
	}
}
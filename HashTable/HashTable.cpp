#include "HashTable.h"

HashTable::HashTable() : HashTable(DEFAULT_TABLE_SIZE) {}

HashTable::HashTable(size_t table_size, HashFunction &hashfunction) : _HashPtr(new HashFunction(hashfunction))
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

size_t HashTable::getSize() const
{
	return TableSize;
}

size_t HashTable::getElementsCount() const
{
	return _elements;
}

void HashTable::TableInitialization() {
	Table.resize(TableSize); 
	for (size_t i = 0; i < TableSize; ++i) {
		Table[i] = new List();
	}
}

void HashTable::InsertAtListFront(const std::string& key, const double& value)
{
	size_t index = _HashPtr->Function(key, TableSize);
	Table[index]->insertAtFront(key, value);
	_elements++;
}

void HashTable::InsertAtListBack(const std::string& key, const double& value) 
{
	size_t index = _HashPtr->Function(key, TableSize);
	Table[index]->insertAtBack(key, value);
	_elements++;
}

ListNode* HashTable::Search(const std::string& key) const
{
	size_t index = _HashPtr->Function(key, TableSize);

	ListNode* currentPtr = Table[index]->getFirstPtr();
	while (currentPtr != nullptr) {
		if (currentPtr->_key == key) {
			return currentPtr; 
		}
		currentPtr = currentPtr->_nextPtr;
	}

	return nullptr; 
}

void HashTable::Delete(const std::string& key) {
	size_t index = _HashPtr->Function(key, TableSize);
	double tempValue; 
	ListNode* currentPtr = Table[index]->getFirstPtr();

	size_t position = 0;
	while (currentPtr != nullptr) {
		if (currentPtr->_key == key) {
			Table[index]->removeAtIndex(position, tempValue); 
			_elements--;
			return;
		}
		currentPtr = currentPtr->_nextPtr;
		position++;
	}

	std::cout << "Key not found in the hash table." << std::endl;
}

double HashTable::getTableLoadFactorByLists() const {
	size_t occupiedBuckets = 0;
	for (const auto& list : Table) {
		if (!list->isEmpty()) {  
			occupiedBuckets++;
		}
	}
	return static_cast<double>(occupiedBuckets) / TableSize * 100;  
}

double HashTable::getTableLoadFactor() const {
	return static_cast<double>(getElementsCount()) / TableSize * 100;
}

void HashTable::rehashIfNeeded() {
	double loadFactor = getTableLoadFactor();

	if (loadFactor >= LOAD_FACTOR) {
		size_t newSize = static_cast<size_t>(TableSize * RESIZE_FACTOR);
		std::vector<List*> newTable(newSize);  

		for (size_t i = 0; i < newSize; ++i) {
			newTable[i] = new List();  
		}

		for (size_t i = 0; i < TableSize; ++i) {
			ListNode* currentPtr = Table[i]->getFirstPtr();
			while (currentPtr != nullptr) {
				size_t newIndex = _HashPtr->Function(currentPtr->_key, newSize);  
				newTable[newIndex]->insertAtBack(currentPtr->_key, currentPtr->_data);  
				currentPtr = currentPtr->_nextPtr;
			}
			delete Table[i];  
		}

		Table = std::move(newTable);  
		TableSize = newSize;  
	}
}

#pragma once

#include "SLL.h"
#include "HashFunction.h"
#include <vector>

const size_t MINIMAL_TABLE_SIZE = 1;
const size_t DEFAULT_TABLE_SIZE = 10;
const double RESIZE_FACTOR = 1.5;
const double LOAD_FACTOR = 70.0;

class HashTable
{
public:
	HashTable();
	HashTable(size_t table_size, HashFunction &);
	HashTable(size_t table_size);
	HashTable(size_t table_size, size_t prime);
	~HashTable();
	void InsertAtListFront(const std::string& key, const double& value);
	void InsertAtListBack(const std::string& key, const double& value);
	ListNode* Search(const std::string& key) const;
	void Delete(const std::string& key);
	double getTableLoadFactor() const;
	double getTableLoadFactorByLists() const;
	void rehashIfNeeded();
	size_t getSize() const;
	size_t getElementsCount() const;
private:
	void setSize(size_t table_size);
	void TableInitialization();
	size_t TableSize;
	size_t _elements = 0;
	HashFunction* _HashPtr;
	std::vector<List*> Table;
};
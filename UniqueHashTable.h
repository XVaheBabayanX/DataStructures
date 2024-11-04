#pragma once

#include "HashFunction.h"
#include "BinaryTree.h"
#include <vector>

const size_t MINIMAL_TABLE_SIZE = 1;
const size_t DEFAULT_TABLE_SIZE = 16;
const double RESIZE_FACTOR = 2;
const double LOAD_FACTOR = 70.0;

class HashTable
{
public:
	HashTable();
	HashTable(size_t table_size, HashFunction&);
	HashTable(size_t table_size);
	HashTable(size_t table_size, size_t prime);
	~HashTable();
	bool Insert(const std::string& key, const double& value);
	Node* Search(const std::string& key) const;
	bool Delete(const std::string& key);
	bool Change(const std::string& key, const double& value) const;
	void Optimize();
	void Visualize();
	double getTableLoadFactor() const;
	void ReHash();
	void Print();
	size_t getSize() const { return TableSize; }
	size_t getElementsCount() const { return _elements; }
private:
	void setSize(size_t table_size);
	void TableInitialization();
	void NewTableInitialization(std::vector<BinaryTree*>&, size_t);
	size_t TableSize;
	size_t _elements = 0;
	HashFunction* _HashPtr;
	std::vector<BinaryTree*> Table;
};
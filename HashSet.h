#pragma once

#include "HashFunction.h"
#include "BinaryTree.h"
#include <vector>

const size_t MINIMAL_TABLE_SIZE = 1;
const size_t DEFAULT_TABLE_SIZE = 16;
const double RESIZE_FACTOR = 2;
const double LOAD_FACTOR = 75.0;

class HashSet {
public:
	HashSet();
	HashSet(size_t table_size, HashFunction&);
	HashSet(size_t table_size);
	HashSet(size_t table_size, size_t prime);
	~HashSet();
	bool Insert(const std::string& key, const double& value);
	Node* Search(const std::string& key) const;
	bool Delete(const std::string& key);
	bool Change(const std::string& key, const double& value);
	double getTableLoadFactor() const;
	void ReHash();
	void TableVisualisation() { Table->visualize(); }
	void Print();
	size_t getSize() const { return TableSize; }
	size_t getElementsCount() const { return _elements; }
private:
	void setSize(size_t table_size);
	void TableInitialization();
	static void TableInitialization(BinaryTree*, size_t);
	size_t TableSize;
	size_t _elements = 0;
	HashFunction* _HashPtr;
	BinaryTree* Table;
	const std::string DefaultKey = "";
	const double DefaultData = 0;
};

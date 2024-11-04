#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

#pragma once

#include "HashFunction.h"
#include "BinaryTree.h"

const size_t MINIMAL_TABLE_SIZE = 1;
const size_t DEFAULT_TABLE_SIZE = 16;
const double RESIZE_FACTOR = 2;
const double LOAD_FACTOR = 75.0;

class HashSet {
public:
    HashSet();
    HashSet(HashFunction&);
    HashSet(size_t prime);
    ~HashSet();
    bool Insert(const std::string& key);
    Node* Search(const std::string& key) const;
    bool Delete(const std::string& key);
    bool isBalanced() { return Table->isBalanced(); }
    void Balance() { Table->balance(); }
    void TableVisualisation() { Table->visualize(); }
    void Print();
    size_t getElementsCount() const { return _elements; }

private:
    size_t _elements = 0;
    HashFunction* _HashPtr;
    BinaryTree* Table;
    const std::string DefaultKey = "";
    const double DefaultData = 0;
};

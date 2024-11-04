#include "HashSet.h"

HashSet::HashSet() : HashSet(DEFAULT_TABLE_SIZE) {}

HashSet::HashSet(HashFunction& hashfunction) : _HashPtr(new HashFunction(hashfunction)), Table(new BinaryTree()) {}

HashSet::HashSet(size_t prime) : Table(new BinaryTree()) {
    _HashPtr = new HashFunction(prime);
}

HashSet::~HashSet() {
    delete Table;
    delete _HashPtr;  
}

bool HashSet::Insert(const std::string& key) {
    std::string bucketIndex = _HashPtr->RollingHash(key);

    while (true) {
        if (Table->Insert(bucketIndex, key)) {
            _elements++;
            return true;
        }
        std::cout << bucketIndex << "\n";
        bucketIndex = _HashPtr->FNV1a(bucketIndex);
    }

    return false;
}

Node* HashSet::Search(const std::string& key) const {
    std::string bucketIndex = _HashPtr->RollingHash(key);
    size_t attempts = 0;
    while (attempts < _elements) {
        Node* node = Table->Search(bucketIndex);
        if (node && node->_key == key) {
            return node;
        }
        bucketIndex = _HashPtr->FNV1a(bucketIndex);
        attempts++;
    }

    return nullptr; 
}

bool HashSet::Delete(const std::string& key) {
    if (Table->Delete(key)) {
        _elements--;
        return true;
    }
    return false;
}

void HashSet::Print() {
    std::vector<Node*> buckets = Table->InorderTraversal();
    for (size_t i = 0; i < buckets.size(); i++) {
        if (i < buckets.size() && buckets[i]) {
            std::cout << buckets[i]->_key << std::endl;
        }
    }
}

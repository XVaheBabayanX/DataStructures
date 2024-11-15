#pragma once

#include <iostream>
#include <cstdlib> 
#include <cmath>   

const size_t DEFAULT_PRIME = 997;

class HashFunction
{
public:
	HashFunction();
	HashFunction(const HashFunction &);
	HashFunction(size_t prime);
	void setPrime(size_t prime);
	size_t Function(const std::string& key, size_t tableSize) const;
	static size_t generateRandomPrime(size_t min, size_t max);
	static bool isPrime(size_t num);
private:
	size_t Prime;
};

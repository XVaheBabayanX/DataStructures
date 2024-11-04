#pragma once

#include <iostream>
#include <cmath>   

const size_t DEFAULT_PRIME = 1000000007;

class HashFunction
{
public:
	HashFunction();
	HashFunction(const HashFunction&);
	HashFunction(size_t prime);
	void setPrime(size_t prime);
	size_t RollingHash(const std::string& key) const;
	size_t CityHash(const std::string& key) const;
	size_t FNV1a(const std::string& key) const;
	size_t MurmurHash(const std::string& key) const;
	static size_t generateRandomPrime(size_t min, size_t max);
	static bool isPrime(size_t num);
private:
	size_t Prime;
};

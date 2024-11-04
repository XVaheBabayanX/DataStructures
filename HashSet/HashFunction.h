#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>   

const size_t DEFAULT_PRIME = 1000000007;

class HashFunction
{
public:
	HashFunction();
	HashFunction(const HashFunction&);
	HashFunction(size_t prime);
	void setPrime(size_t prime);
	std::string RollingHash(const std::string& key) const;
	std::string CityHash(const std::string& key) const;
	std::string FNV1a(const std::string& key) const;
	std::string MurmurHash(const std::string& key) const;
	static size_t generateRandomPrime(size_t min, size_t max);
	static bool isPrime(size_t num);
private:
	size_t Prime;
	size_t hashLength = 8;
};

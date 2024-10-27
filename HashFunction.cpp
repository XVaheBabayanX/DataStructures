#include "HashFunction.h"

HashFunction::HashFunction() : HashFunction(DEFAULT_PRIME) {}

HashFunction::HashFunction(const HashFunction &OtherFunction) : Prime(OtherFunction.Prime) {}

HashFunction::HashFunction(size_t prime)
{
    setPrime(prime);
}

void HashFunction::setPrime(size_t prime)
{
    Prime = (isPrime(prime)) ? prime : DEFAULT_PRIME;
}

size_t HashFunction::Function(const std::string& key, size_t tableSize) const
{
    size_t hash = 0;

    for (char c : key) {
        hash = (hash * Prime + c) % tableSize;
    }

    return hash;
}

bool HashFunction::isPrime(size_t num)
{
    if (num < 2) return false;
    for (size_t i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

size_t HashFunction::generateRandomPrime(size_t min, size_t max)
{
    if (min > max) {
        std::swap(min, max);
    }
    size_t prime;
    do {
        prime = min + rand() % (max - min + 1);
    } while (!isPrime(prime)); 

    return prime;
}
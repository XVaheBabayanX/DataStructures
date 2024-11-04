#include "HashFunction.h"

HashFunction::HashFunction() : HashFunction(DEFAULT_PRIME) {}

HashFunction::HashFunction(const HashFunction& OtherFunction) : Prime(OtherFunction.Prime) {}

HashFunction::HashFunction(size_t prime)
{
    setPrime(prime);
}

void HashFunction::setPrime(size_t prime)
{
    Prime = (isPrime(prime)) ? prime : DEFAULT_PRIME;
}

std::string HashFunction::RollingHash(const std::string& key) const
{
    size_t hash = 0;

    for (char c : key) {
        hash = (hash * Prime + c);
    }

    std::ostringstream oss;
    oss << std::hex << std::setw(hashLength) << std::setfill('0') << hash;
    std::string hashString = oss.str();
    return hashString.substr(0, hashLength);
}

std::string HashFunction::CityHash(const std::string& key) const
{
    size_t hash = 0;
    size_t prime1 = 0x9e3779b1;
    size_t prime2 = 0x85ebca6b;

    for (char c : key) {
        hash ^= static_cast<size_t>(c);
        hash = (hash * prime1) ^ ((hash >> 27) * prime2);
    }

    std::ostringstream oss;
    oss << std::hex << std::setw(hashLength) << std::setfill('0') << hash;

    std::string hashString = oss.str();
    return hashString.substr(0, hashLength); 
}


std::string HashFunction::FNV1a(const std::string& key) const
{
    const size_t fnvPrime = 16777619;
    size_t hash = 2166136261;

    for (char c : key) {
        hash ^= static_cast<size_t>(c);
        hash *= fnvPrime;
    }

    std::ostringstream oss;
    oss << std::hex << std::setw(hashLength) << std::setfill('0') << hash;

    std::string hashString = oss.str();
    return hashString.substr(0, hashLength);  
}


std::string HashFunction::MurmurHash(const std::string& key) const
{
    const size_t seed = 0x9747b28c;
    size_t hash = seed;

    const size_t c1 = 0xcc9e2d51;
    const size_t c2 = 0x1b873593;

    for (char c : key) {
        size_t k = static_cast<size_t>(c);
        k *= c1;
        k = (k << 15) | (k >> (32 - 15)); 
        k *= c2;

        hash ^= k;
        hash = (hash << 13) | (hash >> (32 - 13));  
        hash = hash * 5 + 0xe6546b64;
    }

    hash ^= key.length();
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    std::ostringstream oss;
    oss << std::hex << std::setw(8) << std::setfill('0') << hash;

    std::string hashString = oss.str();
    return hashString.substr(0, hashLength);
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

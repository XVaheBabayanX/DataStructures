#include "Hashset.h"
#include "HashFunction.h"
#include <iostream>
#include <string>

using namespace std;

bool isDouble(const std::string& str) {
    if (str.empty()) return false;

    size_t startIndex = 0;
    bool decimalPointFound = false;

    if (str[0] == '-') {
        if (str.length() == 1) return false;
        startIndex = 1;
    }

    for (size_t i = startIndex; i < str.length(); i++) {
        if (str[i] == '.') {
            if (decimalPointFound || i == startIndex || i == str.length() - 1) {
                return false;
            }
            decimalPointFound = true;
        }
        else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void instructions() {
    cout << "Enter one of the following options:\n"
        << " 1 to insert\n"
        << " 2 to change\n"
        << " 3 to delete\n"
        << " 4 to search\n"
        << " 5 to visualize\n"
        << " 6 to print\n"
        << " 7 to get elements count\n"
        << " 8 to check load factor and potentially resize the table\n"
        << " 9 to end\n";
}

const size_t CHOICE = 9;

int main() {
    size_t tableSize;
    size_t prime;
    std::string input;

    cout << "Enter hash table size : ";
    cin >> input;

    while (!isNumber(input) || (tableSize = std::stoul(input)) < MINIMAL_TABLE_SIZE) {
        cout << "Table size must be at least " << MINIMAL_TABLE_SIZE << ". Please enter a valid size : ";
        cin >> input;
    }

    cout << "Enter prime number for hash function : ";
    cin >> input;

    while (!isNumber(input) || !HashFunction::isPrime(prime = std::stoul(input))) {
        cout << "The number is not prime. Please enter a prime number : ";
        cin >> input;
    }

    HashFunction hashFunc(prime);
    HashSet hashSet(tableSize, hashFunc);

    int choice;
    string key, newkey;
    double value;

    instructions();
    cout << "What do you want to do? ";

    while (true) {
        cin >> input;
        if (isNumber(input)) {
            choice = std::stoi(input);
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and " << CHOICE << " : ";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter key: ";
            cin >> key;
            while (key.empty()) {
                cout << "Key cannot be empty. Please enter a valid key : ";
                cin >> key;
            }
            if (hashSet.Search(key))
            {
                cout << "Key " << key << " already exists.\n";
                cout << "Would you like to change it? (y/n): ";
                cin >> input;
                if (input == "y" || input == "Y")
                {
                    cout << "Enter value to change : ";
                    cin >> input;
                    while (!isDouble(input)) {
                        cout << "Value must be a number. Please enter a valid value : ";
                        cin >> input;
                    }
                    value = std::stod(input);
                    if (hashSet.Change(key, value)) {
                        cout << "Key " << key << " value successfully changed.\n";
                    }
                    else cout << "Failed to change key value" << key << ".\n";
                }
                break;
            }
            cout << "Enter value : ";
            cin >> input;
            while (!isDouble(input)) {
                cout << "Value must be a number. Please enter a valid value : ";
                cin >> input;
            }
            value = std::stod(input);
            if (hashSet.Insert(key, value)) {
                cout << "Key " << key << " successfully inserted.\n";
            }
            else cout << "Failed to insert key " << key << ".\n";
            break;
        case 2:
            cout << "Enter the key that needs to be changed : ";
            cin >> key;
            while (key.empty() || !(hashSet.Search(key))) {
                cout << "Key cannot be empty or non-existent. Please enter a valid key : ";
                cin >> key;
            }
            cout << "Enter value to change : ";
            cin >> input;
            while (!isDouble(input)) {
                cout << "Value must be a number. Please enter a valid value : ";
                cin >> input;
            }
            value = std::stod(input);
            if (hashSet.Change(key, value)) {
                cout << "Key " << key << " value successfully changed.\n";
            }
            else cout << "Failed to change key value" << key << ".\n";
            break;
        case 3:
            cout << "Enter key to delete : ";
            cin >> key;
            while (key.empty()) {
                cout << "Key cannot be empty. Please enter a valid key : ";
                cin >> key;
            }
            if (hashSet.Delete(key)) {
                cout << "Key " << key << " successfully deleted.\n";
            }
            else {
                cout << "Key " << key << " not found.\n";
            }
            break;
        case 4:
            cout << "Enter key to search : ";
            cin >> key;
            while (key.empty()) {
                cout << "Key cannot be empty. Please enter a valid key : ";
                cin >> key;
            }
            if (Node* foundNode = hashSet.Search(key)) {
                cout << "Found key: " << key << " with value : " << foundNode->_data << endl;
            }
            else {
                cout << "Key not found.\n";
            }
            break;
        case 5:
             cout << "Table visualization:\n";
             hashSet.TableVisualisation();
            break;
        case 6:
            cout << "Table:\n";
            hashSet.Print();
            break;
        case 7:
            if (hashSet.getElementsCount() == 0) cout << "HashTable is empty.\n";
            else cout << "Hash Table have " << hashSet.getElementsCount() << " elements\n";
            break;
        case 8:
            cout << "The Load Factor : " << hashSet.getTableLoadFactor() << "%" << endl;
            if (hashSet.getTableLoadFactor() >= LOAD_FACTOR)
            {
                cout << "Load factor exceeds " << LOAD_FACTOR <<". Would you like to resize the hash table? (y/n): ";
                cin >> input;
                if (input == "y" || input == "Y")
                {
                    hashSet.ReHash();
                    cout << "The hash table has been resized to " << hashSet.getSize() << "\n";
                }
            }
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
        if (hashSet.getTableLoadFactor() == 100.0)
        {
            cout << "Load factor exceeds " << LOAD_FACTOR << ". Would you like to resize the hash table or exit? (resize/r/1 or exit/e/2): ";
            cin >> input;
            if (input == "1" || input == "r" || input == "resize")
            {
                hashSet.ReHash();
                cout << "The hash table has been resized to " << hashSet.getSize() << "\n";
            }
            else break;
        }
        cout << "What do you want to do next? ";
    }

    cout << "End of program.\n";
    return 0;
}

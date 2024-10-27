#include "HashTable.h"
#include "HashFunction.h"
#include <iostream>
#include <string>

using namespace std;

bool isInt(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
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
        << " 1 to insert at the front of the list\n"
        << " 2 to insert at the back of the list\n"
        << " 3 to get inserted elements count\n"
        << " 4 to search by key\n"
        << " 5 to delete by key\n"
        << " 6 to check load factor and potentially resize the table\n"
        << " 7 to end\n";
}

const size_t CHOICE = 7;

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
    HashTable hashTable(tableSize, hashFunc);

    int choice;
    string key;
    double value;

    instructions();
    cout << "What do you want to do? ";

    while (true) {
        cin >> input; 
        if (isNumber(input)) {
            choice = std::stoi(input);
            if (choice == CHOICE) break;
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
            cout << "Enter value to insert at front : ";
            cin >> input;
            while (!isNumber(input)) {
                cout << "Value must be a number. Please enter a valid value : ";
                cin >> input;
            }
            value = std::stod(input);  
            hashTable.InsertAtListFront(key, value);
            cout << "Inserted at front.\n";
            break;
        case 2:
            cout << "Enter key : ";
            cin >> key;
            while (key.empty()) {
                cout << "Key cannot be empty. Please enter a valid key: ";
                cin >> key;
            }
            cout << "Enter value to insert at back : ";
            cin >> input;
            while (!isNumber(input)) {
                cout << "Value must be a number. Please enter a valid value: ";
                cin >> input;
            }
            value = std::stod(input);  
            hashTable.InsertAtListBack(key, value);
            cout << "Inserted at back.\n";
            break;
        case 3:
            if (hashTable.getElementsCount() == 0) cout << "HashTable is empty.\n";
            else cout << "Hash Table have " << hashTable.getElementsCount() << " elements\n";
            break;
        case 4:
            cout << "Enter key to search : ";
            cin >> key;
            if (ListNode* foundNode = hashTable.Search(key)) {
                cout << "Found key: " << key << " with value : " << foundNode->_data << endl;
            }
            else {
                cout << "Key not found.\n";
            }
            break;
        case 5:
            cout << "Enter key to delete : ";
            cin >> key;
            hashTable.Delete(key);
            cout << "Attempted to delete key : " << key << endl;
            break;
        case 6:
            cout << "The Load Factor : " << hashTable.getTableLoadFactor() << endl;
            if (hashTable.getTableLoadFactor() >= LOAD_FACTOR)
            {
                cout << "Load factor exceeds 70%. Would you like to resize the hash table? (y/n): ";
                cin >> input;
                if (input == "y" || input == "Y") 
                {
                    hashTable.rehashIfNeeded();
                    cout << "The hash table has been resized to " << hashTable.getSize() << "\n";
                }
            }
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }

        cout << "What do you want to do next? ";
    }

    cout << "End of program.\n";
    return 0;
}

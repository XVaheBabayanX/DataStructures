#include "Hashset.h"
#include "HashFunction.h"
#include <string>

using namespace std;

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
        << " 2 to delete\n"
        << " 3 to search\n"
        << " 4 to visualize\n"
        << " 5 to print\n"
        << " 6 to get elements count\n"
        << " 7 to balance\n"
        << " 8 to end\n";
}

const size_t CHOICE = 8;

int main() {
    size_t prime;
    std::string input;

    cout << "Enter prime number for hash function : ";
    cin >> input;

    while (!isNumber(input) || !HashFunction::isPrime(prime = std::stoul(input))) {
        cout << "The number is not prime. Please enter a prime number : ";
        cin >> input;
    }

    HashFunction hashFunc(prime);
    HashSet hashSet(hashFunc);

    int choice;
    string key, newkey;

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
                break;
            }
            if (hashSet.Insert(key)) {
                cout << "Key " << key << " successfully inserted.\n";
            }
            else cout << "Failed to insert key " << key << ".\n";
            break;
        case 2:
            if (hashSet.getElementsCount() == 0)
            {
                cout << "The HashSet is empty, cannot delete in it.\n";
            }
            else
            {
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
            }
            break;
        case 3:
            if (hashSet.getElementsCount() == 0)
            {
                cout << "The HashSet is empty, cannot search in it.\n";
            }
            else
            {
                cout << "Enter key to search : ";
                cin >> key;
                while (key.empty()) {
                    cout << "Key cannot be empty. Please enter a valid key : ";
                    cin >> key;
                }
                if (Node* foundNode = hashSet.Search(key)) {
                    cout << "Found key: " << key << endl;
                }
                else {
                    cout << "Key not found.\n";
                }
            }
            break;
        case 4:
            if (hashSet.getElementsCount() == 0)
            {
                cout << "The HashSet is empty, cannot visualize it.\n";
            }
            else
            {
                cout << "Table visualization:\n";
                hashSet.TableVisualisation();
            }
            break;
        case 5:
            if (hashSet.getElementsCount() == 0)
            {
                cout << "The HashSet is empty, cannot print it.\n";
            }
            else
            {
                cout << "Table:\n";
                hashSet.Print();
            }
            break;
        case 6:
            if (hashSet.getElementsCount() == 0) cout << "HashSet is empty.\n";
            else cout << "HashSet have " << hashSet.getElementsCount() << " elements\n";
            break;
        case 7:
            if (hashSet.getElementsCount() == 0)
            {
                cout << "The HashSet is empty, cannot balance it.\n";
            }
            else
            {
                if (hashSet.isBalanced())
                {
                    cout << "The HashSet is already balanced.\n";
                }
                else
                {
                    hashSet.Balance();
                    cout << "The HashSet was balanced.\n";
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

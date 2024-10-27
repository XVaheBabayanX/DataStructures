#include "DLL.h"  
#include <iostream>

using namespace std;

void instructions()
{
    cout << "Enter one of the followings:\n"
        << " 1 to insert at the beginning of list\n"
        << " 2 to insert at end of list\n"
        << " 3 to delete from the beginning of list\n"
        << " 4 to delete from end of list\n"
        << " 5 to insert at index\n"
        << " 6 to delete at index\n"
        << " 7 to report the number of elements\n"
        << " 8 to check for cycle presence\n"
        << " 9 to end list processing\n";
}

int main()
{
    DoublyLinkedList myList;  
    int choice;
    double value;
    size_t index;

    instructions();
    cout << "What do you want to do with the list? ";
    cin >> choice;

    while (choice != 9)
    {
        switch (choice)
        {
        case 1:
            cout << "Enter value to insert at front: ";
            cin >> value;
            myList.insertAtFront(value);
            myList.print();
            break;
        case 2:
            cout << "Enter value to insert at back: ";
            cin >> value;
            myList.insertAtBack(value);
            myList.print();
            break;
        case 3:
            if (myList.removeFromFront(value))
            {
                cout << "Removed value from the front: " << value << endl;
                myList.print();
            }
            else
                cout << "List is empty." << endl;
            break;
        case 4:
            if (myList.removeFromBack(value))
            {
                cout << "Removed value from the back: " << value << endl;
                myList.print();
            }
            else
                cout << "List is empty." << endl;
            break;
        case 5:
            cout << "Enter the index: ";
            cin >> index;
            cout << "Enter value to insert at index: ";
            cin >> value;
            if (myList.insertAtIndex(index, value))
            {
                myList.print();
            }
            else
                cout << "Incorrect index" << endl;
            break;
        case 6:
            cout << "Enter the index: ";
            cin >> index;
            if (myList.removeAtIndex(index, value))
            {
                cout << "Removed node at index: " << index << " the value: " << value << endl;
                myList.print();
            }
            else
                cout << "Incorrect index" << endl;
            break;
        case 7:
            if (myList.getElementCount() == 0)
            {
                cout << "List is empty." << endl;
            }
            cout << "List count: " << myList.getElementCount();
            cout << endl;
            break;
        case 8:
            if (myList.hasCycleDLL())
            {
                cout << "List has cycle.\n";
            }
            else cout << "List has no cycles.\n";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        cout << "What to do? ";
        cin >> choice;
    }
    myList.print();
    return 0;
}

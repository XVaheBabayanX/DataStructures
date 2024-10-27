#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

void instructions()
{
    cout << "Enter one of the followings:\n"
        << " 1 to enqueue (add) a value to the queue\n"
        << " 2 to dequeue (remove) a value from the queue\n"
        << " 3 to report the front value\n"
        << " 4 to check if the queue is empty\n"
        << " 5 to print all elements in the queue\n"
        << " 6 to end queue processing\n";
}

bool isDouble(string& input, double& value)
{
    try {
        value = stod(input);
        return true;
    }
    catch (const invalid_argument& e) {
        return false;
    }
    catch (const out_of_range& e) {
        return false;
    }
}

int main()
{
    Queue myQueue; 
    int choice;
    double value;
    string temp;

    instructions();
    cout << "What do you want to do with the queue? ";
    cin >> choice;

    while (choice != 6)  
    {
        switch (choice)
        {
        case 1:
            do
            {
                cout << "Enter value to enqueue into the queue: ";
                cin >> temp;
            } while (!(isDouble(temp, value)));
            myQueue.enqueue(value);
            cout << "Value enqueued into the queue.\n";
            break;
        case 2:
            if (myQueue.dequeue(value))
            {
                cout << "Dequeued value from the queue: " << value << endl;
            }
            else
            {
                cout << "Queue is empty." << endl;
            }
            break;
        case 3:
            if (!myQueue.isEmpty())
            {
                cout << "Front value in the queue: " << value << endl;
            }
            else
            {
                cout << "Queue is empty." << endl;
            }
            break;
        case 4:
            if (myQueue.isEmpty())
            {
                cout << "Queue is empty." << endl;
            }
            else
            {
                cout << "Queue is not empty." << endl;
            }
            break;
        case 5:
            myQueue.print(); 
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        cout << "What to do? ";
        cin >> choice;
    }

    return 0;
}

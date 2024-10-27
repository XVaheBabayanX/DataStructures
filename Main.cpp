#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

void instructions()
{
    cout << "Enter one of the followings:\n"
        << " 1 to push a value onto the stack\n"
        << " 2 to pop a value from the stack\n"
        << " 3 to report the top value\n"
        << " 4 to check if the stack is empty\n"
        << " 5 to end stack processing\n";
}

bool isDigit(string input)
{
    for (size_t i = 0; i < input.length(); ++i)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
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
    Stack myStack;
    int choice;
    double value;
    string temp;

    instructions();
    cout << "What do you want to do with the stack? ";
    cin >> choice;

    while (choice != 5)
    {
        switch (choice)
        {
        case 1:
            do
            {
                cout << "Enter value to push onto the stack: ";
                cin >> temp;
            } while (!(isDouble(temp, value)));
            myStack.Push(value);
            cout << "Value pushed onto the stack.\n";
            break;
        case 2:
            if (myStack.Pop(value))
            {
                cout << "Popped value from the stack: " << value << endl;
            }
            else
            {
                cout << "Stack is empty." << endl;
            }
            break;
        case 3:
            if (myStack.Top(value))
            {
                cout << "Top value in the stack: " << value << endl;
            }
            else
            {
                cout << "Stack is empty." << endl;
            }
            break;
        case 4:
            if (myStack.isEmpty())
            {
                cout << "Stack is empty." << endl;
            }
            else
            {
                cout << "Stack is not empty." << endl;
            }
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
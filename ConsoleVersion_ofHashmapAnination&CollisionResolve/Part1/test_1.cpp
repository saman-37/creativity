/*
Name : Samanpreet Kaur
Id: 100399074
Instructor: Muntaseer Salahuddin
Section: 001
*/

#include <iostream>
#include "Hashing_LinearProbing.h"

using std::cout, std::cin, std::endl;

int main()
{
    int size;
    double loadFactorThreshold;
    int key; 
    int operation;

    cout << "Welcome to Hashing Animation!!!\n";
    cout << "Enter the table size: ";
    cin >> size;

    cout << "Enter the load factor threshold: ";
    cin >> loadFactorThreshold;

    // construct hash-table with data provided
    Hashing_LinearProbing myHash(size, loadFactorThreshold);

    myHash.Display();

    char decision;
    do
    {
        cout << "Enter an integer key: ";
        cin >> key;

        cout << "Pick one of the following operations: 1.Search  2.Insert 3.Remove  4.RemoveAll\nYou can enter 1, 2, 3 or 4 here: ";
        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
            if (myHash.Search(key))
            {
                cout << key << " is in the hash set\n";
            }
            else
                cout << key << " is not in the hash set\n";
            break;

        case 2:
            myHash.Insert(key);
            break;

        case 3:
            myHash.Delete(key);
            break;

        case 4:
            myHash.RemoveAll();
            break;

        default:
            cout << "Invalid input. Please enter 1, 2, 3 or 4.\n";
        }

        cout << "\nYour hash after recent task: \n";
        myHash.Display();

        cout << "Would you like to do another operation on your hash? (y/n)";
        cin >> decision;
    } while (decision == 'y' || decision == 'Y');

    cout << "\nProgram ended!";
}
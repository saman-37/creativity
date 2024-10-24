#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SkipList.h"

using namespace std;

int main()
{
    srand(time(0));

    int n = 3;
    cout << "Skip list with maximum allowed level " << n << " is:\n";
    SkipList lst(n); // skiplist with maximum allowed level index

    // Testing insert function
    lst.InsertElement(13);
    lst.InsertElement(7);
    lst.InsertElement(11);
    lst.InsertElement(1);
    lst.InsertElement(5);
    lst.InsertElement(19);
    lst.InsertElement(313);
    lst.InsertElement(37);
    lst.InsertElement(311);
    lst.InsertElement(31);
    lst.InsertElement(35);
    lst.InsertElement(319);

    lst.Show();

    // Testing search function
    cout << "The element 7 is there in list , (before deletion)?  " << boolalpha << lst.Search(7) << endl;

    // Testing delete function
    lst.Delete(7);
    lst.Delete(11);
    lst.Delete(319);

    // Testing if delete function worked properly
    cout << "\nThe element 7 is there in list, (after deletion)?  " << boolalpha << lst.Search(7) << endl;
    lst.Show();

    // Testing rescale method
    int new_n = 5;
    cout << "\nRescaling the list to new max size: " << new_n << "\n";
    lst.Rescale(new_n);
    lst.Show();

    return 0;
}
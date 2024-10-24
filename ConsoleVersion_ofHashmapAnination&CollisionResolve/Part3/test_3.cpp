#include <iostream>
#include "Hashing_TwoSum.h"

using std::cout, std::cin, std::endl;

int main()
{
    cout << "Welcome to Two Sum Animation!!!\n";

    // static array
    int arr[] = {8, 7, 2, 5, 3, 1};
    int targetSum = 10;
    int arrSize = 6;

    // construct two-sum object
    TwoSum object(arr, arrSize, targetSum);

    Pair *thePair = object.findPair();

    // check if nothing got filled
    if (thePair == nullptr)
    {
        cout << "No pairs found\n";
    }

    else
    {
        // get the value of pair
        cout << "Pair found (" << thePair->value1 << ", " << thePair->value2 << ")\n";

        cout << "\nProgram ended!";
    }
}
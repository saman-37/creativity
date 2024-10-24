#include <iostream>
#include "HashTable.h"
using namespace std;

struct Pair
{
    int value1;
    int value2;

    Pair()
    {
        value1 = 0;
        value2 = 0;
    }
};

class TwoSum
{
public:
    int size; // size of integer array, will become size of our hash too
    int targetSum;
    HashTable hashtable; //(our hashtable can be made static array of integers)//yet this is just an object of another Class
    Pair *pair;          // make it a member, so that its value get filled after findPair() method has ended

    // Constructor
    TwoSum(int array[], int size, int targetSum)
    {
        this->targetSum = targetSum;
        this->size = size;
        hashtable = HashTable(size); // initialise hash-table

        for (int i = 0; i < size; i++)
            hashtable.Insert(array[i]); // fill hash-table

        pair = nullptr;
    }

    Pair *findPair()
    {
        //hashtable.Display();

        for (int i = 0; i < size; i++)
        {
            int firstPart = hashtable.hashTable[i]; // hashTable is of broad HashTable class, further access its data members
            int otherPart = targetSum - firstPart;

            if (hashtable.Search(otherPart)) // search returns true, we found the element
            {
                pair = new Pair();        // put ur own constructor
                pair->value1 = firstPart; // rather access them separately one-by-one later and then fill them
                pair->value2 = otherPart;
                return pair;
            }
        }

        return nullptr;
    }
};
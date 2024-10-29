#ifndef HASHINGLINEARPROBINGDEMO_H
#define HASHINGLINEARPROBINGDEMO_H
#include "SkipList.h"
#include <iostream>
#include <functional>
using namespace std;

class Hashing_SeparateChaining
{
private:
    // int *hashTable;
    SkipList *hashTable; // array of skip list for separate chaining
    int hashTableSize;
    int numberOfKeys;
    double loadFactorThreshold;
    hash<int> builtInHashFunction;

public:
    Hashing_SeparateChaining()
    {
        hashTable = nullptr;
        hashTableSize = 0;
        numberOfKeys = 0;
        loadFactorThreshold = 1.0; // unless stated only rehash when completely filled
    }

    Hashing_SeparateChaining(int size, double lft)
    {
        hashTableSize = size;
        numberOfKeys = 0;
        loadFactorThreshold = lft;

        hashTable = new SkipList[hashTableSize]; // default skip list, main task we are doing here is setting size of hashtable

        for (int i = 0; i < hashTableSize; i++)
            hashTable[i] = SkipList(1); // reassigning, here it will work fine //but, shallow copy, make sure deep copy happens
    }

    // Destructor, to release dynamically allocated memory
    ~Hashing_SeparateChaining()
    {
        delete[] hashTable;
        hashTable = nullptr;
    }

    void Insert(int value)
    {

        if (!Search(value))
        {
            double currentLoadFactor = (double)(numberOfKeys + 1) / hashTableSize;
            if (currentLoadFactor > loadFactorThreshold)
            {
                ReHash();
            }

            int hashCode = builtInHashFunction(value);
            int hashTableIndex = hashCode % hashTableSize;
            // Use SkipList to handle separate chaining
            hashTable[hashTableIndex].InsertElement(value);
            numberOfKeys++;
        }

        else
        {
            cout << "key " << value << "  is already in the hash set\n";
        }
    }

    void ReHash()
    {
        int newTableSize = 2 * hashTableSize;
        SkipList *new_hashTable = new SkipList[newTableSize];
        for (int i = 0; i < newTableSize; i++)
        {
            new_hashTable[i] = SkipList(1);
        }

        for (int i = 0; i < hashTableSize; i++)
        {
            if (hashTable[i].head->nextLinks[0] != nullptr) // if someone is there, find new position for him according to new size
            {
                Node *current = hashTable[i].head->nextLinks[0];
                while (current != nullptr)
                {
                    int new_hashCode = builtInHashFunction(current->value);
                    int new_hashtableIndex = new_hashCode % newTableSize;
                    new_hashTable[new_hashtableIndex].InsertElement(current->value);
                    current = current->nextLinks[0];
                }
            }
        }

        // clean up old hash
        delete[] hashTable;
        hashTable = new_hashTable;
        hashTableSize = newTableSize; // update the value of data field member
    }

    bool Search(int value)
    {
        int hashCode = builtInHashFunction(value);
        int hashTableIndex = hashCode % hashTableSize;
        return hashTable[hashTableIndex].Search(value); // a skip list is there, it will handle itself
    }

    void Delete(int value)
    {
        int hashCode = builtInHashFunction(value);
        int hashTableIndex = hashCode % hashTableSize;
        hashTable[hashTableIndex].Delete(value);
        numberOfKeys--;
    }

    // Edit it so that it prints skip list now
    void Display()
    {
        cout << "-------------------------------------------------------------------------------------------------------\n";
        cout << "Current table size: " << hashTableSize;
        cout << "     Number of keys: " << numberOfKeys;
        cout << "     Current Load: " << (double)(numberOfKeys) / hashTableSize;

        cout << "     Load Factor Threshold : " << loadFactorThreshold << endl;

        cout << "=======================================================================================================\n";

        if (hashTableSize == 0)
        {
            cout << "Nothing to display, hashtable is empty.\n";
            return;
        }
        cout << "The contents of hashtable are: \n";

        for (int i = 0; i < hashTableSize; i++)
        {
            cout << "[" << i << "] ";
            // Printing contents of skip list
            hashTable[i].Show();
            cout << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------\n";
    }
};
#endif
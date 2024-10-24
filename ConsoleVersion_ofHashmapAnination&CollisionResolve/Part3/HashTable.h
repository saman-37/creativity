#ifndef HASHINGLINEARPROBINGDEMO_H
#define HASHINGLINEARPROBINGDEMO_H
#include <iostream>
#include <functional>
using namespace std;
class HashTable
{
public:
    // int *hashTable; // table is simple array of integers, as we are storing pairs or multiple items @1index
    int *hashTable;
    int hashTableSize;
    hash<int> builtInHashFunction;

    HashTable()
    {
        hashTable = nullptr;
        hashTableSize = 0;
    }

    HashTable(int size)
    {
        hashTableSize = size;
        hashTable = new int[hashTableSize];

        // Initialise all indices to 0, to indicate empty space
        for (int i = 0; i < hashTableSize; i++)
        {
            hashTable[i] = 0;
        }
    }

    // Destructor, to release dynamically allocated memory
    ~HashTable()
    {
        delete[] hashTable;
        hashTable = nullptr;
    }

    void Insert(int value)
    {
        if (value == 0)
        {
            cout << "0 not allowed\n";
            return;
        }

        // not allowing repeated values
        if (!Search(value))
        {

            int hashCode = builtInHashFunction(value);
            int hashTableIndex = hashCode % hashTableSize;

            // output message
            if (hashTableIndex < 0)
            {
                return;
            }

            // no collision happened
            if (hashTable[hashTableIndex] == 0)

                hashTable[hashTableIndex] = value;

            // Handle collision using linear probing
            // Note: There must be at least 1 spot, as we are doing rehash on time
            else
            {
                // Start from immediate next index, but make sure, it loops and stays in circle
                for (int i = (hashTableIndex + 1) % hashTableSize; i != hashTableIndex; i = (i + 1) % hashTableSize)
                {
                    if (hashTable[i] == 0)
                    {
                        hashTable[i] = value;
                        return; // break once inserted
                    }
                }
            }
        }
        else
        {
            cout << "key " << value << "  is already in the hash set\n";
        }
    }

    bool Search(int value)
    {
        int hashCode = builtInHashFunction(value);

        int hashTableIndex = hashCode % hashTableSize;
        // output message
        if (hashTableIndex < 0)
        {
            return false;
        }
        int counter = 0;

        if (hashTable[hashTableIndex] == value)
        {
            return true;
        }

        // Linear probing might have happened, considering collision
        else
        {
            // start checking from immediate next index
            for (int i = (hashTableIndex + 1) % hashTableSize; i != hashTableIndex; i = (i + 1) % hashTableSize)
            {
                if (hashTable[i] == value)
                {
                    return true;
                }
            }
            return false;
        }
    }

    void Display()
    {
        cout << "-------------------------------------------------------------------------------------------------------\n";
        cout << "Current table size: " << hashTableSize << endl;

        cout << "=======================================================================================================\n";

        if (hashTableSize == 0)
        {
            cout << "Nothing to display, hashtable is empty.\n";
            return;
        }
        cout << "The contents of hashtable are: \n";

        for (int i = 0; i < hashTableSize; i++)
        {
            cout << "[" << i << "]   |" << hashTable[i] << " |" << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------\n";
        cout << endl;
    }
};
#endif
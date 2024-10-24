/*
Name : Samanpreet Kaur
Id: 100399074
Instructor: Muntaseer Salahuddin
Section: 001
*/

#ifndef HASHINGLINEARPROBINGDEMO_H
#define HASHINGLINEARPROBINGDEMO_H
#include <iostream>
#include <functional>
using namespace std;
class Hashing_LinearProbing
{
private:
    int *hashTable; 
    int hashTableSize;
    int numberOfKeys; // filled positions
    double loadFactorThreshold;
    // Declares an instance of the standard library's hash function template for int.
    hash<int> builtInHashFunction; // This function takes an integer and returns a hash value.

public:
    /*
    Default Constructor
    */
    Hashing_LinearProbing()
    {
        hashTable = nullptr;
        hashTableSize = 0;
        numberOfKeys = 0;
        loadFactorThreshold = 1.0; // unless stated only rehash when completely filled
    }

    /*
    Defined Constructor
    */
    Hashing_LinearProbing(int size, double lft)
    {
        hashTableSize = size;
        hashTable = new int[hashTableSize];
        for (int i = 0; i < hashTableSize; i++)
        {
            hashTable[i] = 0; // Initialise all indices to 0, to indicate empty space
        }
        numberOfKeys = 0;
        loadFactorThreshold = lft;
    }

    /*
     Destructor, to release dynamically allocated memory
    */
    ~Hashing_LinearProbing()
    {
        delete[] hashTable;
        hashTable = nullptr;
    }

    /*
    Inserts an integer value into the hash-table
    */
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
            double currentLoadFactor = (double)(numberOfKeys + 1) / hashTableSize;
            if (currentLoadFactor > loadFactorThreshold)

                ReHash();

            int hashCode = builtInHashFunction(value);
            int hashTableIndex = hashCode % hashTableSize;

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
            numberOfKeys++;
        }
        else
        {
            cout << "key " << value << "  is already in the hash set\n";
        }
    }

    /*
    Increases the size of the hash-table after certain capacity is filled
    */
    void ReHash()
    {
        int newTableSize = 2 * hashTableSize; // Double the size of the table
        int *new_hashTable = new int[newTableSize];

        // initialise all elements to 0, as soon as new hash_table created
        for (int i = 0; i < newTableSize; i++)
        {
            new_hashTable[i] = 0;
        }

        for (int i = 0; i < hashTableSize; i++)
        {
            // copy non-empty elements
            if (hashTable[i] != 0) // if someone is there, find new position for him according to new size
            {

                int value = hashTable[i]; // Get the element
                int new_hashCode = builtInHashFunction(value);
                int new_hashTableIndex = new_hashCode % newTableSize;

                // we may first try to insert directly, and later think of doing probing
                if (new_hashTable[new_hashTableIndex] == 0)
                {
                    new_hashTable[new_hashTableIndex] = value;
                }

                else
                {
                    //  Insert the element into the new table using linear probing to resolve collisions
                    while (new_hashTable[new_hashTableIndex] != 0)
                    {
                        new_hashTableIndex = (new_hashTableIndex + 1) % newTableSize; // Linear probing
                    }
                    new_hashTable[new_hashTableIndex] = value;
                }

                cout << hashTable[i] << " added at index: " << new_hashTableIndex << endl;
            }
        }

        delete[] hashTable;
        hashTable = new_hashTable;
        hashTableSize = newTableSize; // update the value of data field member
    }

    /*
   Searches an integer value in the hash-table
   */
    bool Search(int value)
    {
        int hashCode = builtInHashFunction(value);

        int hashTableIndex = hashCode % hashTableSize;

        if (hashTable[hashTableIndex] == value)
            return true;

        // Linear probing might have happened, considering collision
        else
        {
            // start checking from immediate next index
            for (int i = hashTableIndex + 1; i != hashTableIndex; i = (i + 1) % hashTableSize)
            {
                if (hashTable[i] == value)
                    return true;
            }
            return false;
        }
    }

    /*
   Deletes an integer value from the hash-table
   */
    void Delete(int value)
    {
        int hashCode = builtInHashFunction(value);
        int hashTableIndex = hashCode % hashTableSize;

        if (hashTable[hashTableIndex] == value)
        {
            hashTable[hashTableIndex] = 0;
            numberOfKeys--;
        }
        else
        {
            // start checking from immediate next index
            for (int i = (hashTableIndex + 1) % hashTableSize; i != hashTableIndex; i = (i + 1) % hashTableSize)
            {
                if (hashTable[i] == value)
                {
                    hashTable[i] = 0;
                    numberOfKeys--;
                    return;
                }
            }
            // Checked all indices, couldnt find element
            cout << "\nkey " << value << " is not in the hash set\n";
        }
    }

    /*
   Deletes all the integer value from the hash-table
   */
    void RemoveAll()
    {
        for (int i = 0; i < hashTableSize; i++)
        {
            if (hashTable[i] != 0)
                hashTable[i] = 0;
        }
    }

    void Display()
    {
        cout << "-------------------------------------------------------------------------------------------------------\n";
        cout << "Current table size: " << hashTableSize;
        cout << "     Number of keys: " << numberOfKeys;
        // if table size is zero, below calculation gives nan, how to avoid that
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
            cout << "[" << i << "]   |" << hashTable[i] << " |" << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------\n";
        cout << endl;
    }
};
#endif
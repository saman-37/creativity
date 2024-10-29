
#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <math.h>

#ifndef SKIPLIST_H
#define SKIPLIST_H

using namespace std;

class SkipList
{
public:
    int MAX_ALLOWED_LEVEL_INDEX;
    int currentHighestLevelIndex;
    Node *head;
    int size; // number of elements in skip list

    // Constructor
    SkipList()
    {
        size = 0;
        MAX_ALLOWED_LEVEL_INDEX = 0;
        currentHighestLevelIndex = 0;
        head = nullptr;
    }

    SkipList(int maxlevel)
    {
        size = 0;
        MAX_ALLOWED_LEVEL_INDEX = maxlevel;
        currentHighestLevelIndex = 0;
        head = new Node(INT_MIN, MAX_ALLOWED_LEVEL_INDEX);
    }

    ~SkipList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->nextLinks[0]; // Move to the next node
            delete temp;                     // Delete the node
        }
    }

    int randomLevel()
    {
        int lvl = 0;
        float probability = (float)rand() / RAND_MAX;
        while (probability < 0.5 && lvl < MAX_ALLOWED_LEVEL_INDEX)
        {
            lvl++;
            probability = (float)rand() / RAND_MAX;
        }
        return lvl;
    }

    /*
    The method enables insertion of a particular node with stated value in the skip list
    */
    void InsertElement(int data)
    {
        if (size + 1 > pow(2, MAX_ALLOWED_LEVEL_INDEX))
        {
            cout << "\n~~~~~~~~~~~~~~~~~~~TIME TO RESCALE UP!~~~~~~~~~~~~~~~~~\n";
            Rescale(MAX_ALLOWED_LEVEL_INDEX + 1);
        }
        Node *current = head;

        vector<Node *> update(MAX_ALLOWED_LEVEL_INDEX + 1, nullptr);

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current->nextLinks[i] != nullptr && current->nextLinks[i]->value < data)
            {
                current = current->nextLinks[i];
            }
            update[i] = current;
        }

        current = current->nextLinks[0];

        if (current == nullptr || current->value != data)
        {

            int ranLevel = randomLevel();

            if (ranLevel > currentHighestLevelIndex)
            {
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++)
                {
                    update[i] = head;
                }
                currentHighestLevelIndex = ranLevel;
            }

            Node *n = new Node(data, ranLevel);

            for (int i = 0; i <= ranLevel; i++)
            {
                n->nextLinks[i] = update[i]->nextLinks[i];
                update[i]->nextLinks[i] = n;
            }

            size++;
        }
    }

    /*
    The method enables searching of a particular node with stated value in the skip list
    */
    bool Search(int value)
    {
        Node *current = head;
        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current->nextLinks[i] != nullptr && current->nextLinks[i]->value < value)
            {
                current = current->nextLinks[i];
            }

            if (current->nextLinks[i] != nullptr && current->nextLinks[i]->value == value)
                return true;
        }

        current = current->nextLinks[0];
        if (current != nullptr && current->value == value)
            return true;

        return false;
    }

    /*
    The method enables deleting of a particular node with stated value in the skip list
    */
    void Delete(int value)
    {
        Node *current = head;

        vector<Node *> update(MAX_ALLOWED_LEVEL_INDEX + 1, nullptr);

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current->nextLinks[i] != nullptr && current->nextLinks[i]->value < value)
            {
                current = current->nextLinks[i];
            }
            update[i] = current;
        }

        current = current->nextLinks[0];

        if (current == nullptr || current->value != value)
        {
            cout << "No such item found " << endl;
            return;
        }

        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {

            if (update[i]->nextLinks[i] != current)
            {
                break;
            }

            update[i]->nextLinks[i] = current->nextLinks[i];
            if (size - 1 <= pow(2, MAX_ALLOWED_LEVEL_INDEX - 1))
            {
                cout << "~~~~~~~~~~~~~~~~~~~TIME TO RESCALE DOWN!~~~~~~~~~~~~~~~~~\n";

                Rescale(MAX_ALLOWED_LEVEL_INDEX - 1);
            }

            size--;
        }

        while (currentHighestLevelIndex > 0 && head->nextLinks[currentHighestLevelIndex] == nullptr)
        {
            currentHighestLevelIndex--;
        }

        delete current; // Free the memory occupied by the node
        cout << "Value " << current->value << " deleted." << endl;
    }

    /*
    The method enables resacling based on new maximum level (upscales/downscales)
    */
    void Rescale(int newMaxLevelIndex)
    {
        vector<int> baseLevelElements;
        Node *current = head->nextLinks[0];
        while (current != nullptr)
        {
            baseLevelElements.push_back(current->value);
            current = current->nextLinks[0]; // Move to the next node at level 0
        }

        current = head->nextLinks[0];
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->nextLinks[0]; // Move to the next node
            delete temp;                     // Delete the node
        }

        MAX_ALLOWED_LEVEL_INDEX = newMaxLevelIndex; // Update the maximum allowed level
        currentHighestLevelIndex = 0;               // Reset current highest level index
        size = 0;                                   // reset size
        // head = new Node(INT_MIN, MAX_ALLOWED_LEVEL_INDEX); //do not allocate
        head->nextLinks = vector<Node *>(MAX_ALLOWED_LEVEL_INDEX + 1, nullptr);

        for (int value : baseLevelElements)
        {
            InsertElement(value); // As our original skip list is there, and we are just reassigning values to it
        }

        cout << "\nRescale completed\n";
        cout << "New Maximum allowed level index is: " << MAX_ALLOWED_LEVEL_INDEX << endl;
    }

    /*
    The methods prints the skip list, with all levels
    */
    void Show()
    {
        // start from head's next,i.e. meaningful data
        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {
            Node *current = head->nextLinks[i];
            cout << "\t\tLevel " << i << ": ";

            if (current == nullptr)
            {
                cout << "Empty.\n";
                return;
            }

            while (current != nullptr && current->nextLinks[i] != nullptr)
            {

                cout << current->value << "->";
                current = current->nextLinks[i];
            }

            cout << current->value << " |" << endl; // To put separate punctuation here
        }
    }
};

#endif
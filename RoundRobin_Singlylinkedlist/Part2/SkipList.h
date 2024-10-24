#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#ifndef SKIPLIST_H
#define SKIPLIST_H

using namespace std;

class SkipList
{
public:
    int MAX_ALLOWED_LEVEL_INDEX;
    int currentHighestLevelIndex;
    Node *head;

    // Constructor
    SkipList(int maxlevel)
    {
        MAX_ALLOWED_LEVEL_INDEX = maxlevel;
        currentHighestLevelIndex = 0;
        head = new Node(INT_MIN, MAX_ALLOWED_LEVEL_INDEX);
    }

    /*
    Essential method for the probabilistic skip list data structure, which decides a level for each new node
    */
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
        Node *current = head;
        // update vector to keep track while coming up
        vector<Node *> update(MAX_ALLOWED_LEVEL_INDEX + 1, nullptr);

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        { // very imp to keep in mind, when to check value comparison from 1 step behind, when not
            while (current->nextLinks[i] != nullptr && current->nextLinks[i]->value < data)
            {
                current = current->nextLinks[i];
            }
            update[i] = current;
        }

        // Move 1 step ahead to check for duplicacy
        current = current->nextLinks[0];

        if (current == nullptr || current->value != data)
        {
            int ranLevel = randomLevel();

            if (ranLevel > currentHighestLevelIndex)
            {
                // Need to update more positions in update
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++)
                {
                    update[i] = head;
                }
                currentHighestLevelIndex = ranLevel;
            }

            // create node
            Node *n = new Node(data, ranLevel);

            // Restore links
            // in loop//until there is content in update
            for (int i = 0; i <= ranLevel; i++)
            {
                n->nextLinks[i] = update[i]->nextLinks[i];
                update[i]->nextLinks[i] = n;
            }
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

            // If at any level, loop existed due to larger value detect, return false rightaway
        }

        // check all leftout nodes at bottom level
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
            while (current->nextLinks[i] != nullptr && current->nextLinks[i]->value < value) // confusion about when try to spot, go to deepest level and then spot, as want to delete from level 0 and above
            {
                current = current->nextLinks[i];
            }
            update[i] = current;
        }

        current = current->nextLinks[0];

        if (current == nullptr || current->value != value) // BUT WE MAY NEED TO LOOP?
        {
            cout << "No such item found " << endl;
            return;
        }

        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {
            // If at a given level, the node's next link is not the node to delete, break out
            if (update[i]->nextLinks[i] != current)
            {
                break;
            }

            //  Update the link to bypass the current node, effectively deleting it from this level
            update[i]->nextLinks[i] = current->nextLinks[i];
        }

        // After deletion, check if we need to reduce the current highest level
        // If there are no nodes at the highest level, decrease the currentHighestLevelIndex
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
        // Check if the new maximum level index is the same as the current
        if (newMaxLevelIndex == MAX_ALLOWED_LEVEL_INDEX)
        {
            cout << "Same level as current, no change needs to be done.\n";
            return;
        }

        // Step 1: Store all values from level 0 in a vector
        vector<int> baseLevelElements;
        Node *current = head->nextLinks[0]; // Start from the first level
        while (current != nullptr)
        {
            baseLevelElements.push_back(current->value);
            current = current->nextLinks[0]; // Move to the next node at level 0
        }

        // Step 2: Delete all nodes in level 0
        current = head->nextLinks[0]; // Start again from the first level
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->nextLinks[0]; // Move to the next node
            delete temp;                     // Delete the node
        }

        // Step 3: Remove head node if necessary
        // (We are already creating a new head later, so we can skip this)
        // delete head; // Not necessary as we will create a new head

        // Step 4: Rebuild the skip list with the new maximum level index
        MAX_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;        // Update the maximum allowed level
        currentHighestLevelIndex = 0;                      // Reset current highest level index
        head = new Node(INT_MIN, MAX_ALLOWED_LEVEL_INDEX); // Create new head node

        // Step 5: Reinsert all values from baseLevelElements back into the skip list
        for (int value : baseLevelElements)
        {
            InsertElement(value); // As our original skip list is there, and we are just reassigning values to it
        }
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
            cout << "Level " << i << ": ";

            while (current != nullptr && current->nextLinks[i] != nullptr)
            {
                cout << current->value << "->";
                current = current->nextLinks[i];
            }
            // print last element, bcz we stopped 1 step behind, in fear of getting in invalid state in updation step
            cout << current->value << " ." << endl; // To put separate punctuation here
        }
    }

    // non-destructive: Resulting list is a new list, copying nodes, recalculating random levels
    SkipList merge(const SkipList &list)
    {
        // Data members of new skip list
        int MAX_ALLOWED_INDEX = 0;

        // Resultant's maximum_level_index, compare both, highest will be chosen
        if (list.MAX_ALLOWED_LEVEL_INDEX > MAX_ALLOWED_LEVEL_INDEX)
            MAX_ALLOWED_INDEX = list.MAX_ALLOWED_LEVEL_INDEX;
        else
            MAX_ALLOWED_INDEX = MAX_ALLOWED_LEVEL_INDEX;

        cout << "Printing value of MAX_ALLOWED_INDEX for new list: " << MAX_ALLOWED_INDEX << endl;
        // Call defined constructor to initialise new skip list
        SkipList new_List(MAX_ALLOWED_INDEX); // Pattern: ClassName objectName(parameters needed in constructor)

        // store integer values (NOT NODES, AS NODE COMES WITH RAN LEVEL DECIDED, but we need to generate that info again ) of base level elements of both lists in separate integer vector
        vector<int> list1Elements, list2Elements, new_ListElements;

        Node *current = head->nextLinks[0]; // Will get referance of first node in level 0, of "this" skip-list
        while (current != nullptr)
        {
            list1Elements.push_back(current->value);
            current = current->nextLinks[0];
        }

        // Print content of list1Elements for verification first.
        for (int i = 0; i < list1Elements.size(); i++)
        {
            cout << list1Elements[i] << "->";
        }
        cout << "done\n";

        // maybe we can store values of base level elements of both in vector , keep comparing, keep inserting,
        // but in that case, all new random levels needs to be decided for each node
        // we should just try to restore connections
        // so that levels remain same
    };

    // Destructive, change this to include elements of list to create new skip list in order
    SkipList mergeD(const SkipList &list)
    {
        // what will be resultant's maximum_level_index, compare both, highest will be chosen
        // maybe we can store values of base level elements of both in vector , keep comparing, keep inserting,
        // but in that case, all new random levels needs to be decided for each node
        // we should just try to restore connections
        // so that levels remain same
    }

    // Find all common items between two skip lists; find all unique items between two skip lists
    SkipList findCommonItems(const SkipList &list1, const SkipList &list2)
    {
    }

    // Count the number of values that meet certain criteria in a section of the list. For example, the number of odd values between x and y (where x and y are values of two nodes in the list marking some range that you want to search through)

    // Search from the right (add a tail member to the skip list class and implement each level as a doubly linked list)
    Node *searchFromRight(const SkipList &list, int value)
    {
    }

    // Save the skip list to a file with level info; load it back up from a file (maintaining saved structure)
    void saveToFile(const SkipList &list, const std::string &filename)
    {
    }
};

/*
Suggested Exercises:
Allow repeated values in the skip list
*/
#endif
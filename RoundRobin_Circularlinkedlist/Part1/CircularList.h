#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
class Node // Node class
{
public:
    int processTime;
    int turnaroundTime;
    int id; // remember which numbered process it is (P1, P2,..)
    Node *next;

    Node(int value, int idnumber) : processTime(value), id(idnumber), turnaroundTime(0), next(nullptr) {}
};

class CircularLinkedList
{
private:
    Node *last; // external referance to last node

public:
    CircularLinkedList() : last(nullptr) {}

    Node *getLast() // getter
    {
        return last;
    }

    bool isEmpty()
    {
        if (last == nullptr)
            return true;
        return false;
    }

    /*
    Display all elements in the circular linked list
    */
    void display()
    {
        if (last == nullptr)
            return;

        Node *current = last->next;

        cout << "\n||============Processes============||\n"
             << endl;
        do
        {
            cout << "P" << current->id << ":" << current->processTime << " ";

            current = current->next;
        } while (current != last->next);

        cout << endl;
    }

    /*
   Insert a new node with data at the end of the circular linked list
   */
    void insert(int processTime, int id)
    {
        // whenever requested for new node, give next number

        Node *new_node = new Node(processTime, id);

        if (last == nullptr)
        {
            last = new_node;
            last->next = last;
        }
        else
        {
            new_node->next = last->next;
            last->next = new_node;
            last = new_node;
        }
    }

    // Destructor
    ~CircularLinkedList()
    {
        if (last != nullptr) // prevents dereferencing a null pointer
        {
            Node *current = last->next;
            while (current != last)
            {
                Node *next = current->next;
                delete current;
                current = next;
            }
            delete last;
            last = nullptr; // last is external node pointer, remove it to indicate emptiness
        }
    }

    /*
   Delete for a node with the given data
   */
    void deleteNode(int data)
    {
        if (last == nullptr) // If the list is empty
            return;

        Node *current = last->next;
        Node *prev = last;

        // Loop through the circular linked list
        do
        {
            if (current->processTime == data) // Found the node to delete
            {
                if (current == last->next) // Node is head node
                {
                    if (last == current) // Only one node in the list
                    {
                        delete current;
                        last = nullptr; // List is now empty
                    }
                    else // More than one node
                    {
                        last->next = current->next; // Update head
                        delete current;
                    }
                }
                else if (current == last) // Node is the last node
                {
                    prev->next = last->next; // Bypass last node
                    delete last;
                    last = prev; // Update last pointer
                }
                else // Node is in the middle
                {
                    prev->next = current->next; // Bypass current node
                    delete current;
                }
                return; // Node deleted, exit function
            }

            prev = current; // Move to the next node
            current = current->next;
        } while (current != last->next);
    }

    /*
    Search for a node with the given data
    */
    bool search(int data)
    {
        if (last == nullptr)
            return false;

        Node *current = last->next;

        do
        {
            if (current->processTime == data)
                return true;
            current = current->next;
        } while (current != last->next);

        return false;
    }
};

#endif
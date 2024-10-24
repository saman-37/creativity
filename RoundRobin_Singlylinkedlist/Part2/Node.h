#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace std;

class Node
{
public:
    int value;
    vector<Node*> nextLinks;

    // constructor
    Node(int data, int level)
    {
        value = data;
        nextLinks = vector<Node*> (level+1, nullptr); 
    }
};

#endif
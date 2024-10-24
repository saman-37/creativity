#include <iostream>
// #include "CircularList.h"
#include "RoundRobinProcessScheduler.h"

using std::cout, std::cin, std::endl;

int main()
{
    RoundRobinProcessScheduler sch;
    sch.loadFromFile("process.txt");

    sch.process();
    sch.ShowResults();

    // CircularLinkedList list;
    // list.insert(1);
    // list.insert(2);
    // list.insert(3);
    // list.insert(4);

    // list.display();
    // list.deleteNode(4);
    // list.display();
    // cout << "HI";
}

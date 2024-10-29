#include <iostream>

#include "RoundRobinProcessScheduler.h"

using std::cout, std::cin, std::endl;

int main()
{
    RoundRobinProcessScheduler sch;
    sch.loadFromFile("process.txt");

    sch.process();
    sch.ShowResults();
}

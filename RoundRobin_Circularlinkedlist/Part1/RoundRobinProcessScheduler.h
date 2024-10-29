#include "CircularList.h" //which is concrete data structure
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

#ifndef PROCESSSCHEDULING_H
#define PROCESSSCHEDULING_H
struct information
{
    int turnaroundTime;
    int id;
};

class RoundRobinProcessScheduler
{

private:
    int timeSlice;
    CircularLinkedList processTimes;      // hold processTimes as read via file in order using insert()
    std::vector<information> processInfo; // need vector ( dynamic integer array) to store end times of all processes
    int globalTurnaroundTime;
    std::vector<std::vector<information>> collectionOfProcessInfos;

public:
    // Constructor
    RoundRobinProcessScheduler()
    {
        globalTurnaroundTime = 0;
    }

    /*Populates timeSlice  and processTimes by reading the data from the file*/
    void loadFromFile(string fileName)
    {
        ifstream input(fileName);

        if (!input)
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string processLine;

        while (input >> timeSlice) // as long as alternate lines are coming out to be integer type
        {
            // No need to ignore after reading the timeSlice
            input.ignore(numeric_limits<streamsize>::max(), '\n'); // Ensure the rest of the line is ignored after the integer

            // Read the line with process times (second line of pair)
            if (getline(input, processLine))
            {
                stringstream ss(processLine);
                int processTime;
                int counter = 1;

                // Parse each process time from the second line
                while (ss >> processTime)
                {
                    processTimes.insert(processTime, counter); // keep filling circular-list object
                    counter++;

                    if (ss.peek() == ',')
                        ss.ignore();
                }
            }

            process();
            ShowResults();
        }

        input.close();
    }

    /* Executes all the processes in processTimes to completion */
    void process()
    {
        processInfo.clear();
        globalTurnaroundTime = 0;

        if (processTimes.isEmpty()) // Nothing to process
        {
            return;
        }

        Node *lastNode = processTimes.getLast();
        Node *current = lastNode->next;

        while (!processTimes.isEmpty())
        {
            if (current->processTime > timeSlice)
            {
                globalTurnaroundTime += timeSlice;
                current->processTime -= timeSlice;
                current->turnaroundTime = globalTurnaroundTime; // Add time slice to turnaround time
                current = current->next;
            }

            else
            {
                int timeUsed = current->processTime;
                current->processTime = 0;
                globalTurnaroundTime += timeUsed;
                current->turnaroundTime = globalTurnaroundTime;

                information object;      // declare, dont use new when not alloacting memory ourself
                object.id = current->id; // initialise
                object.turnaroundTime = current->turnaroundTime;
                processInfo.push_back(object);

                // Step 2: Store next node referance before deleting
                Node *nextProcess = current->next;
                processTimes.deleteNode(current->processTime);
                current = nextProcess;
            }
        }
    }

    /*
    outputs the turnaround time for each process and the average turnaround time to file named output
    */
    void ShowResults()
    {
        // Check if the processInfo vector is empty
        if (processInfo.empty())
        {
            ofstream outputFile("output.txt", ios::app); // Open in append mode
            outputFile.close();
            return;
        }

        // Create an output file stream
        ofstream outputFile("output.txt", ios::app); // Open in append mode
        outputFile << "==================================" << endl;

        int totalDuration = 0;

        // Loop through the processInfo vector to print turnaround times
        for (const information &info : processInfo)
        {
            int processID = info.id;
            int turnaroundTime = info.turnaroundTime;

            outputFile << "P" << processID << " = " << turnaroundTime << endl;

            totalDuration += turnaroundTime; // Summing turnaround times for average calculation
        }

        // Calculating and printing the average turnaround time
        double average = static_cast<double>(totalDuration) / processInfo.size();
        outputFile << "average: " << average << endl
                   << "\n";

        // Close the output file
        outputFile.close();
    }
};

#endif

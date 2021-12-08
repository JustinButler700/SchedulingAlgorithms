//=========================================================
//Assignment 3
//Your name: Justin Butler & David Farjon
//Complier:  G++
//File type: Client program for implementing a rr algorithm
//==========================================================
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#define ERROR -1
//Purpose: creates a struct "process" that will act as our PCB 
//Variables:
// int Number = ID number of our process ex. T1, T2, T3
// int burst = burst time of our process ex. 20, 30, 40
// int priority = current priority value of our process. ex. 4, 3, 2, 1
typedef struct process_s {
    int number;
    int priority;
    int burst;
} process;
//Purpose: checks if a given string passed to it is a digit string
//output: returns false or true if the given string if a digit
bool check_number(std::string str)
{
    for (unsigned int i = 0; i != str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        else
            return (false);
    }
    return (true);
}
//Prints a vector of processes passed to it
// for debugging purposes
void printVector(std:: vector<process> myVector)
{
    for(unsigned int i = 0; i < myVector.size(); i++)
    {
        std::cout<< myVector[i].number<<" "<< myVector[i].priority<<" "<< myVector[i].burst<<" "<<std::endl; 
    }
}
// PURPOSE: step-by-step calculate turnaround and wait times in a RR algorithm on a given vector
// PAREMETER: a vector, which acts as our queue of processes, and a time quantum
// outputs each step of the RR turnaround time and wait time calculation
void rr(std::vector<process> q, int quantum)
{
    int wt = 0; // wait
    int tat = 0; //turn around time
    int average_wt = 0; // avg wait
    int average_tat = 0; //avg turn around time
    int size = q.size();
    while(q.size() !=0)
    {
        process p; // initialize a process to be pushed to the end of the vector if burst > quantum
        int currentBurst = q.front().burst;
        p.number = q.front().number;
        p.priority = q.front().priority;
        if(currentBurst > quantum)
        {
            p.burst = q.front().burst-quantum;
            tat += quantum;
            q.push_back(p); // add updated process back to the end of the array
            currentBurst = quantum;
        }
        else
        {
            tat += q.front().burst;
        }
        std::cout << "T" << q.front().number << " Turn-Around Time: ";
        std::cout << tat << ", Waiting Time: ";
        std::cout << wt << std::endl;
        average_wt += wt;
        wt += currentBurst;
        average_tat += tat;
        q.erase(q.begin()); // pop current process
    }
    average_tat /= size;
    average_wt /= size;
    std::cout << "Average turn-around time = " << average_tat << ", Average waiting time = " << average_wt << std::endl;
}
// Purpose: We start to check the number of argument, open the file, 
//          create a loop for scan line by line of the file for get 
//          data and fill a (queue/vector) of struct.
// Variables: ac is the number of arguments send to the program 
//            and av is a array of array of char who give the contenent
// We output each step of the RR algo and avg wait/turnaround time.
/*
To run it:
First make rr
then pass it an input file in shell ex. ./rr input.txt 10
(this adds input.txt to the vector with a time quantum of 10)
*/
int main(int ac, char *av[])
{
    std::vector<process> q; //holds the process's
    std::ifstream file;
    std::string token;
    std::string str;
    process p; // current process
    if (ac != 3)
        return (ERROR);
    file.open(av[1]);
    int quantum = std::atoi(av[2]); // set the time quantum
    while (true) {
        std::getline(file, str);
        if (file.fail())
            break;
        for (size_t i = 0; (i = str.find(", ")) != std::string::npos;) {
            token = str.substr(0, i);
            if (check_number(token)) {
                p.priority = std::stoi(token);
            } else {
                token.erase(0,1);
                p.number = std::stoi(token);
            }
            str.erase(0, i + 2);
        }
        if (check_number(str))
            p.burst = std::stoi(str);
        q.push_back(p);
    }
    rr(q, quantum); // run the round robin
    return (0);
}
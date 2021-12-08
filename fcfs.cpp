
//=========================================================
//Assignment 3
//Your name: Justin Butler & David Farjon
//Complier:  G++
//File type: Client program for implementing a FCFS algorithm
//==========================================================
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue> // use queue because first to come in the queue, is the first to come out

#define ERROR -1

//Purpose: creates a struct "process" that will act as our PCB 
//Variables:
// int Number = ID number of our process ex. T1, T2, T3
// int burst = burst time of our process ex. 20, 30, 40
typedef struct process_s {
    int number;
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
// PURPOSE: step-by-step calculate turnaround and wait times in a FCFS algorithm on a given queue
// PAREMETER: queue, a queue of process's
// outputs each step of the fcfs turnaround time and wait time calculation
void fcfs(std::queue<process> q)
{
    int wt = 0;
    int tat = 0;
    int average_wt = 0;
    int average_tat = 0;
    int size = q.size();

    while (q.size() != 0) {
        tat += q.front().burst;
        std::cout << "T" << q.front().number << " Turn-Around Time: ";
        std::cout << tat << ", Waiting Time: ";
        std::cout << wt << std::endl;
        average_wt += wt;
        wt += q.front().burst;
        average_tat += tat;
        q.pop();
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
// We output each step of the FCFS algo and avg wait/turnaround time.
/*
To run it:
First make fcfs
then pass it an input file in shell ex. ./fcfs input.txt
*/
int main(int ac, char *av[])
{
    std::queue<process> q; // holds our process's
    std::ifstream file;
    std::string token;
    std::string str;
    process p; //curent process

    if (ac != 2)
        return (ERROR);
    file.open(av[1]);
    while (true) {
        std::getline(file, str);
        if (file.fail())
            break;
        for (size_t i = 0; (i = str.find(", ")) != std::string::npos;) {
            token = str.substr(0, i);
            if (!check_number(token)) {
                token.erase(0,1);
                p.number = std::stoi(token);
            }
            str.erase(0, i + 2);
        }
        if (check_number(str))
            p.burst = std::stoi(str);
        q.push(p);
    }
    fcfs(q); //run our fcfs algo
    return (0);
}
//=========================================================
//Assignment 3
//Your name: Justin Butler & David Farjon
//Complier:  G++
//File type: Client program for implementing a sjf algorithm
//==========================================================
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue> 
#include <tuple>
#include <vector>

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
// PURPOSE: step-by-step calculate turnaround and wait times in a SJF algorithm on a given queue
// PAREMETER: queue, a queue of process's
// outputs each step of the SJF turnaround time and wait time calculation
void sjf(std::queue<process> q)
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
// We output each step of the SJF algo and avg wait/turnaround time.
/*
To run it:
First make sjf
then pass it an input file in shell ex. ./sjf input.txt
*/
int main(int ac, char *av[])
{
    std::vector<process> data; // sorts by SJF
    std::queue<process> q; // holds all our process
    std::ifstream file;
    std::string token;
    std::string str;
    process p; // current process
    int a = 0;

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
        data.push_back(p);
    }
    while (data.size() != 0) {
        a = 0;
        for (unsigned int i = 0; i != data.size(); i++) {
            if (data[i].burst < data[a].burst)
                a = i;
        }
        q.push(data[a]);
        data.erase(data.begin() + a);
    }
    sjf(q); // run sjf algo
    return (0);
}
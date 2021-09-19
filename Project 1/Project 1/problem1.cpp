#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "Process.h"


//Problem 1) Run through the 3 algorithms and determine both the normalized turnaround time
//and wait time for each process. Then report the results of the mean turnaround time and the maximum
//waiting time. Provide an analysis of the results.

//
void firstComeFirstServe(std::vector<Process> queue) { //No Preemption WORKS
	std::cout << "First Come First Serve" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int sum{ 0 };

	for (Process p : queue) {
		p.setExeTimeRem(0);
		p.setWaitTime(sum);
		sum = sum + p.getServTime();
		std::cout << p.getServTime() << " " << sum << std::endl;

	}
}


void roundRobin(std::vector<Process> queue) { //Quantum = 1ms WORKING
	std::cout << "Round Robin" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	bool finished = false;
	int sum{ 0 };//remove when done testing
	int wait{ 0 };

	while (1) {
		bool finished = true;
		sum = 0;
		for (int i = 0; i < queue.size(); i++) {
			if (queue.at(i).getExeTimeRem() > 0) { //Keeps while loop going if there is a process that isn't completed
				finished = false;
				queue.at(i).setExeTimeRemRR();
				queue.at(i).setWaitTime(wait);
				wait = wait + 1;
			}
			else {
				std::cout << std::endl << "Process finished running" << std::endl << std::endl;
			}
			sum = sum + queue.at(i).getExeTimeRem();
		}
		std::cout << std::endl << sum << std::endl;

		for (Process p : queue) {
			std::cout << p.getExeTimeRem() << " " << p.getWaitTime() << std::endl;
		}

		if (finished == true) { //If all processes are done break out of while loop
			std::cout << std::endl << "done" << std::endl << std::endl;
			break;
		}
	}

}


void shortestRemTime(std::vector<Process> queue) { //ITS WORKING
	std::cout << "Shortest Remaining Time" << std::endl << std::endl;
	int sum{ 0 };
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sorts processes based on service times
		return (i.getServTime() < j.getServTime()); });
	for (Process p : queue) {
		p.setExeTimeRem(0);
		p.setWaitTime(sum);
		sum = sum + p.getServTime();
		std::cout << p.getServTime() << ' ' << p.getWaitTime();
		std::cout << std::endl << "Process finished running" << std::endl << std::endl;
	}
}

int main() {
	//Process Queue
	std::vector<Process> queue;

	//Random Engine
	static std::random_device seed;
	static std::default_random_engine randEngine;

	//Populate process queue
	for (int i = 1; i <= 10; i++) {
		std::uniform_int_distribution<int> servTime(1, 100); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		Process p(servTime(randEngine), ariveTime(randEngine));
		queue.push_back(p);
	}

	//First Come First Serve (No Preemption)
	firstComeFirstServe(queue);

	//Round Robin
	roundRobin(queue);

	//Shortest Remaining Time
	shortestRemTime(queue);

	system("PAUSE");
	return 0;
}
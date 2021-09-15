#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "Process.h"


//Problem 1) Run through the 3 algorithms and determine both the normalized turnaround time
//and wait time for each process. Then report the results of the mean turnaround time and the maximum
//waiting time. Provide an analysis of the results.


int main() {
	//Process Queue
	std::vector<Process> queue;

	//Random Engine
	static std::random_device seed;
	static std::default_random_engine randEngine;

	//Populate process queue
	for (int i = 1; i <= 10; i++) {
		std::uniform_int_distribution<int> servTime(1, 100); // Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); // Milliseconds
		Process p(servTime(randEngine), ariveTime(randEngine));
		queue.push_back(p);
	}


	//First Come First Serve (no preemption)
	std::cout << "First Come First Serve" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int j{ 1 };
	for (Process p : queue) {
		std::cout << p.getAriveTime() << ' ';
		std::cout << std::endl << "Process finished running" << std::endl << std::endl;
		//wait times
		int k{ 0 };
		for (int i = j; i <= queue.size(); i++) {
			p.setWaitTime(queue.at(k).getServTime());//off by 1 
			std::cout << p.getWaitTime() << ' ';
			k++;
		}
		j++;

	}// cal wait times


	//Round Robin
	//Quantum = 1ms
	//Since the queue has already been sorted by arival times so no need to sort here
	std::cout << "Round Robin" << std::endl << std::endl;
	bool finished = false;
	int sum{ 0 };
	std::vector<int> exeTimeRems;
	for (Process p : queue) {
		exeTimeRems.push_back(p.getExeTimeRem());
	}
	while (1) {
		bool finished = true;
		sum = 0;
		for (int i = 0; i < exeTimeRems.size(); i++) {
			if (exeTimeRems.at(i) > 0) {//If any process still remains stay in loop
				finished = false;
				exeTimeRems.at(i)--;
			}
			else {
				std::cout << std::endl << "Process finished running" << std::endl << std::endl;
			}
			sum = sum + exeTimeRems.at(i);
		}
		std::cout << std::endl << sum << std::endl;
		if (finished == true) { //If all processes are done break out if loop
			std::cout << std::endl << "done" << std::endl << std::endl;
			break;
		}
	}//cal wait times


	//Shortest Remaining Time
	//std::sort(queue.begin(), queue.end(), [](for (Process p : queue)) {return p.getServTime});// sort processes based on service times
	//for (std::vector<Process>::iterator it = queue.begin(); it != queue.end(); ++it) {
		//it->getServTime();
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) {
		return (i.getServTime() < j.getServTime()); });
			//bool myfunction(Process i, Process j) { return (i.getServTime() < j.getServTime()); }
	//}

	std::cout << "Shortest Remaining Time" << std::endl << std::endl;
	for (Process p : queue) {
		std::cout << p.getServTime() << ' ';
		std::cout << std::endl << "Process finished running" << std::endl << std::endl;
	}//wait tiems

	system("PAUSE");
	return 0;
}
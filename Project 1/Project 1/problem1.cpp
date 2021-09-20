#include <iostream>
#include <algorithm>
#include <random>
#include <tuple>
#include <vector>
#include "Process.h"


//Problem 1) Run through the 3 algorithms and determine both the normalized turnaround time
//and wait time for each process. Then report the results of the mean turnaround time and the maximum
//waiting time. Provide an analysis of the results.


void firstComeFirstServe(std::vector<Process> queue) { //No Preemption WORKS
	std::cout << "First Come First Serve" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int sum{ 0 };

	for (int i = 0; i < queue.size(); i++) {
		queue.at(i).setExeTimeRem(0);
		queue.at(i).setWaitTime(sum);
		sum = sum + queue.at(i).getServTime();
		std::cout << queue.at(i).getServTime() << " " << queue.at(i).getWaitTime() << std::endl;
	}

	for (Process p : queue) {
		std::cout << p.getServTime() << " " << p.getWaitTime() << std::endl;
	}

	//Normalized Turnaround Times
	std::vector<int> TATs;
	for (Process p : queue) {
		TATs.push_back((p.getServTime() + p.getWaitTime()) / p.getServTime());
	}

	//Mean Turnaround Time
	float mTAT{ 0 };
	for (int i : TATs) {
		mTAT = mTAT + i;
		std::cout << mTAT << std::endl << std::endl;
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl 
			  << "Maximum Wait Time: " << queue.at(queue.size() - 1).getWaitTime() << std::endl;

}


void roundRobin(std::vector<Process> queue) { //Quantum = 1ms 
	std::cout << "Round Robin" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int sum{ 0 };//remove when done testing
	int wait{ 0 };

	while (1) {
		bool finished = true;
		sum = 0;
		for (int i = 0; i < queue.size(); i++) {
			if (queue.at(i).getExeTimeRem() > 0) { //Keeps while loop going if there is a process that isn't completed
				finished = false;
				queue.at(i).setExeTimeRemRRSRT();
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

	//Normalized Turnaround Times
	std::vector<int> TATs;
	for (Process p : queue) {
		TATs.push_back((p.getServTime() + p.getWaitTime()) / p.getServTime());
	}

	//Mean Turnaround Time
	float mTAT{ 0 };
	for (int i : TATs) {
		mTAT = mTAT + i;
		std::cout << mTAT << std::endl << std::endl;
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl
		<< "Maximum Wait Time: " << queue.at(queue.size() - 1).getWaitTime() << std::endl;

}



//WARNING: SPEGHETTI AHEAD!!!!
//IN TESTING
void shortestRemTime(std::vector<Process> queue) { //restructure
	std::cout << "Shortest Remaining Time" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int currentTime{0}, maxTime{0};
	//Calculate maxTime
	for (Process p : queue) {
		maxTime = maxTime + p.getServTime();
	}
	maxTime = maxTime + queue.at(queue.size() - 1).getAriveTime();
	
	std::vector<std::tuple<int, Process>> secondaryQueue;
	int sum{ 0 };

	//so i can see the initial queue
	for (Process p : queue) {
		std::cout << p.getAriveTime() << " " << p.getExeTimeRem() << std::endl << std::endl;
	} std::cout << std::endl;

	for (int i = 0; i < maxTime; i++) {
		if (currentTime <= queue.at(queue.size() - 1).getAriveTime()) {			
			for (int j = 0; j < queue.size(); j++) {
				if (queue.at(j).getAriveTime() <= currentTime) {
					secondaryQueue.push_back(std::make_tuple(j, queue.at(j)));
				}
			}
			if (secondaryQueue.size() != 0) {
				std::sort(secondaryQueue.begin(), secondaryQueue.end(), [](std::tuple<int, Process> i, std::tuple<int, Process> j) { //Sort based on remaining exe times
					return ((std::get<1>(i).getExeTimeRem()) < (std::get<1>(j).getExeTimeRem())); });
				queue.at(std::get<0>(secondaryQueue[0])).setExeTimeRemRRSRT(); // Gets the main queue index from the first tuple in the sorted secondary queue and processes that process this second
				//queue.at(std::get<0>(secondaryQueue[0])).setWaitTime(sum);//set wait time
			}
		}
		else {
			sort(queue.begin(), queue.end(), [](Process i, Process j) {
				return(i.getExeTimeRem() < j.getExeTimeRem()); });
			
			queue.at(0).setExeTimeRemRRSRT();
			//queue.at(0).setWaitTime(sum);//set wait time
//			sum = sum + p.getServTime();}
			//adjust all other wait times
		}
		//sum++;
		currentTime++;
		/*for (int i = 0; i < secondaryQueue.size(); i++) {
			std::cout << "a " << secondaryQueue.size() << std::endl << std::endl;
		}*/
	}


	for (Process p : queue) {
		std::cout << p.getAriveTime() << " " << p.getExeTimeRem() << std::endl << std::endl;
	}

	//for (Process p : queue) {
	//	p.setExeTimeRem(0);
	//	p.setWaitTime(sum);
	//	sum = sum + p.getServTime();
	//	std::cout << p.getServTime() << ' ' << p.getWaitTime();
	//	std::cout << std::endl << "Process finished running" << std::endl << std::endl;
	//}
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
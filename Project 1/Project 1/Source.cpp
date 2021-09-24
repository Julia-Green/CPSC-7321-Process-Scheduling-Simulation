#include <iostream>
#include <algorithm>
#include <random>
#include <tuple>
#include <vector>
#include "Process.h"

//FCFS for problem 1 and 2
void firstComeFirstServe(std::vector<Process> queue) { //No Preemption WORKS
	std::cout << "First Come First Serve" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int sum{ 0 };

	for (int i = 0; i < queue.size(); i++) {
		queue.at(i).setExeTimeRem(0);
		queue.at(i).setWaitTime(sum);
		sum = sum + queue.at(i).getServTime();
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
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl 
			  << "Maximum Wait Time: " << queue.at(queue.size() - 1).getWaitTime() << std::endl << std::endl;
}


//FCFS for problem 3
void firstComeFirstServeP(std::vector<Process> queue) { // WORKS
	std::cout << "First Come First Serve" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int temp = queue.size();
	std::vector<Process> running;
	std::vector<Process> complete;
	int currentTime{ 0 };

	while (1) {
		//wait for arival of a process
		if (queue.size() != 0) {
			if (currentTime >= queue.at(0).getAriveTime()) {
				running.push_back(queue.at(0)); //Add to running 
				queue.erase(queue.begin()); //remove from queue
			}
		}
		if (!running.empty()) {
			running.at(0).setExeTimeRem2(); //Runs Process

			for (int i = 1; i < running.size(); i++) {
				running.at(i).setWaitTime2(); //Add 1s to other running proccess' wait times
			}

			//Resort running vector based on priorities
			for (int i = 0; i < running.size() - 1; i++) {
				//Already sorted on arrival time
				if (running.at(i + 1).getPriority() > running.at(i).getPriority()) {
					std::swap(running.at(i), running.at(i + 1));
				}
			}

			if (running.at(0).getExeTimeRem() == 0) { //Checks to see if process is done and removes it 
					complete.push_back(running.at(0)); //Add to running 
					running.erase(running.begin()); //Remove from queue
			}
		}
		if (complete.size() == temp) {
			break;
		}
		currentTime++;
	}

	//Normalized Turnaround Times
	std::vector<int> TATs;
	for (Process p : complete) {
		TATs.push_back((p.getServTime() + p.getWaitTime()) / p.getServTime());
	}

	//Mean Turnaround Time
	float mTAT{ 0 };
	for (int i : TATs) {
		mTAT = mTAT + i;
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(complete.begin(), complete.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl
		<< "Maximum Wait Time: " << complete.at(complete.size() - 1).getWaitTime() << std::endl << std::endl;
}


//RR for problem 1 and 2
void roundRobin(std::vector<Process> queue) { //Quantum = 1ms 
	std::cout << "Round Robin" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int sum{ 0 };
	int wait{ 0 };

	while (1) {
		bool finished = true;
		sum = 0;
		for (int i = 0; i < queue.size(); i++) {
			if (queue.at(i).getExeTimeRem() > 0) { //Keeps while loop going if there is a process that isn't completed
				finished = false;
				queue.at(i).setExeTimeRem2();
				queue.at(i).setWaitTime(wait);
				wait = wait + 1;
			}
			sum = sum + queue.at(i).getExeTimeRem();
		}

		if (finished == true) { //If all processes are done break out of while loop
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
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl
		<< "Maximum Wait Time: " << queue.at(queue.size() - 1).getWaitTime() << std::endl;

}


//RR for problem 3
void roundRobinP(std::vector<Process> queue) { //Testing
	std::cout << "Round Robin" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int temp = queue.size();
	std::vector<Process> running;
	std::vector<Process> complete;
	int currentTime{ 0 };

	while (1) {
		//wait for arival of a process
		if (queue.size() != 0) {
			if (currentTime >= queue.at(0).getAriveTime()) {
				running.push_back(queue.at(0)); //Add to running 
				queue.erase(queue.begin()); //Remove from queue
			}
		}
		if (!running.empty()) {
			for (int i = 0; i < running.size(); i++) {
				running.at(i).setExeTimeRem2(); //Runs processes
			}

			for (int i = 0; i < running.size() - 1; i++) {
				for (Process p : running) {
					running.at(i).setWaitTime2();//Add 1s to running proccess' wait times
				}
			}

			//Resort running vector based on priorities
			for (int i = 0; i < running.size() - 1; i++) {
				if (running.at(i + 1).getPriority() > running.at(i).getPriority()) {//check here
					std::swap(running.at(i), running.at(i + 1));
				}
			}

			for (int i = 0; i < running.size(); i++) {
				if (running.at(i).getExeTimeRem() == 0) { //Checks to see if process is done and removes it not triggering
					complete.push_back(running.at(i)); //Add to running 
					running.erase(running.begin() + i); //Remove from queue
				}
			}
		}
		if (complete.size() == temp) {
			break;
		}
		currentTime++;
	}
	
	//Normalized Turnaround Times
	std::vector<int> TATs;
	for (Process p : complete) {
		TATs.push_back((p.getServTime() + p.getWaitTime()) / p.getServTime());
	}

	//Mean Turnaround Time
	float mTAT{ 0 };
	for (int i : TATs) {
		mTAT = mTAT + i;
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(complete.begin(), complete.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl
		<< "Maximum Wait Time: " << complete.at(complete.size() - 1).getWaitTime() << std::endl << std::endl;
}


//SRT for problem 1 and 2
void shortestRemTime(std::vector<Process> queue) {
	std::cout << "Shortest Time Remaining" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int temp = queue.size();
	std::vector<Process> running;
	std::vector<Process> complete;
	int currentTime{ 0 };

	while (1) {
		//wait for arival of a process
		if (queue.size() != 0) {
			if (currentTime >= queue.at(0).getAriveTime()) {
				running.push_back(queue.at(0)); //Add to running 
				queue.erase(queue.begin()); //remove from queue
			}
		}
		if (!running.empty()) {
			running.at(0).setExeTimeRem2(); //Runs Process

			for (int i = 1; i < running.size(); i++) {
				running.at(i).setWaitTime2(); //Add 1s to other running proccess' wait times
			}

			//Resort running vector based on remaining exe times
			for (int i = 0; i < running.size() - 1; i++) {
				//Already sorted on arrival time
				if (running.at(i + 1).getExeTimeRem() < running.at(i).getExeTimeRem()) {
					std::swap(running.at(i), running.at(i + 1));
				}
			}

			if (running.at(0).getExeTimeRem() == 0) { //Checks to see if process is done and removes it 
				complete.push_back(running.at(0)); //Add to running 
				running.erase(running.begin()); //Remove from queue
			}
		}
		if (complete.size() == temp) {
			break;
		}
		currentTime++;
	}

	//Normalized Turnaround Times
	std::vector<int> TATs;
	for (Process p : complete) {
		TATs.push_back((p.getServTime() + p.getWaitTime()) / p.getServTime());
	}

	//Mean Turnaround Time
	float mTAT{ 0 };
	for (int i : TATs) {
		mTAT = mTAT + i;
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(complete.begin(), complete.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl
		<< "Maximum Wait Time: " << complete.at(complete.size() - 1).getWaitTime() << std::endl << std::endl;
}


//SRT for problem 3
void shortestRemTimeP(std::vector<Process> queue) {
	std::cout << "Shortest Time Remaining" << std::endl << std::endl;
	std::sort(queue.begin(), queue.end(), [](Process i, Process j) { //Sort based on arrival times
		return (i.getAriveTime() < j.getAriveTime()); });

	int temp = queue.size();
	std::vector<Process> running;
	std::vector<Process> complete;
	int currentTime{ 0 };

	while (1) {
		//wait for arival of a process
		if (queue.size() != 0) {
			if (currentTime >= queue.at(0).getAriveTime()) {
				running.push_back(queue.at(0)); //Add to running 
				queue.erase(queue.begin()); //remove from queue
			}
		}
		if (!running.empty()) {
			running.at(0).setExeTimeRem2(); //Runs Process

			for (int i = 1; i < running.size(); i++) {
				running.at(i).setWaitTime2(); //Add 1s to other running proccess' wait times
			}

			//Resort running vector based on remaining exe times
			std::sort(running.begin(), running.end(), [](Process i, Process j) { //Sort based on arrival times
				return (i.getPriority() > j.getPriority()); });

			int count{ 0 };
			for (Process p : running) {
				if (p.getPriority() > 1) {
					count++;
				}
			}

			//Resort running vector based on priority
			for (int i = count; i < running.size() - 1; i++) {
				if (running.at(i + 1).getExeTimeRem() < running.at(i).getExeTimeRem()) {
					std::swap(running.at(i), running.at(i + 1));
				}
			}

			if (running.at(0).getExeTimeRem() == 0) { //Checks to see if process is done and removes it 
				complete.push_back(running.at(0)); //Add to running 
				running.erase(running.begin()); //Remove from queue
			}
		}
		if (complete.size() == temp) {
			break;
		}
		currentTime++;
	}

	//Normalized Turnaround Times
	std::vector<int> TATs;
	for (Process p : complete) {
		TATs.push_back((p.getServTime() + p.getWaitTime()) / p.getServTime());
	}

	//Mean Turnaround Time
	float mTAT{ 0 };
	for (int i : TATs) {
		mTAT = mTAT + i;
	}
	mTAT = mTAT / TATs.size();

	//Max Wait Time
	std::sort(complete.begin(), complete.end(), [](Process i, Process j) { //Sort based on wait times
		return (i.getWaitTime() < j.getWaitTime()); });

	std::cout << "Mean Turnaround Time: " << mTAT << std::endl
		<< "Maximum Wait Time: " << complete.at(complete.size() - 1).getWaitTime() << std::endl;
}


int main() {
	//Process Queue
	std::vector<Process> queue;

	//Random Engine
	static std::random_device seed;
	static std::default_random_engine randEngine;

	//Problem 1) Run through the 3 algorithms and determine both the normalized turnaround time
	//and wait time for each process. Then report the results of the mean turnaround time and the maximum
	//waiting time. Provide an analysis of the results.

	//Populating the process queue
	for (int i = 1; i <= 100; i++) {
		std::uniform_int_distribution<int> servTime(1, 100); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		Process p(servTime(randEngine), ariveTime(randEngine));
		queue.push_back(p);
	}

	std::cout << "Problem 1" << std::endl;

	//First Come First Serve (No Preemption)
	firstComeFirstServe(queue);

	//Round Robin
	roundRobin(queue);

	//Shortest Remaining Time
	shortestRemTime(queue);

	//Empty queue for problem 2
	queue.clear();


	//Problem 2) Begin with the generation of a similar dataset to problem 1, but this time, use a PRNG to 
	//(i) give half the processes service times between 80 and 100 milliseconds and
	//(ii) give the other half service times between 1 and 10 milliseconds. This time, for each algorithm, report 
	//the results of the overall mean turnaround timeand the mean turnaround time for each group of processes.
	//Provide an analysis of the results.

	//Populating half the process queue with processes that have 1-10ms service times
	for (int i = 1; i <= 50; i++) {
		std::uniform_int_distribution<int> servTime1(1, 10); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		Process p(servTime1(randEngine), ariveTime(randEngine));
		queue.push_back(p);
	}

	//Populating half the process queue with processes that have 80-100ms service times
	for (int i = 1; i <= 50; i++) {
		std::uniform_int_distribution<int> servTime2(80, 100); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		Process p(servTime2(randEngine), ariveTime(randEngine));
		queue.push_back(p);
	}

	std::cout << "Problem 2" << std::endl;

	//First Come First Serve (No Preemption)
	firstComeFirstServe(queue);

	//Round Robin
	roundRobin(queue);

	//Shortest Remaining Time
	shortestRemTime(queue);

	//Empty queue for problem 3
	queue.clear();


	//Problem 3) Begin with the generation of a similar dataset to problem 2, but this time, add prioritization
	//in the following manner : give each process a base priority of 1, but for 10 of the processes, give a
	//random priority between 2 and 16. For each algorithm, check the priority to ensure the highest priority
	//process runs next. Use the given algorithm to break any ties of priority in the queue. Record the mean
	//turnaround time for each algorithm. Provide an analysis of the results.

	//Populating half the process queue with processes that have 1-10ms service times, 45 of which have a priority of 1
	//and 5 that have a random priority from 2-16
	for (int i = 1; i <= 45; i++) {
		std::uniform_int_distribution<int> servTime1(1, 10); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		Process p(servTime1(randEngine), ariveTime(randEngine), 1);
		queue.push_back(p);
	}
	for (int i = 0; i <= 5; i++) {
		std::uniform_int_distribution<int> servTime2(1, 10); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		std::uniform_int_distribution<int> priority(2, 16);
		Process p(servTime2(randEngine), ariveTime(randEngine), priority(randEngine));
		queue.push_back(p);
	}

	//Populating half the process queue with processes that have 80-100ms service times, 45 of which have a priority of 1
	//and 5 that have a random priority from 2-16
	for (int i = 1; i <= 45; i++) {
		std::uniform_int_distribution<int> servTime3(80, 100); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		Process p(servTime3(randEngine), ariveTime(randEngine), 1);
		queue.push_back(p);
	}

	for (int i = 0; i <= 5; i++) {
		std::uniform_int_distribution<int> servTime4(80, 100); //Milliseconds
		std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
		std::uniform_int_distribution<int> priority(2, 16);
		Process p(servTime4(randEngine), ariveTime(randEngine), priority(randEngine));
		queue.push_back(p);
	}

	std::cout << "Problem 3" << std::endl;

	//First Come First Serve (No Preemption)
	firstComeFirstServeP(queue);

	//Round Robin
	roundRobinP(queue);

	//Shortest Remaining Time
	shortestRemTimeP(queue);

	system("PAUSE");
	return 0;
}
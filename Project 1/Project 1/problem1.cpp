#include <iostream>
#include <algorithm>
#include <random>
#include <tuple>
#include <vector>
#include "Process.h"


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
	std::vector<Process> completedQueue;
	int sum{ 0 };

	//so i can see the initial queue
	for (Process p : queue) {
		std::cout << p.getAriveTime() << " " << p.getExeTimeRem() << std::endl << std::endl;
	} std::cout << std::endl;

	for (int i = 0; i < maxTime; i++) {//change to while loop
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
		for (Process p : queue) { //adding proccesses more than once
			if (p.getExeTimeRem() == 0) {
				completedQueue.push_back(p);
			}
		}
		remove_if(queue.begin(), queue.end(), [](Process i) {
			return (i.getExeTimeRem() == 0);});
		//sum++;
		currentTime++;
		/*for (int i = 0; i < secondaryQueue.size(); i++) {
			std::cout << "a " << secondaryQueue.size() << std::endl << std::endl;
		}*/
	}

	std::sort(completedQueue.begin(), completedQueue.end(), [](Process i, Process j) { //Sort based on remaining exe times
		return (i.getAriveTime() < j.getAriveTime()); });

	for (Process p : completedQueue) {
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

	//Problem 1) Run through the 3 algorithms and determine both the normalized turnaround time
	//and wait time for each process. Then report the results of the mean turnaround time and the maximum
	//waiting time. Provide an analysis of the results.

	//Populating the process queue
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


	////Empty queue for problem 2
	//queue.clear();

	////Problem 2) Begin with the generation of a similar dataset to problem 1, but this time, use a PRNG to 
	////(i) give half the processes service times between 80 and 100 milliseconds and
	////(ii) give the other half service times between 1 and 10 milliseconds. This time, for each algorithm, report 
	////the results of the overall mean turnaround timeand the mean turnaround time for each group of processes.
	////Provide an analysis of the results.

	////Populating half the process queue with processes that have 1-10ms service times
	//for (int i = 1; i <= 5; i++) {
	//	std::uniform_int_distribution<int> servTime1(1, 10); //Milliseconds
	//	std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
	//	Process p(servTime1(randEngine), ariveTime(randEngine));
	//	queue.push_back(p);
	//}

	////Populating half the process queue with processes that have 80-100ms service times
	//for (int i = 1; i <= 5; i++) {
	//	std::uniform_int_distribution<int> servTime2(80, 100); //Milliseconds
	//	std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
	//	Process p(servTime2(randEngine), ariveTime(randEngine));
	//	queue.push_back(p);
	//}

	////First Come First Serve (No Preemption)
	//firstComeFirstServe(queue);

	////Round Robin
	//roundRobin(queue);

	////Shortest Remaining Time
	//shortestRemTime(queue);


	////Empty queue for problem 3
	//queue.clear();

	////Problem 3) Begin with the generation of a similar dataset to problem 2, but this time, add prioritization
	////in the following manner : give each process a base priority of 1, but for 10 of the processes, give a
	////random priority between 2 and 16. For each algorithm, check the priority to ensure the highest priority
	////process runs next. Use the given algorithm to break any ties of priority in the queue. Record the mean
	////turnaround time for each algorithm. Provide an analysis of the results.

	////Populating half the process queue with processes that have 1-10ms service times, 45 of which have a priority of 1
	////and 5 that have a random priority from 2-16
	//for (int i = 1; i <= 4; i++) {
	//	std::uniform_int_distribution<int> servTime1(1, 10); //Milliseconds
	//	std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
	//	Process p(servTime1(randEngine), ariveTime(randEngine), 1);
	//	queue.push_back(p);
	//}
	//for (int i = 0; i <= 1; i++) {
	//	std::uniform_int_distribution<int> servTime2(1, 10); //Milliseconds
	//	std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
	//	std::uniform_int_distribution<int> priority(2, 16);
	//	Process p(servTime2(randEngine), ariveTime(randEngine), priority(randEngine));
	//	queue.push_back(p);
	//}

	////Populating half the process queue with processes that have 80-100ms service times, 45 of which have a priority of 1
	////and 5 that have a random priority from 2-16
	//for (int i = 1; i <= 4; i++) {
	//	std::uniform_int_distribution<int> servTime3(80, 100); //Milliseconds
	//	std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
	//	Process p(servTime3(randEngine), ariveTime(randEngine), 1);
	//	queue.push_back(p);
	//}

	//for (int i = 0; i <= 1; i++) {
	//	std::uniform_int_distribution<int> servTime4(80, 100); //Milliseconds
	//	std::uniform_int_distribution<int> ariveTime(1, 1000); //Milliseconds
	//	std::uniform_int_distribution<int> priority(2, 16);
	//	Process p(servTime4(randEngine), ariveTime(randEngine), priority(randEngine));
	//	queue.push_back(p);
	//}

	////First Come First Serve (No Preemption)
	//firstComeFirstServe(queue);

	////Round Robin
	//roundRobin(queue);

	////Shortest Remaining Time
	//shortestRemTime(queue);

	system("PAUSE");
	return 0;
}
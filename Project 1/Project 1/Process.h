#pragma once

class Process {
	public:
		Process(int servTime, int ariveTime);
		Process(int servTime, int ariveTime, int prior);

		int getServTime();
		int getAriveTime();
		int getExeTimeRem();
		int getWaitTime();

		void setExeTimeRem(int time);
		void setExeTimeRemRRSRT(); // For Round Robin and Shortest Remaining Time Algorithms
		void setWaitTime(int time);

	private:
		int serviceTime; //Time required for the process to run overall
		int arrivalTime; //Between 1 and 1,000 milliseconds
		int exeTimeRemaining; //Execution time remaining
		int waitTime; //Calculated over the simulation
		int processGroup; // (for problem 2)
		int priority; // between 1 and 16 (for problem 3)
};
#pragma once
#include <iostream>
#include "Process.h"

Process::Process(int servTime, int ariveTime) {
	serviceTime = servTime;
	arrivalTime = ariveTime;
	exeTimeRemaining = servTime;
	waitTime = 0;
	processGroup; //remove
	priority; //remove
};

//Process::Process(int servTime, int prior) {
//	serviceTime = servTime;
//	int arrivalTime;
//	int exeTimeTemaining;
//	int waitTime;
//	int processGroup;
//	int priority = prior;
//};


//Process::Process(int servTime, int prior, int arivTime) {
//	serviceTime = servTime;
//	int arrivalTime = arivTime;
//	int exeTimeTemaining;
//	int waitTime;
//	int processGroup;
//	int priority = prior;
//};

int Process::getServTime() {
	return serviceTime;
}

int Process::getAriveTime() {
	return arrivalTime;
}

int Process::getExeTimeRem() {
	return exeTimeRemaining;
}

int Process::getWaitTime() {
	return waitTime;
}

void Process::setExeTimeRem() {
	exeTimeRemaining--;
}

void Process::setWaitTime(int time) {
	waitTime = time;
}
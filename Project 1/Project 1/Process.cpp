#pragma once
#include <iostream>
#include "Process.h"

Process::Process(int servTime, int ariveTime) {
	serviceTime = servTime;
	arrivalTime = ariveTime;
	exeTimeRemaining = servTime;
	waitTime = 0;
	processGroup = 0; //Not nessicary for my problem 2
	priority = 1; 
};

Process::Process(int servTime, int ariveTime, int prior) {
	serviceTime = servTime;
	arrivalTime = ariveTime;
	exeTimeRemaining = servTime;
	waitTime = 0;
	processGroup = 0; //Not nessicary for my problem 2
	priority = prior;
};

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

void Process::setExeTimeRem(int time) {
	exeTimeRemaining = time;
}

void Process::setExeTimeRemRRSRT() {
	if (exeTimeRemaining > 0) {
		exeTimeRemaining--;
	}
	else {
		exeTimeRemaining = 0;
	}
}

void Process::setWaitTime(int time) {
	waitTime = time;
}
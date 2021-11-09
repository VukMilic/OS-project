/*

 * infThr.cpp
 *
 *  Created on: Dec 8, 2020
 *      Author: OS1
*/

#include"infThr.h"
#include "pcb.h"

extern volatile int numOfActiveThreads;

InfThread::InfThread(StackSize stackSize, Time timeSlice):Thread(stackSize, timeSlice){

	this->getMyPCB()->notForScheduler = 1;//da ne udje nikad u Scheduler

}

void InfThread::run(){

	while(numOfActiveThreads!=0){};

}

InfThread::~InfThread(){
	waitToComplete();
}


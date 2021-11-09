/*
 * kernSem.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: OS1
 */
#include "kernSem.h"
#include "listSEM.h"

extern volatile PCB* running;

int KernelSem::staticId = 0;

KernelSem::KernelSem(int init) {

	myId = staticId++;

	val = init;

	flag = 0;

	listOfBlockedPCB = new ListPCB();

}

KernelSem::~KernelSem() {

	listOfBlockedPCB->wakeUpAll();

	delete listOfBlockedPCB;

}

int KernelSem::wait(Time maxTimeToWait) {

	lockFlag = 0;

	if (--val < 0) {

		running->blocked = 1;

		running->timeWaitOnSem = maxTimeToWait;
		if (maxTimeToWait == 0) {
			running->infWaitOnSem = 1;
		} else {
			running->infWaitOnSem = 0;
		}

		listOfBlockedPCB->addPCB((PCB*) running);

		unlockFlag();

		dispatch();

		lockFlag = 0;

		if (running->timeWaitOnSem == 0 && !running->infWaitOnSem) {

			unlockFlag();
			return 0;
		} else {

			unlockFlag();
			return 1;
		}
	} else {

		unlockFlag();
		return 1;

	}

}

void KernelSem::signal() {

	lockFlag = 0;

	if (val++ < 0) {							//<-------------------val<0

		listOfBlockedPCB->wakeUpFirst(myId);

	}

	unlockFlag();

}

void KernelSem::tick() {

	listOfBlockedPCB->tick(myId);

}


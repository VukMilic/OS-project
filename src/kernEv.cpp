/*

 * kernEv.cpp
 *
 *  Created on: Jan 2, 2021
 *      Author: OS1
 */

#include"kernEv.h"
#include"ivt.h"

extern IVTEntry* vecTable[256];
extern volatile PCB* running;
extern volatile unsigned lockFlag;
extern void unlockFlag();
extern volatile int numOfThreadsInScheduler;

KernelEv::KernelEv(IVTNo ivtNo) {

	ivtNumber = ivtNo;

	value = 0;

	blockedThread = 0;

	madeThisEvent = (PCB*) running;

	vecTable[ivtNumber]->setEvent(this);

}

KernelEv::~KernelEv() {

	vecTable[ivtNumber]->setEventNULL();

	blockedThread = 0;
	madeThisEvent = 0;


}

void KernelEv::wait() {

	lockFlag = 0;

	if (running->myId == madeThisEvent->myId) {

		if (value == 0) {

			running->blocked = 1;
			blockedThread = (PCB*) running;

			unlockFlag();

			dispatch();

		} else {

			value = 0;

			unlockFlag();
		}

	}

}

void KernelEv::signal() {

	lockFlag = 0;

	if (blockedThread == 0) {

		value = 1;

		unlockFlag();

	} else {

		blockedThread->blocked = 0;

		Scheduler::put(blockedThread);
		numOfThreadsInScheduler++;

		blockedThread = 0;

		unlockFlag();

	}

	dispatch();

}

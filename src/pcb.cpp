#include "pcb.h"

extern void unlockFlag();
extern volatile int numOfActiveThreads;


ID PCB::staticId = -2;

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* t) {

	myThread = t;
	myId = staticId++;

	quantum = timeSlice;
	if (quantum == 0) {
		infinitely = 1;
	} else {
		infinitely = 0;
	}

	timeWaitOnSem = 0;
	infWaitOnSem = 0;

	finished = 0;
	blocked = 0;
	started = 0;

	notForScheduler = 0;

	listOfBlocked = new ListPCB();

	if (stackSize > 65536) {

		stackSize = 65536;

	}

	stackSize = stackSize / sizeof(unsigned);

	unsigned* st1 = new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE

	st1[stackSize-1] = FP_SEG(myThread);
	st1[stackSize-2] = FP_OFF(myThread);

	st1[stackSize-5] = 0x200;

	st1[stackSize-6] = FP_SEG(wrapper);
	st1[stackSize-7] = FP_OFF(wrapper);

	sp = FP_OFF(st1+stackSize-16);
	ss = FP_SEG(st1+stackSize-16);
	bp =sp;

#endif

}

PCB::~PCB() {

	 listOfBlocked->wakeUpAll();

	 delete listOfBlocked;

}

void PCB::wrapper(Thread* t) {

	t->run();

	lockFlag = 0;

	t->myPCB->listOfBlocked->wakeUpAll();

	t->getMyPCB()->finished = 1;
	numOfActiveThreads--;

	unlockFlag();

	dispatch();
}

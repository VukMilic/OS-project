#include "thread.h"
#include "pcb.h"

#define lock asm cli
#define unlock asm sti

extern volatile PCB* running;
extern void interrupt timer();
extern volatile int numOfThreadsInScheduler;
extern volatile int numOfActiveThreads;
extern void unlockFlag();
extern ListPCB* threadsArray;

Thread::Thread(StackSize stackSize, Time timeSlice) {

	lockFlag = 0;

	myPCB = new PCB(stackSize, timeSlice, this);

	threadsArray->addPCB(myPCB);

	unlockFlag();
}

Thread::~Thread() {

	lockFlag = 0;

	if (myPCB != NULL) {

		delete myPCB;

	}

	unlockFlag();

}

void Thread::waitToComplete() {

	lockFlag = 0;

	if (!myPCB->finished) {

		running->blocked = 1;

		myPCB->listOfBlocked->addPCB((PCB*) running);

		unlockFlag();

		dispatch();

	} else {

		unlockFlag();
	}
}

void Thread::start() {

	lockFlag = 0;

	if (myPCB->started == 0) {

		myPCB->started = 1;

		Scheduler::put(myPCB);
		numOfThreadsInScheduler++;

		numOfActiveThreads++;

	}

	unlockFlag();
}

ID Thread::getId() {
	return myPCB->myId;
}

ID Thread::getRunningId() {
	return running->myId;
}

Thread* Thread::getThreadById(ID id) {

	lockFlag = 0;
	Thread* t = threadsArray->getPCBById(id)->myThread;
	unlockFlag();

	return t;

}

PCB* Thread::getMyPCB() {
	return myPCB;
}

void dispatch() {

	lock
	context_switch_on_demand = 1;
	timer();
	unlock
}

/*
 * pcb.h
 *
 *  Created on: Nov 24, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include <iostream.h>
#include <dos.h>
#include "thread.h"
#include "listPCB.h"

extern volatile int context_switch_on_demand;
extern volatile unsigned lockFlag;

class PCB{
public:

	static ID staticId;
	ID myId;


	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;

	unsigned quantum;
	unsigned infinitely;

	unsigned timeWaitOnSem;
	unsigned infWaitOnSem;

	unsigned finished;
	unsigned blocked;
	unsigned started;

	unsigned notForScheduler;

	Thread* myThread;

	ListPCB* listOfBlocked;//koliko je PCBova na ovoj niti blokirano

	PCB(StackSize stackSize , Time timeSlice , Thread* t);
	~PCB();

	static void wrapper(Thread* t);

};

#endif /* PCB_H_ */


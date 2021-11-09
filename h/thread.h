#ifndef _thread_h_
#define _thread_h_

#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"

typedef int ID;

extern volatile unsigned lockFlag;

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;

typedef unsigned int Time;
const Time defaultTimeSlice = 2;

class Thread{
public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);

	//void schedulerPut();

	PCB* getMyPCB();

protected:

	friend class PCB;
	Thread (StackSize stackSize = defaultStackSize , Time timeSlice = defaultTimeSlice );
	virtual void run(){};

private:

	PCB* myPCB;

};

void dispatch();

#endif


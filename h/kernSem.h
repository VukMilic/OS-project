/*
 * kernSem.h
 *
 *  Created on: Dec 19, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "listPCB.h"

extern void unlockFlag();

typedef unsigned int Time;

class KernelSem{
public:

	static int staticId;
	int myId;

	int val;

	int flag;

	ListPCB* listOfBlockedPCB;

	KernelSem(int init);
	~KernelSem();

	int wait(Time maxTimeToWait);
	void signal();

	void tick();

};



#endif /* KERNSEM_H_ */

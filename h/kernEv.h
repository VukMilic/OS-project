/*

 * kernEv.h
 *
 *  Created on: Jan 2, 2021
 *      Author: OS1

*/

#ifndef KERNEV_H_
#define KERNEV_H_

#include"pcb.h"

typedef unsigned char IVTNo;

class KernelEv{
public:

	int value;
	PCB* blockedThread;
	PCB* madeThisEvent;

	unsigned int ivtNumber;

	KernelEv(IVTNo ivtNo);

	~KernelEv();

	void wait();

	void signal();


};



#endif  KERNEV_H_

/*

 * ivt.h
 *
 *  Created on: Jan 22, 2021
 *      Author: OS1

*/

#ifndef IVT_H_
#define IVT_H_

#include"kernEv.h"

typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
private:

	pInterrupt oldRoutine;
	unsigned int num;

	KernelEv* myEvent;

public:

	IVTEntry();
	IVTEntry(IVTNo num , pInterrupt p);

	void callOld();

	~IVTEntry();

	void signal(int flag);

	IVTEntry* getEntry();

	void setEvent(KernelEv* ke);
	void setEventNULL();
};



#endif  IVT_H_

/*



* event.h

 *
 *  Created on: Jan 2, 2021
 *      Author: OS1

*/
#ifndef EVENT_H_
#define EVENT_H_

#include "kernEv.h"
#include "ivt.h"

#define PREPAREENTRY(num, flag)\
void interrupt inter##num(...); \
IVTEntry entry##num(num, inter##num); \
void interrupt inter##num(...) {\
	entry##num.signal(flag);\
	if (flag == 1){\
		entry##num.callOld();\
	}\
}

typedef unsigned char IVTNo;

class Event{
public:

	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:

	friend class KernelEv;
	void signal();

private:

	KernelEv* myImp;

};

#endif  EVENT_H_

/*

 * infThr.h
 *
 *  Created on: Dec 8, 2020
 *      Author: OS1
*/

#ifndef INFTHR_H_
#define INFTHR_H_

#include"thread.h"

class InfThread: public Thread{
public:
	InfThread(StackSize stackSize = defaultStackSize , Time timeSlice = 1);

	~InfThread();

protected:
	void run();

};

#endif  INFTHR_H_

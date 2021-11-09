/*


 * event.cpp
 *
 *  Created on: Jan 2, 2021
 *      Author: OS1
 */

#include"event.h"

extern volatile unsigned lockFlag;
extern void unlockFlag();

Event::Event(IVTNo ivtNo) {

	lockFlag = 0;

	myImp = new KernelEv(ivtNo);

	unlockFlag();

}

void Event::wait() {

	myImp->wait();

}

void Event::signal() {

	myImp->signal();

}

Event::~Event() {

	delete myImp;


}

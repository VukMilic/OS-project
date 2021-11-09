/*
 * semaphor.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: OS1
 */
#include "semaphor.h"
#include "listSEM.h"

extern ListSEM* semaphoreArray;
extern volatile unsigned lockFlag;
extern void unlockFlag();

Semaphore::Semaphore(int init) {

	lockFlag = 0;

	myImpl = new KernelSem(init);

	semaphoreArray->addSEM(myImpl);

	unlockFlag();
}

Semaphore::~Semaphore() {

	lockFlag = 0;

	if (myImpl != NULL) {

		delete myImpl;

	}

	unlockFlag();


}

int Semaphore::wait(Time maxTimeToWait) {

	return myImpl->wait(maxTimeToWait);

}

void Semaphore::signal() {

	myImpl->signal();

}

int Semaphore::val() const {

	return myImpl->val;

}


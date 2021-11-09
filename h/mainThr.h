/*
 * mainThr.h
 *
 *  Created on: Dec 14, 2020
 *      Author: OS1
 */

#ifndef MAINTHR_H_
#define MAINTHR_H_

#include "thread.h"

class MainThread: public Thread{
public:
	MainThread();
	~MainThread(){};
protected:
	void run(){};
};

MainThread::MainThread():Thread(){

	getMyPCB()->notForScheduler = 1;//da ne udje u scheduler nikad

}

#endif /* MAINTHR_H_ */

/*
 * listSEM.h
 *
 *  Created on: Dec 19, 2020
 *      Author: OS1
 */

#ifndef LISTSEM_H_
#define LISTSEM_H_

#include "kernSem.h"

class ListSEM{
private:

	struct Elem{
		KernelSem* ksem;
		Elem* next;
	};

	Elem* head;
	Elem* cur;
	Elem* temp;

public:

	ListSEM();
	~ListSEM();
	void addSEM(KernelSem* ks);
	void removeSEM(KernelSem* ks);

	KernelSem* getSEMById(int id);

	void printAll();

	void tick();
};







#endif /* LISTSEM_H_ */

/*
 * listPCB.h
 *
 *  Created on: Dec 15, 2020
 *      Author: OS1
 */

#include "pcb.h"


#ifndef LISTPCB_H_
#define LISTPCB_H_


class ListPCB{
private:

	struct Elem{
		PCB* pcb;
		Elem* next;
	};

	Elem* head;
	Elem* cur;
	Elem* temp;

public:

	ListPCB();
	~ListPCB();

	void addPCB(PCB* p);
	void removePCB(PCB* p);
	void deletePCB(int i);

	PCB* getPCBById(int id);

	void wakeUpFirst(int idSem);
	void wakeUpAll();
	void printAll();

	void tick(int idSem);

};




#endif /* LISTPCB_H_ */

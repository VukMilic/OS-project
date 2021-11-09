/*
 * listPCB.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: OS1
 */

#include "listPCB.h"
#include "listSEM.h"

extern volatile int numOfThreadsInScheduler;
extern ListSEM* semaphoreArray;

ListPCB::ListPCB() {

	head = 0;
	cur = 0;
	temp = 0;
}
ListPCB::~ListPCB() {

	while (head != 0) {

		temp = head;
		head = head->next;

		lockFlag = 0;
		temp->pcb = NULL;
		temp->next = NULL;
		delete temp;
		unlockFlag();

	}

	head = 0;
	cur = 0;
	temp = 0;


}

void ListPCB::addPCB(PCB* p) {

	Elem* newElem = new Elem;

	newElem->next = 0;
	newElem->pcb = p;

	if (head != 0) {
		cur = head;
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = newElem;
	} else {
		head = newElem;
	}

}

void ListPCB::removePCB(PCB* p) {

	temp = head;
	cur = head;

	while (cur != 0 && cur->pcb->myId != p->myId) {

		temp = cur;
		cur = cur->next;

	}

	if (cur == head) {

		head = head->next;

	} else if (cur != 0) {

		cur = cur->next;
//		delete temp->next;
		temp->next = cur;

	}

	//this->printAll();

}


void ListPCB::wakeUpFirst(int idSem) {

	if (head != 0) {

		cur = head;
		head = head->next;

		cur->pcb->blocked = 0;

		Scheduler::put(cur->pcb);
		numOfThreadsInScheduler++;

//		delete cur;

	}
}

void ListPCB::wakeUpAll() {

	while (head != 0) {
		wakeUpFirst(0);
	}

}
/*

 void ListPCB::printAll() {

 cur = head;

 while (cur != 0) {
 cout << ".." << cur->pcb->myId << "..";
 cur = cur->next;
 if (cur == 0) {
 cout << "\n";
 }
 }

 }
 */

PCB* ListPCB::getPCBById(int id) {

	cur = head;

	while (cur != 0) {
		if (cur->pcb->myId == id) {
			break;
		} else {
			cur = cur->next;
		}
	}

	if (cur != 0) {
		return cur->pcb;
	} else {
		return NULL;
	}

}

void ListPCB::tick(int idSem) {

	Elem* pom = head;

	while (pom != 0) {

		if (!pom->pcb->infWaitOnSem && pom->pcb->blocked) {

			pom->pcb->timeWaitOnSem--;

			if (pom->pcb->timeWaitOnSem == 0) {

				pom->pcb->blocked = 0;

				Scheduler::put(pom->pcb);
				numOfThreadsInScheduler++;

				semaphoreArray->getSEMById(idSem)->val++;

				this->removePCB(pom->pcb);

			}
		}

		pom = pom->next;

	}

}

/*
 * listSEM.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: OS1
 */

#include "listSEM.h"

ListSEM::ListSEM() {

	head = 0;
	cur = 0;
	temp = 0;
}

ListSEM::~ListSEM() {

	while (head != 0) {

		temp = head;
		head = head->next;

		lockFlag = 0;
		temp->ksem = NULL;
		temp->next = NULL;
		delete temp;
		unlockFlag();

	}

	head = 0;
	cur = 0;
	temp = 0;

}

void ListSEM::addSEM(KernelSem* ks) {

	Elem* newElem = new Elem;

	newElem->next = 0;
	newElem->ksem = ks;

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

void ListSEM::removeSEM(KernelSem* ks) {

	temp = head;
	cur = head;

	while (cur != 0 && cur->ksem->myId != ks->myId) {

		temp = cur;
		cur = cur->next;

	}

	if (cur == head) {

		head = head->next;

	} else if (cur != 0) {

		cur = cur->next;
		temp->next = cur;

	}

	//this->printAll();

}


/*void ListSEM::printAll(){

 cur = head;

 while(cur!=0){
 cout<<".."<<cur->ksem->myId<<"..";
 cur = cur->next;
 if(cur==0){
 cout<<"\n";
 }
 }

 }*/

KernelSem* ListSEM::getSEMById(int id) {

	cur = head;

	while (cur != 0) {
		if (cur->ksem->myId == id) {
			break;
		} else {
			cur = cur->next;
		}
	}

	if (cur != 0) {
		return cur->ksem;
	} else {
		return NULL;
	}

}

void ListSEM::tick() {

	cur = head;

	while (cur != 0) {

		cur->ksem->tick();

		cur = cur->next;

	}

}


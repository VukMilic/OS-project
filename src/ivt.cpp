#include"ivt.h"
#include<dos.h>

extern IVTEntry* vecTable[256];
extern volatile unsigned lockFlag;
extern void unlockFlag();

IVTEntry::IVTEntry() {
	oldRoutine = NULL;
}

IVTEntry::IVTEntry(IVTNo n, pInterrupt p) {

	this->num = n;
	pInterrupt pI = p;
	myEvent = NULL;

#ifndef BCC_BLOCK_IGNORE

	asm cli
	oldRoutine = getvect(num);
	setvect(num , pI);
	asm sti

#endif

	vecTable[num] = this;

}

void IVTEntry::callOld() {

	(*oldRoutine)();

}

void IVTEntry::signal(int flag) {

	if (myEvent != NULL) {
		myEvent->signal();
	} else {
		if (flag == 0) {
			callOld();
		}
	}

}

void IVTEntry::setEvent(KernelEv* ke) {

	myEvent = ke;

}

void IVTEntry::setEventNULL() {

	myEvent = NULL;

}

IVTEntry::~IVTEntry() {

	callOld();

	if (oldRoutine != NULL) {
#ifndef BCC_BLOCK_IGNORE
		asm cli
		setvect(num , oldRoutine);
		asm sti
#endif
	}

}

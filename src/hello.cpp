#include "thread.h"
#include "pcb.h"
#include <iostream.h>
#include <dos.h>
#include "infThr.h"
#include "mainThr.h"
#include "listPCB.h"
#include "listSEM.h"
#include "ivt.h"

volatile PCB* running;
volatile PCB* infPCB;
volatile PCB* mainPCB;

ListPCB* threadsArray = new ListPCB();
ListSEM* semaphoreArray = new ListSEM();

IVTEntry* vecTable[256];

void interrupt timer();

volatile int cntr = 20;
volatile int context_switch_on_demand = 0;
volatile unsigned lockFlag = 1;
void unlockFlag(){
	lockFlag = 1;
	if(context_switch_on_demand){
		dispatch();
	}
}
volatile int numOfThreadsInScheduler = 0;
volatile int numOfActiveThreads = 0;

volatile unsigned tsp;
volatile unsigned tss;
volatile unsigned tbp;

unsigned oldTimerOFF, oldTimerSEG;
extern void tick();

void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax // es = 0

		// pamti staru rutinu
		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		// postavlja novu rutinu
		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		// postavlja staru rutinu na int 60h
		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}

}

void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}

volatile int pom = 0;

void interrupt timer(){

	if(!context_switch_on_demand){

		pom = 0;
		tick();
		semaphoreArray->tick();

	}else{

		pom = 1;

	}

	if (!context_switch_on_demand && !running->infinitely)	cntr--;
	if ((cntr == 0 && !running->infinitely) || context_switch_on_demand) {
		if(lockFlag==1){

			context_switch_on_demand = 0;

			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			running->sp = tsp;
			running->ss = tss;
			running->bp = tbp;


			if(!running->finished && !running->blocked && !running->notForScheduler){

				Scheduler::put((PCB*)running);
				numOfThreadsInScheduler++;

			}


			running = Scheduler::get();
			numOfThreadsInScheduler--;

			if(!infPCB->finished && running == NULL){

					running = infPCB;

			}else{
				if(running== NULL){
					running = mainPCB;
				}
			}

			tsp = running->sp;
			tss = running->ss;
			tbp = running->bp;

			cntr = running->quantum;

			asm {
				// restaurira sp
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}

		}else{

			context_switch_on_demand = 1;

		}

	}

	if(!pom) asm int 60h;


}




extern int userMain(int argc, char* argv[]);

int main(int argc,char* argv[]){

	InfThread* inf = new InfThread();
	infPCB = inf->getMyPCB();

	MainThread* mt = new MainThread();
	mainPCB = mt->getMyPCB();

	running = mainPCB;

	inic();

	int a = userMain(argc,argv);

	restore();


	delete inf;
	delete mt;
	delete threadsArray;
	delete semaphoreArray;


	return a;
}

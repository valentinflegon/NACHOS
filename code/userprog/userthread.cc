#ifdef CHANGED

#include "userthread.h"
int COUNTER;
struct schmurtz
{
    int f;
    int arg;
};


//DEBUG('x', "mon debug %d\n", mavar);

/****************************
 * do_ThreadCreate
 *
 ****************************/

int do_ThreadCreate(int f, int arg){
    DEBUG('t', "do_ThreadCreate");
    Thread *newThread = new Thread("new thread");
    COUNTER++;
    struct schmurtz *s;
    s = (struct schmurtz*) malloc(2*sizeof(int));
    s->f = f;
    s->arg = arg;
    newThread->Start(StartUserThread,s);
    //StartUserThread(schmurtz);

    //test si y a de la place dans la pile reurn -1 si pas de place
    //ici
    return 1;
}

/****************************
 * StartUserThread
 *
 ****************************/
static void StartUserThread(void *arg){ //voir AddrSpace
    struct schmurtz* ptr = (struct schmurtz*) arg;
    DEBUG('t',"StartUserThread \n");
    // similaire a AddrSpace InitRegisters
    int i;
    for (i = 0; i < NumTotalRegs; i++){
    	machine->WriteRegister (i, 0);
    }
    machine->WriteRegister (PCReg,ptr->f );
    machine->WriteRegister (4,ptr->arg);
    //DEBUG('x', "mon debug %d\n", mavar);
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
    machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack ());

    machine->Run();

}

/****************************
 * do_ThreadExit
 * détruit le thread Nachos
 ****************************/
void do_ThreadExit(){
  if (COUNTER>0){
    currentThread->Finish();
    COUNTER--;
  }
  if (COUNTER==0)
    interrupt->Halt ();
}

#endif

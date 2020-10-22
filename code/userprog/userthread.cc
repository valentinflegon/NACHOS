#ifdef CHANGED

#include "userthread.h"
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
    struct schmurtz s = malloc(sizeof(int)*2);
    schmurtz.f = f;
    schmurtz.arg = arg;
    newThread->Start(StartUserThread,schmurtz);
    //StartUserThread(schmurtz);
    //test si y a de la place dans la pile reurn -1 si pas de place
    //ici
}

/****************************
 * StartUserThread
 *
 ****************************/
static void StartUserThread(void *schmurtz){ //voir AddrSpace
    DEBUG('t',"StartUserThread \n");
    // similaire a AddrSpace InitRegisters
    int i;
    for (i = 0; i < NumTotalRegs; i++){
    	machine->WriteRegister (i, 0);
    }
    machine->WriteRegister (PCReg,schmurtz.f );
    machine->WriteRegister (4,schmurtz.arg);
    //DEBUG('x', "mon debug %d\n", mavar);
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
    machine->WriteRegister (StackReg, numPages * PageSize - 16);

    machine->Run();

}

/****************************
 * do_ThreadExit
 * détruit le thread Nachos
 ****************************/
void do_ThreadExit(){
    currentThread->Finish();
}

#endif

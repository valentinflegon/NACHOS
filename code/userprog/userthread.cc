#ifdef CHANGED

#include "userthread.h"
int COUNTER = 1;

struct schmurtz
{
    int f;
    int arg;
    //int pos;
};
//static BitMap *bitmap;


//DEBUG('x', "mon debug %d\n", mavar);

/****************************
 * do_ThreadCreate
 *
 ****************************/

int do_ThreadCreate(int f, int arg){
    //bitmap = new BitMap (UserStacksAreaSize/256);
    //if (bitmap.numclear() !=0 ){}
    DEBUG('t', "do_ThreadCreate");
    Thread *newThread = new Thread("new thread");
    COUNTER++;
    struct schmurtz *s;
    s = (struct schmurtz*) malloc(2*sizeof(int));
    s->f = f;
    s->arg = arg;
    //s->pos = bitmap.find ();
    newThread->Start(StartUserThread,s);
    //return 1;

    //test si y a de la place dans la pile reurn -1 si pas de place
    //ici

    return -1;
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
    //machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack (ptr->pos) );
    machine->Run();

}

/****************************
 * do_ThreadExit
 * détruit le thread Nachos
 ****************************/
void do_ThreadExit(){
  if (COUNTER>1){
    DEBUG('t',"On fait un finish \n");
    COUNTER--;
    currentThread->Finish();
    // tant que nummclear != 1 on fait currentThread->Finish()
    //il faudrait clear le bit dans le bitmap mais comment savoir lequel est celui du thread ?
  }
  if (COUNTER==1)//quand numclear == 1
  {
    DEBUG('t',"On fait un halt \n");
    interrupt->Halt ();
  }
}

#endif

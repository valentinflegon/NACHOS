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
    if (currentThread->space->bitmap->NumClear() !=0 ){
      DEBUG('t', "do_ThreadCreate\n");
      COUNTER++;
      const char *name = "Thread";
      Thread *newThread = new Thread(name+COUNTER);
      struct schmurtz *s;
      s = (struct schmurtz*) malloc(2*sizeof(int));
      s->f = f;
      s->arg = arg;
      currentThread->pos = currentThread->space->bitmap->Find ();
      //s->pos =
      newThread->Start(StartUserThread,s);
      return 1;
    }

    printf("Il n'y a plus de place disponible sur la pile pour pouvoir créer et executer un nouveau thread\n");
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
    //machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack ());
    machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack (currentThread->pos) );
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
    currentThread->space->bitmap->Clear (currentThread->pos);
    currentThread->Finish();
    // tant que numclear != 1 on fait currentThread->Finish()
  }
  if (COUNTER==1)//quand numclear == 1
  {
    currentThread->space->bitmap->Clear (currentThread->pos);
    DEBUG('t',"On fait un halt \n");
    interrupt->Halt ();
  }
}

#endif

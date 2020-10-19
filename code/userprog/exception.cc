// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"


/**********************************
 * copyStringFromMachine
 * 
 **********************************/	
#ifdef CHANGED
int copyStringFromMachine(int from, char *to, unsigned size){
	int x;
	for(unsigned i = 0; i<size-1; i++){
		machine->ReadMem(from+i, 1,&x);
		to[i] = (char)x;
		if ( (char)x == '\0'){
			return i;
		}
	}
	to[size] = '\0'; 
	return size;
}

/**********************************
 * copyStringToMachine
 * 
 **********************************/
int copyStringToMachine(int to, char *from,unsigned size){
for (unsigned i=0; i<size-1;i++)
  {
    machine->WriteMem (to+i, 4, from[i]);
    if ( from[i] == '\0')
    {
      return i;
    }
  }
  machine->WriteMem (to+size-1, 4, '\0');
  return size;
}
#endif

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
    int address = machine->registers[BadVAddrReg];

    switch (which)
      {
	case SyscallException:
          {
	    switch (type)
	      {
		case SC_Halt:
		  {
		    DEBUG ('s', "Shutdown, initiated by user program.\n");
		    interrupt->Halt();
		    break;
		  }
		#ifdef CHANGED		
		case SC_Exit:
		  {
		    DEBUG ('s', "Exit\n");
		    interrupt->Halt();
		    break;
		  }
		case SC_PutChar:
		  {
		    DEBUG ('s', "PutChar\n");
			int car = machine->ReadRegister (4);
			consoledriver->PutChar(car);
		    break;
		  }
		
		case SC_PutString:{
			DEBUG ('s',"PutString\n");
			char to[MAX_STRING_SIZE];
			int s;
			int shift = copyStringFromMachine (machine->ReadRegister (4), to, MAX_STRING_SIZE);
			consoledriver->PutString (to);
			s = shift-1;
			while (shift==MAX_STRING_SIZE)
			{
			shift = copyStringFromMachine (machine->ReadRegister (4)+s, to, MAX_STRING_SIZE);
			consoledriver->PutString (to);
			s += shift-1;
			}
			break;
      	}

		case SC_GetChar:
		  {
		    DEBUG ('s', "GetChar\n");
			int i = consoledriver->GetChar();
			if( i == 10){ //   EOF case   
				machine->WriteRegister(2,'\0');
				break;
			}
			machine->WriteRegister(2,i);
		    break;
		  }

		case SC_GetString:{
			DEBUG ('s', "GetString\n");
			char str[12];
			consoledriver->GetString(str,12);
			break;
		}

		case SC_ThreadCreate:{
			DEBUG('t',"ThreadCreate");
			int f, arg;//to define
			do_ThreadCreate(f,arg);
			break;
		}

		case SC_ThreadExit:{
			DEBUG('t',"ThreadExit");
			do_ThreadExit();
			//interrupt->Halt(); if c'est le dernier threads sjdsf
			break;

		}











		#endif //CHANGED 









		default:
		  {
		    printf("Unimplemented system call %d\n", type);
		    ASSERT(FALSE);
		  }
	      }

	    // Do not forget to increment the pc before returning!
	    UpdatePC ();
	    break;
	  }

	case PageFaultException:
	  if (!address) {
	    printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	    ASSERT (FALSE);
	  } else {
	    printf ("Page Fault at address %x at PC %x\n", address, machine->registers[PCReg]);
	    ASSERT (FALSE);	// For now
	  }
	  break;

	case ReadOnlyException:
	  printf ("Read-Only at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case BusErrorException:
	  printf ("Invalid physical address at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case AddressErrorException:
	  printf ("Invalid address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case OverflowException:
	  printf ("Overflow at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case IllegalInstrException:
	  printf ("Illegal instruction at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	default:
	  printf ("Unexpected user mode exception %d %d %x at PC %x\n", which, type, address, machine->registers[PCReg]);
	  ASSERT (FALSE);
	  break;
      }
}
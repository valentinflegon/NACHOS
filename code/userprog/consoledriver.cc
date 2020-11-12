#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *nbThread;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    nbThread = new Semaphore("Thread in progress", 1);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}

ConsoleDriver::~ConsoleDriver()
{
    delete console;
    delete writeDone;
    delete readAvail;
    delete nbThread;
}

void ConsoleDriver::PutChar(int ch)
{
  nbThread->P ();
  console->TX (ch);	// echo ch
	writeDone->P ();	// wait for write to finish
  nbThread->V ();
}

int ConsoleDriver::GetChar()
{
  nbThread->P ();
  int ch;
  readAvail->P ();	// wait for character to arrive
  ch = console->RX ();
  nbThread->V ();
  return ch;
}


void ConsoleDriver::PutString(const char s[])
{
  nbThread->P ();
  int i = 0;
  while (s[i] != '\0'){
      PutChar(s[i]);
      i++;
  }nbThread->V ();
}
void ConsoleDriver::GetString(char *s, int n)
{
  nbThread->P ();
  int i = 0;
  while( n > 0){

      s[i] = GetChar();
      //printf(" s[%d] = %d ",i,s[i] );
      i++;
      n--;
  }
  nbThread->V ();
}



#endif // CHANGED

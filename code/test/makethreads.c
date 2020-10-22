#include "syscall.h"

void test (char c){
  PutChar (c);
  ThreadExit ();
}

int main () {
  ThreadCreate (test , 'a');

  Halt ();
}

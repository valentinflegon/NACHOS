#include "syscall.h"

int printChar (char c){
    PutChar (c);
    ThreadExit ();
    return 0;
}

int print10Char (char c){
  int i;
  for (i = 0; i<5; i++)
  {
    ThreadCreate (printChar, c);
  }
  ThreadExit ();
  return 0;
}

int test (char c){
  print10Char (c);
  ThreadExit ();
  return 0;
}

int test2 (char s[]){
  PutString (s);
  ThreadExit ();
  return 0;
}


int main () {
  ThreadCreate (test, 'a');
  ThreadCreate (test2, "abcdzekh");

  ThreadExit ();
  return 0;
}

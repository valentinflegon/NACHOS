#include "syscall.h"

int test (char c){
  PutChar (c);
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
  //ThreadCreate (test, '\n');
  ThreadCreate (test2, "abcdzekh");
  //ThreadCreate (test, '\n');

  ThreadExit ();
  return 0;
}

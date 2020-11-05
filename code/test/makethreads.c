#include "syscall.h"

int test (char c){
  PutChar (c);
  ThreadExit ();
  return 0;
}
int test2 (char s[]){
  PutString (s);
  ThreadExit ();
}


int main () {
  ThreadCreate (test, 'a');
  //ThreadCreate (test2, "abcdzekh");

  ThreadExit ();
  return 0;
}

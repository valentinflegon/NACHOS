#include "syscall.h"

void print(char* c){
   PutString(c);
}

int main(){
    print("azerty");
    print("\n");
    Halt();
    //tesssssst
}

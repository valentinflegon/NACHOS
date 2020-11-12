#include <cstdlib>
#include "system.h"
#include "addrspace.h"
#include "bitmap.h"


extern int do_ThreadCreate(int f, int arg);

static void StartUserThread(void *schmurtz);

void do_ThreadExit();

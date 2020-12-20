// utiliser semaphore dans les getEmptypage etc pour securiser l'acces
// +rajouter la compilation dans le common.makefile
// creer la classe comme le consoledriver

#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "pageprovider.h"
#include "synch.h"

PageProvider::PageProvider ()
{
  bitmap = new BitMap (NumPhysPages);
}
PageProvider::~PageProvider ()
{
  delete bitmap;
}

int PageProvider::getEmptyPage ()
{
  int empty_page = bitmap->Find ();
  if (empty_page == -1)
    return -1;
  int addr_page = (empty_page*PageSize);
  void *mem_addr = &(machine->mainMemory[addr_page]);
  memset (mem_addr, 0, PageSize);
  return empty_page;
} 

void PageProvider::ReleasePage (int addr_page) 
{
  int num_page = addr_page/PageSize;
  bitmap->Clear (num_page);
}

int PageProvider::NumAvailPage ()
{
  return bitmap->NumClear ();
}








#endif // CHANGED
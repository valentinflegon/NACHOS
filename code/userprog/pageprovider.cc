// utiliser semaphore dans les getEmptypage etc pour securiser l'acces
// +rajouter la compilation dans le common.makefile
// creer la classe comme le consoledriver

#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "pageprovider.h"
#include "synch.h"
//#include "machine.h" 


// si on a le temps regarder les pb de boucle de .h avec les differentes inclusions (notamment entre system.h et pageprovider.h)

static Semaphore *bitmapAvail;
static Semaphore *opOnCounter;

PageProvider::PageProvider ()
{
  bitmap = new BitMap (NumPhysPages);
  free_pages = bitmap->NumClear ();
  bitmapAvail = new Semaphore ("bitmap available",1);
  opOnCounter = new Semaphore  ("operation on counter of free pages", 1);
}
PageProvider::~PageProvider ()
{
  delete bitmap;
  delete bitmapAvail;
}

int PageProvider::getEmptyPage ()
{
  //rajouter un semaphore pour la gestion d'appels par plusieurs process differents
  bitmapAvail->P ();
  int empty_page = bitmap->Find ();
  bitmapAvail->V ();
  if (empty_page == -1)
    return -1;
  void *mem_addr = &(machine->mainMemory[empty_page*PageSize]);
  memset (mem_addr, 0, PageSize);
  return empty_page;
} 

void PageProvider::ReleasePage (int page) 
{
  bitmap->Clear (page);
  opOnCounter->P ();
  free_pages++;
  opOnCounter->V ();
}

void PageProvider::BookPages (int nb_pages)
{
  opOnCounter->P ();
  free_pages -= nb_pages;
  opOnCounter->V ();
} 

int PageProvider::NumAvailPage ()
{
  return free_pages;
}








#endif // CHANGED
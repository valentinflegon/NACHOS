#ifdef CHANGED
#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H


#include "copyright.h"
#include "utility.h"
#include "system.h"
#include "bitmap.h"


class PageProvider:dontcopythis{
  public:
    PageProvider ();
    ~PageProvider (); //clean up

    int getEmptyPage ();
    void ReleasePage (int addr_page);
    int NumAvailPage ();

  private:
    BitMap *bitmap;
};

#endif // PAGEPROVIDER_H

#endif // CHANGED






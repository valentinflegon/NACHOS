#ifdef CHANGED


#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H


#include "copyright.h"
#include "utility.h"
//#include "system.h"
#include "machine.h" 
#include "bitmap.h"


class PageProvider:dontcopythis{
  public:
    PageProvider ();
    ~PageProvider (); //clean up

    int getEmptyPage (); //Permet de récuperer le numero d'une page disponible
    void ReleasePage (int page); //permet de liberer la page page de la bitmap
    void BookPages (int nb_pages); //permet de reserver virtuellement nb_pages de la bitmap
    int NumAvailPage (); //permet de savoir combien il reste de pages disponibles

  private:
    BitMap *bitmap;
    int free_pages;
};

#endif // PAGEPROVIDER_H

#endif // CHANGED






//
// Classe de base d'un probleme
//

#ifndef EtatAmibeBiologie_h
#define EtatAmibeBiologie_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatAmibeBiologie : public Etat
{
    public:
     EtatAmibeBiologie(void);	
     virtual ~EtatAmibeBiologie(void);

     static Etat *construire(void){return new EtatAmibeBiologie();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

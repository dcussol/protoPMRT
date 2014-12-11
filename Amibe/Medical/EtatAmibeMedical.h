//
// Classe de base d'un probleme
//

#ifndef EtatAmibeMedical_h
#define EtatAmibeMedical_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatAmibeMedical : public Etat
{
    public:
     EtatAmibeMedical(void);	
     virtual ~EtatAmibeMedical(void);
     
     static Etat *construire(void){return new EtatAmibeMedical();}

     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

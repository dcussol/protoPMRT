//
// Classe de base d'un probleme
//

#ifndef EtatWormMedical_h
#define EtatWormMedical_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatWormMedical : public Etat
{
    public:
     EtatWormMedical(void);	
     virtual ~EtatWormMedical(void);
     
     static Etat *construire(void){return new EtatWormMedical();}

     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

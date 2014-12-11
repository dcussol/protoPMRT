//
// Classe de base d'un probleme
//

#ifndef EtatWormIrradiation_h
#define EtatWormIrradiation_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatWormIrradiation : public Etat
{
    public:
     EtatWormIrradiation(void);	
     virtual ~EtatWormIrradiation(void);
     
     static Etat *construire(void){return new EtatWormIrradiation();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

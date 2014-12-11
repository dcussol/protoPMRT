//
// Classe de base d'un probleme
//

#ifndef EtatWormPhysiqueMedicale_h
#define EtatWormPhysiqueMedicale_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatWormPhysiqueMedicale : public Etat
{
    public:
     EtatWormPhysiqueMedicale(void);	
     virtual ~EtatWormPhysiqueMedicale(void);
     
     static Etat *construire(void){return new EtatWormPhysiqueMedicale();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

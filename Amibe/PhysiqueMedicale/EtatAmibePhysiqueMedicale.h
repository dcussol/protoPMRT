//
// Classe de base d'un probleme
//

#ifndef EtatAmibePhysiqueMedicale_h
#define EtatAmibePhysiqueMedicale_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatAmibePhysiqueMedicale : public Etat
{
    public:
     EtatAmibePhysiqueMedicale(void);	
     virtual ~EtatAmibePhysiqueMedicale(void);
     
     static Etat *construire(void){return new EtatAmibePhysiqueMedicale();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

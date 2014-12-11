//
// Classe de base d'un probleme
//

#ifndef EtatAmibeIrradiation_h
#define EtatAmibeIrradiation_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatAmibeIrradiation : public Etat
{
    public:
     EtatAmibeIrradiation(void);	
     virtual ~EtatAmibeIrradiation(void);
     
     static Etat *construire(void){return new EtatAmibeIrradiation();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

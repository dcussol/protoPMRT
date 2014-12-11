//
// Classe de base d'un probleme
//

#ifndef EtatWormBiologie_h
#define EtatWormBiologie_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatWormBiologie : public Etat
{
    public:
     EtatWormBiologie(void);	
     virtual ~EtatWormBiologie(void);

     static Etat *construire(void){return new EtatWormBiologie();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

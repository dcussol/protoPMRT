//
// Classe de base d'un probleme
//

#ifndef EtatWormImagerie_h
#define EtatWormImagerie_h

class Automate;
#include "Etat.h"
#include <string>

using namespace std;

class EtatWormImagerie : public Etat
{
    public:
     EtatWormImagerie(void);	
     virtual ~EtatWormImagerie(void);
 
     static Etat *construire(void){return new EtatWormImagerie();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

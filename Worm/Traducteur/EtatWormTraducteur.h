//
// Classe de base d'un probleme
//

#ifndef EtatWormTraducteur_h
#define EtatWormTraducteur_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatWormTraducteur : public Etat
{
    public:
     EtatWormTraducteur(void);	
     virtual ~EtatWormTraducteur(void);

     static Etat *construire(void){return new EtatWormTraducteur();}
          
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

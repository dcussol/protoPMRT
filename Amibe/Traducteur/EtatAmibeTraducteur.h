//
// Classe de base d'un probleme
//

#ifndef EtatAmibeTraducteur_h
#define EtatAmibeTraducteur_h

#include "Etat.h"
#include <string>

using namespace std;

class EtatAmibeTraducteur : public Etat
{
    public:
     EtatAmibeTraducteur(void);	
     virtual ~EtatAmibeTraducteur(void);

     static Etat *construire(void){return new EtatAmibeTraducteur();}
          
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

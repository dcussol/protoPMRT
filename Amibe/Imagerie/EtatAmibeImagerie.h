//
// Classe de base d'un probleme
//

#ifndef EtatAmibeImagerie_h
#define EtatAmibeImagerie_h

class Automate;
#include "Etat.h"
#include <string>

using namespace std;

class EtatAmibeImagerie : public Etat
{
    public:
     EtatAmibeImagerie(void);	
     virtual ~EtatAmibeImagerie(void);
 
     static Etat *construire(void){return new EtatAmibeImagerie();}
     
     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      }
};

#endif    

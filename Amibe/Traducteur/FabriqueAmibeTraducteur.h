//
// Classe de base d'un FabriqueAmibeTraducteur
//

#ifndef FabriqueAmibeTraducteur_h
#define FabriqueAmibeTraducteur_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueAmibeTraducteur: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueAmibeTraducteur(void);	
     virtual ~FabriqueAmibeTraducteur(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

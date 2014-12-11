//
// Classe de base d'un FabriqueWormTraducteur
//

#ifndef FabriqueWormTraducteur_h
#define FabriqueWormTraducteur_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueWormTraducteur: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueWormTraducteur(void);	
     virtual ~FabriqueWormTraducteur(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

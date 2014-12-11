//
// Classe de base d'un FabriqueWormIrradiation
//

#ifndef FabriqueWormIrradiation_h
#define FabriqueWormIrradiation_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueWormIrradiation: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueWormIrradiation(void);	
     virtual ~FabriqueWormIrradiation(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

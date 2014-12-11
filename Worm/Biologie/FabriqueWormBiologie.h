//
// Classe de base d'un FabriqueWormBiologie
//

#ifndef FabriqueWormBiologie_h
#define FabriqueWormBiologie_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueWormBiologie: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueWormBiologie(void);	
     virtual ~FabriqueWormBiologie(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

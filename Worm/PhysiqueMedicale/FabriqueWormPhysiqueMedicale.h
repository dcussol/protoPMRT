//
// Classe de base d'un FabriqueWormPhysiqueMedicale
//

#ifndef FabriqueWormPhysiqueMedicale_h
#define FabriqueWormPhysiqueMedicale_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueWormPhysiqueMedicale: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueWormPhysiqueMedicale(void);	
     virtual ~FabriqueWormPhysiqueMedicale(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

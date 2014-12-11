//
// Classe de base d'un FabriqueAmibePhysiqueMedicale
//

#ifndef FabriqueAmibePhysiqueMedicale_h
#define FabriqueAmibePhysiqueMedicale_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueAmibePhysiqueMedicale: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueAmibePhysiqueMedicale(void);	
     virtual ~FabriqueAmibePhysiqueMedicale(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

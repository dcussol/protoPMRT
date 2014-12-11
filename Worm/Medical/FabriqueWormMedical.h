//
// Classe de base d'un FabriqueWormMedical
//

#ifndef FabriqueWormMedical_h
#define FabriqueWormMedical_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueWormMedical: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueWormMedical(void);	
     virtual ~FabriqueWormMedical(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif

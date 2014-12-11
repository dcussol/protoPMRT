//
// Classe de base d'un FabriqueAmibeIrradiation
//

#ifndef FabriqueAmibeIrradiation_h
#define FabriqueAmibeIrradiation_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueAmibeIrradiation: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueAmibeIrradiation(void);	
     virtual ~FabriqueAmibeIrradiation(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif
